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

        b2ChainDef perimeterChainDef = b2DefaultChainDef();
        perimeterChainDef.isLoop     = true;

        perimeterChainDef.count  = corners.size();
        perimeterChainDef.points = corners.data();

        b2CreateChain(perimeterBodyId, &perimeterChainDef);
    }
}

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
void PhysicsMap::initPerimeterBodyId()
{
    b2BodyDef perimeterBodyDef = b2DefaultBodyDef();
    perimeterBodyDef.position  = (b2Vec2) {0, 0};
    perimeterBodyId = b2CreateBody(Physics::worldId, &perimeterBodyDef);
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

}  // namespace Platformer
