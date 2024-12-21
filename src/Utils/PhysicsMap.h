#ifndef INCLUDE_UTILS_PHYSICSMAP_H_
#define INCLUDE_UTILS_PHYSICSMAP_H_

#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "Utils/Constants.h"
#include <SDL_video.h>
#include <array>
#include <cstdint>
#include <set>
#include <vector>

namespace Platformer
{

bool vec2Equal(const b2Vec2 &a, const b2Vec2 &b);
bool vec2Less(const b2Vec2 &a, const b2Vec2 &b);

struct Edge
{
    b2Vec2 a;
    b2Vec2 b;

    bool operator<(const Edge &other) const
    {
        if (vec2Less(a, other.a))
        {
            return true;
        }
        if (vec2Equal(a, other.a))
        {
            return vec2Less(b, other.b);
        }
        return false;
    }

    bool operator==(const Edge &other) const
    {
        return (vec2Equal(a, other.a) && vec2Equal(b, other.b))
               || (vec2Equal(a, other.b) && vec2Equal(b, other.a));
    }
};

struct b2Vec2Hash
{
    std::size_t operator()(const b2Vec2 &v) const
    {
        std::hash<float> hashFn;
        return hashFn(v.x) ^ (hashFn(v.y) << 1);
    }
};

struct EdgeHash
{
    std::size_t operator()(const Edge &edge) const
    {
        return std::hash<float>()(edge.a.x) ^ std::hash<float>()(edge.a.y)
               ^ std::hash<float>()(edge.b.x) ^ std::hash<float>()(edge.b.y);
    }
};

class PhysicsMap
{
public:
    static void init(
        const std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>,
                         Platformer::TILESET_HEIGHT> &map);

private:
    static void initPerimeterBodyId();

    /// Get different clusters of physics tiles
    template<size_t WIDTH, size_t HEIGHT>
    static std::vector<std::vector<b2Vec2>> findClusters(
        const std::array<std::array<std::uint8_t, WIDTH>, HEIGHT> &grid);

    /// From one point generate 4 points (square) look at PhysicsMap.cpp
    static std::vector<b2Vec2>
        getSurroundingPoints(const std::vector<b2Vec2> &points);

    /// look at PhysicsMap.cpp Explained it there IDK why. Here would've been a
    /// better place right?
    static std::vector<b2Vec2>
        getOddDuplicates(const std::vector<b2Vec2> &points);

    /// Find 4 Edges from one point PhysicsMap.cpp has it explained.
    static std::vector<Edge> findEdges(const std::vector<b2Vec2> &points);

    /// Remove Edges that occur more than once
    static std::vector<Edge> getUniqueEdges(const std::vector<Edge> &edges);

    /// Remove points that are not common in both the vec.
    static void removeNonCommonElements(std::vector<b2Vec2> &vec1,
                                        std::vector<b2Vec2> &vec2);


    /// Invert the Y axis :)
    static std::vector<b2Vec2> invertY(const std::vector<b2Vec2> &points);

    /// Provides us with the points arranged to make a polygon.
    static std::vector<b2Vec2>
        constructPolygon(const std::set<Edge> &outerEdges,
                         const b2Vec2 &startCorner);

    /// Not used now. IDK may be removed later
    static void reversePolygon(std::vector<b2Vec2> &corners);


    static b2Vec2 computeCentroid(const std::vector<b2Vec2> &points);
    static float calculateAngle(const b2Vec2 &center, const b2Vec2 &point);
    static void sortPointsAntiClockwise(std::vector<b2Vec2> &points);

private:
    static b2BodyId perimeterBodyId;
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_PHYSICSMAP_H_
