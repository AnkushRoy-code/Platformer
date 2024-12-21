#include "PhysicsMap.h"
#include "Platformer/Physics.h"
#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "utils/constants.h"
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

/*
 * So... You reached here... See this joke of a algorithm fucks all the
 * optimisations harder than Will Smith's slap in the middle of making this algo
 * I learnt that lookup in set is faster than of a vector... So in the middle I
 * changed from vec to set :). I might've broken all rules for optimisation, but
 * it might not matter much because C++ is fast (got no better excuse) and that
 * this function will only run once :) during initialisation.
 *
 * After all this you would think atleast his algorithm work. No it doesn't
 * always work. The algorithm is supposed to provide a vector of b2Vec2 in
 * 'anitclockwise' order so that it can 'b2CreateChain' function can create a
 * static physics shape that can collide with the player body. Unfortunately I
 * was unable to find a way to detect or make the algo give out the vec2 in
 * anticlockwise manner.
 *
 * Why though?
 * - Yes I could just give all the different physics blocks their own collider
 * shape. But that would be too easy. And inefficient. Now performance matters
 * because it'll run every frame.
 *
 * - Okay how it works now:
 *      - 1. First gets a 2D array of int and populates another vec of
 * co-ordinates using the given array.
 *
 *          Array Contents (Input):
 *
 *          - 0 -> Water
 *          - 1 -> Grass
 *          - 2 -> Dirt
 *
 *          Before anything we differenciate between different patches of Dirt
 * block (Really Hard!) and then, for every Dirt block detected we populate the
 * vec with 4 co-ordinates (Top-Left, Top-Right, Bottom-Left and Bottom-Right
 * vectices)
 *
 *      - 2. So now there would be dublicate co-ordinates right?
 *
 *          The co-ordinates that occur odd number of times are actually the
 * corners! Half of our work done! Detecting co-ordinates was really hard before
 * I got this observation. Earlier I worked on the co-ordinates after removing
 * dublicates and that didn't help. All thanks to a old post in Math Exchange I
 * saw searching for a solution to my problem in the internet.
 *
 *      - 3. Actually before Populating the 4 co-ordinates in step 1. We make
 * edges from the point first.
 *
 *          The edges that occur only once are outer edges and more than once
 * means inside edges. We only keep the outer edges.
 *
 *      - 4. Lastly we pass the Edges and corners to a function named
 * 'constructPolygon' that gives us the corner points in clockwise or
 * anticlockwise manner.
 *
 *      - 5. We can try to arrange them anticlockwise by finding a mean points
 * of the cluster, transform the co-ordinates into parametric form. And arrange
 * them in ascending order of ther angle theta. But that won't work for more
 * complex shapes.
 *
 *      I arrange the corners anticlockwise if there are only 4 corners
 * (rectangle) then only it is 100% sure to work.
 *
 *      The algo 95% of the time gives anticlockwise results and only sometimes
 * doesn't work and only for small bodies of Dirt. And most small bodies of dirt
 * are rectangles. So if luck succeeds we shall not have any problem.
 *
 * Since you read through the end. Here is a cookie for you 🍪 I hope your font
 * can render it :)
 *
 *
 */

namespace Platformer
{

b2BodyId PhysicsMap::perimeterBodyId {};

bool vec2Equal(const b2Vec2 &a, const b2Vec2 &b)
{
    return a.x == b.x && a.y == b.y;
}

bool vec2Less(const b2Vec2 &a, const b2Vec2 &b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

void Platformer::PhysicsMap::init(
    const std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>,
                     Platformer::TILESET_HEIGHT> &map)
{
    initPerimeterBodyId();

    auto clusters = findClusters(map);

    std::vector<Edge> Edges;
    std::vector<b2Vec2> corners;

    for (auto points: clusters)
    {
        // Due to the co-ordinate system we have to invert Y axis of points.
        points = invertY(points);

        Edges.clear();
        // From a single point detect 4 Edges.
        Edges = findEdges(points);
        // Remove all the edges that are appearing more than once. They are
        // inner Edge. We don't need those
        Edges = getUniqueEdges(Edges);  // Edge now has outer Edges only

        // Why set? Faster lookup someone said.
        // Why now? I learned it while in the middle of making it.
        std::set<Edge> edgeSet(Edges.begin(), Edges.end());

        // From a single point make 3 more points.
        points = getSurroundingPoints(points);

        corners.clear();
        // From the points now. The points that occur odd number of times are
        // the corner points.
        corners = getOddDuplicates(points);

        // Keep the corners we will need later.
        auto ActualCorners = corners;

        // With the corners and Edges we will make a polygon. We don't know if
        // the points will be sorted clockwise or anitclockwise
        corners = constructPolygon(edgeSet, corners[1]);

        // constructPolygon function gives some useless points that are not
        // corners and we don't need them. We kept track of ActualCorners
        // earlier and will remove all the corners that are not actually
        // corners without changing the arrangement.
        removeNonCommonElements(corners, ActualCorners);

        if (corners.size() == 5)
        {  // If 4 vertices then arrange them in anticlockwise manner. If more
           // than 4 you are fucked, all you can do is pray to god that it is
           // arranged in anticlockwise manner.
            sortPointsAntiClockwise(corners);
        }

        b2ChainDef perimeterChainDef = b2DefaultChainDef();
        perimeterChainDef.isLoop     = true;

        perimeterChainDef.count  = corners.size();
        perimeterChainDef.points = corners.data();

        b2CreateChain(perimeterBodyId, &perimeterChainDef);
    }
}

void PhysicsMap::initPerimeterBodyId()
{
    b2BodyDef perimeterBodyDef = b2DefaultBodyDef();
    perimeterBodyDef.position  = (b2Vec2) {0, 0};
    perimeterBodyId = b2CreateBody(Physics::worldId, &perimeterBodyDef);
}

template<size_t WIDTH, size_t HEIGHT>
std::vector<std::vector<b2Vec2>> PhysicsMap::findClusters(
    const std::array<std::array<std::uint8_t, WIDTH>, HEIGHT> &grid)
{
    std::vector<std::vector<b2Vec2>> clusters;
    std::array<std::array<bool, WIDTH>, HEIGHT> visited {};

    auto isValid = [&](int x, int y)
    {
        return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && grid[y][x] == 2
               && !visited[y][x];
    };

    std::array<int, 4> dx = {1, -1, 0, 0};
    std::array<int, 4> dy = {0, 0, 1, -1};

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (grid[y][x] == 2 && !visited[y][x])
            {
                std::vector<b2Vec2> cluster;
                std::queue<b2Vec2> q;
                q.push({static_cast<float>(x), static_cast<float>(y)});
                visited[y][x] = true;

                while (!q.empty())
                {
                    b2Vec2 point = q.front();
                    q.pop();
                    cluster.push_back(point);

                    for (int i = 0; i < 4; ++i)
                    {
                        int nx = static_cast<int>(point.x) + dx[i];
                        int ny = static_cast<int>(point.y) + dy[i];

                        if (isValid(nx, ny))
                        {
                            visited[ny][nx] = true;
                            q.push({static_cast<float>(nx),
                                    static_cast<float>(ny)});
                        }
                    }
                }

                clusters.push_back(std::move(cluster));
            }
        }
    }

    return clusters;
}

std::vector<b2Vec2>
    PhysicsMap::getSurroundingPoints(const std::vector<b2Vec2> &points)
{
    std::vector<b2Vec2> tmp;

    for (auto i: points)
    {
        tmp.emplace_back(i);                          // Top-Left
        tmp.emplace_back(b2Vec2 {i.x + 1, i.y});      // Top-Right
        tmp.emplace_back(b2Vec2 {i.x + 1, i.y - 1});  // Bottom-Right
        tmp.emplace_back(b2Vec2 {i.x, i.y - 1});      // Bottom-Left
    }

    // Sorting
    std::sort(tmp.begin(), tmp.end(),
              [](b2Vec2 a, b2Vec2 b)
              {
                  if (a.x != b.x)
                  {
                      return a.x < b.x;
                  }
                  return a.y < b.y;
              });
    return tmp;
}

std::vector<b2Vec2>
    PhysicsMap::getOddDuplicates(const std::vector<b2Vec2> &points)
{
    std::unordered_map<b2Vec2, int, b2Vec2Hash> countMap;
    std::vector<b2Vec2> result;

    // Count occurrences of each b2Vec2
    for (const auto &point: points)
    {
        countMap[point]++;
    }

    // Collect points with odd occurrences
    for (const auto &[point, count]: countMap)
    {
        if (count % 2 != 0)
        {
            result.push_back(point);
        }
    }

    return result;
}

std::vector<Edge> PhysicsMap::findEdges(const std::vector<b2Vec2> &points)
{
    std::vector<Edge> tmp;
    for (auto point: points)
    {
        b2Vec2 p1 = {point.x, point.y};
        b2Vec2 p2 = {point.x + 1, point.y};
        tmp.emplace_back(Edge {p1, p2});  // Top-Edge

        // p1 is same
        p2 = {point.x, point.y - 1};
        tmp.emplace_back(Edge {p1, p2});  // Left-Edge

        p1 = {point.x + 1, point.y};
        p2 = {point.x + 1, point.y - 1};
        tmp.emplace_back(Edge {p1, p2});  // Right-Edge

        p1 = {point.x, point.y - 1};
        // p2 is same
        tmp.emplace_back(Edge {p1, p2});  // Bottom-Edge
    }

    return tmp;
}

std::vector<Edge> PhysicsMap::getUniqueEdges(const std::vector<Edge> &edges)
{
    std::unordered_map<Edge, int, EdgeHash> edgeCount;
    for (const Edge &edge: edges)
    {
        edgeCount[edge]++;
    }

    // Collect edges that appear only once
    std::vector<Edge> uniqueEdges;
    for (const auto &pair: edgeCount)
    {
        if (pair.second == 1)
        {
            uniqueEdges.push_back(pair.first);
        }
    }

    return uniqueEdges;
}

void PhysicsMap::removeNonCommonElements(std::vector<b2Vec2> &vec1,
                                         std::vector<b2Vec2> &vec2)
{
    std::set<b2Vec2, decltype(&vec2Less)> set2(vec2.begin(), vec2.end(),
                                               vec2Less);

    vec1.erase(std::remove_if(vec1.begin(), vec1.end(),
                              [&set2](const b2Vec2 &v)
                              {
                                  return set2.find(v) == set2.end();
                              }),
               vec1.end());

    std::set<b2Vec2, decltype(&vec2Less)> set1(vec1.begin(), vec1.end(),
                                               vec2Less);

    vec2.erase(std::remove_if(vec2.begin(), vec2.end(),
                              [&set1](const b2Vec2 &v)
                              {
                                  return set1.find(v) == set1.end();
                              }),
               vec2.end());
}

std::vector<b2Vec2> PhysicsMap::invertY(const std::vector<b2Vec2> &points)
{
    std::vector<b2Vec2> tmp;
    tmp.reserve(points.size());
    for (auto i: points)
    {
        tmp.emplace_back(b2Vec2 {i.x, TILESET_HEIGHT - i.y});
    }
    return tmp;
}

std::vector<b2Vec2>
    PhysicsMap::constructPolygon(const std::set<Edge> &outerEdges,
                                 const b2Vec2 &startCorner)
{
    std::vector<b2Vec2> polygon;
    b2Vec2 current = startCorner;

    polygon.push_back(current);
    std::set<Edge> visitedEdges;

    while (true)
    {
        bool foundNextEdge = false;

        for (const auto &edge: outerEdges)
        {
            if (visitedEdges.count(edge) > 0)
                continue;  // Skip visited edges

            b2Vec2 next;
            if (vec2Equal(edge.a, current))
            {
                next = edge.b;
            }
            else if (vec2Equal(edge.b, current))
            {
                next = edge.a;
            }
            else
            {
                continue;
            }

            // Mark edge as visited
            visitedEdges.insert(edge);

            // Move to the next corner
            current = next;
            polygon.push_back(current);
            foundNextEdge = true;
            break;
        }

        if (!foundNextEdge || vec2Equal(current, startCorner))
        {
            break;  // Completed the loop or no valid edges
        }
    }

    return polygon;
}

// This function is not used for now.
void PhysicsMap::reversePolygon(std::vector<b2Vec2> &corners)
{
    int left  = 0;
    int right = corners.size() - 1;
    while (left < right)
    {
        b2Vec2 temp    = corners[left];
        corners[left]  = corners[right];
        corners[right] = temp;

        left++;
        right--;
    }
}

b2Vec2 PhysicsMap::computeCentroid(const std::vector<b2Vec2> &points)
{
    float sumX = 0.0f, sumY = 0.0f;
    for (const auto &point: points)
    {
        sumX += point.x;
        sumY += point.y;
    }
    return {sumX / points.size(), sumY / points.size()};
}

float PhysicsMap::calculateAngle(const b2Vec2 &center, const b2Vec2 &point)
{
    // atan2 is very expensive function someone said.
    return std::atan2(point.y - center.y, point.x - center.x);
}

void PhysicsMap::sortPointsAntiClockwise(std::vector<b2Vec2> &points)
{
    b2Vec2 centroid = computeCentroid(points);

    std::sort(points.begin(), points.end(),
              [&centroid](const b2Vec2 &a, const b2Vec2 &b)
              {
                  return calculateAngle(centroid, a)
                         < calculateAngle(centroid, b);
              });
}

}  // namespace Platformer
