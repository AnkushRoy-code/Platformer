#include "PhysicsMap.h"
#include "Platformer/Physics.h"
#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "utils/constants.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

namespace Platformer
{
b2BodyId PhysicsMap::perimeterBodyId {};

struct b2Vec2Hash
{
    std::size_t operator()(const b2Vec2 &v) const
    {
        std::hash<float> hashFn;
        return hashFn(v.x) ^ (hashFn(v.y) << 1);
    }
};

b2Vec2 computeCentroid(const std::vector<b2Vec2>& points) {
    float sumX = 0.0f, sumY = 0.0f;
    for (const auto& point : points) {
        sumX += point.x;
        sumY += point.y;
    }
    return {sumX / points.size(), sumY / points.size()};
}

float calculateAngle(const b2Vec2& center, const b2Vec2& point) {
    return std::atan2(point.y - center.y, point.x - center.x);
}

void sortPointsAntiClockwise(std::vector<b2Vec2>& points) {
    b2Vec2 centroid = computeCentroid(points);

    std::sort(points.begin(), points.end(), [&centroid](const b2Vec2& a, const b2Vec2& b) {
        return calculateAngle(centroid, a) < calculateAngle(centroid, b);
    });
}

std::vector<b2Vec2> invertY(const std::vector<b2Vec2> &points)
{
    std::vector<b2Vec2> tmp;
    tmp.reserve(points.size());
    for (auto i: points)
    {
        tmp.emplace_back(b2Vec2 {i.x, TILESET_HEIGHT - i.y});
    }
    return tmp;
}

void Platformer::PhysicsMap::init(
    const std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>,
                     Platformer::TILESET_HEIGHT> &map)
{
    initPerimeterBodyId();

    auto clusters = findClusters(map);

    for (size_t i = 0; i < clusters.size(); ++i)
    {
        std::cout << "Cluster " << i + 1 << ":\n";
        for (const auto &point: clusters[i])
        {
            std::cout << "(" << point.x << ", " << point.y << ") ";
        }
        std::cout << '\n';
    }

    for (auto points: clusters)
    {
        points = invertY(points);
        b2ChainDef perimeterChainDef = b2DefaultChainDef();
        perimeterChainDef.isLoop     = true;

        points = getSurroundingPoints(points);
        points = getOddDuplicates(points);

        sortPointsAntiClockwise(points);

        perimeterChainDef.count  = points.size();
        perimeterChainDef.points = points.data();

        b2CreateChain(perimeterBodyId, &perimeterChainDef);
    }
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
