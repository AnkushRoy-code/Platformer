#ifndef INCLUDE_DEBUGHELP_BOX2DDEBUGDRAW_H_
#define INCLUDE_DEBUGHELP_BOX2DDEBUGDRAW_H_

#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include <GL/gl.h>
#include <cmath>

namespace Debug
{

// This class implements Box2D debug drawing callbacks
class Draw
{
public:
    Draw();
    ~Draw();

    void Create();
    void Destroy();

    void DrawPolygon(const b2Vec2 *vertices,
                     int32_t vertexCount,
                     b2HexColor color);
    void DrawSolidPolygon(b2Transform transform,
                          const b2Vec2 *vertices,
                          int32_t vertexCount,
                          float radius,
                          b2HexColor color);

    void DrawCircle(b2Vec2 center, float radius, b2HexColor color);
    void DrawSolidCircle(b2Transform transform,
                         b2Vec2 center,
                         float radius,
                         b2HexColor color);

    void DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color);

    void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color);

    void DrawTransform(b2Transform transform);

    void DrawPoint(b2Vec2 p, float size, b2HexColor color);

    void DrawString(int x, int y, const char *string, ...);

    void DrawString(b2Vec2 p, const char *string, ...);

    void DrawAABB(b2AABB aabb, b2HexColor color);

    void Flush();
    void DrawBackground();

    bool m_showUI;
    struct GLPoints *m_points;
    struct GLLines *m_lines;
    struct GLCircles *m_circles;
    struct GLSolidCircles *m_solidCircles;
    struct GLSolidCapsules *m_solidCapsules;
    struct GLSolidPolygons *m_solidPolygons;
    b2DebugDraw m_debugDraw;

};

extern Draw g_draw;
}

#endif  // INCLUDE_DEBUGHELP_BOX2DDEBUGDRAW_H_
