// SPDX-FileCopyrightText: 2023 Erin Catto
// SPDX-License-Identifier: MIT

#include "box2dDebugDraw.h"

#include <vector>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <vector>

#if defined(_WIN32)
#    define _CRTDBG_MAP_ALLOC
#    include <crtdbg.h>
#    include <stdlib.h>
#else
#    include <cstdlib>
#endif

#define GLEW_STATIC
#include <GL/glew.h>

struct RGBA8
{
    uint8_t r, g, b, a;
};

static inline RGBA8 MakeRGBA8(b2HexColor c, float alpha)
{
    return {uint8_t((c >> 16) & 0xFF), uint8_t((c >> 8) & 0xFF),
            uint8_t(c & 0xFF), uint8_t(0xFF * alpha)};
}

namespace Debug
{

Draw g_draw;

struct PointData
{
    b2Vec2 position;
    float size;
    RGBA8 rgba;
};

struct GLPoints
{
    void AddPoint(b2Vec2 v, float size, b2HexColor c)
    {
        RGBA8 rgba = MakeRGBA8(c, 1.0f);
        m_points.push_back({v, size, rgba});
    }

    void Flush()
    {
        int count = (int)m_points.size();
        if (count == 0)
        {
            return;
        }
        for (int i = 0; i < count; i++)
        {
            RGBA8 c = m_points[i].rgba;
            glColor3f(c.r, c.g, c.b);

            glPointSize(m_points[i].size);

            // Draw the point
            glBegin(GL_POINTS);
            b2Vec2 p = m_points[i].position;
            glVertex2f(p.x, p.y);
            glEnd();
        }

        m_points.clear();
    }

    std::vector<PointData> m_points;
};

struct VertexData
{
    b2Vec2 position;
    RGBA8 rgba;
};

struct GLLines
{
    void AddLine(b2Vec2 p1, b2Vec2 p2, b2HexColor c)
    {
        RGBA8 rgba = MakeRGBA8(c, 1.0f);
        m_points.push_back({p1, rgba});
        m_points.push_back({p2, rgba});
    }

    void Flush()
    {
        int count = (int)m_points.size();
        if (count == 0)
        {
            return;
        }

        assert(count % 2 == 0);

        for (int i = 0; i < count; i += 2)
        {
            RGBA8 c = m_points[i].rgba;
            glColor3f(c.r, c.g, c.b);

            b2Vec2 p1 = m_points[i].position;
            b2Vec2 p2 = m_points[i + 1].position;

            glBegin(GL_LINES);
            glVertex2f(p1.x, p1.y);
            glVertex2f(p2.x, p2.y);
            glEnd();
        }

        m_points.clear();
    }
    std::vector<VertexData> m_points;
};

struct CircleData
{
    b2Vec2 position;
    float radius;
    RGBA8 rgba;
};

struct GLCircles
{
    void AddCircle(b2Vec2 center, float radius, b2HexColor color)
    {
        RGBA8 rgba = MakeRGBA8(color, 1.0f);
        m_circles.push_back({center, radius, rgba});
    }

    void Flush()
    {
        int count = (int)m_circles.size();
        if (count == 0)
        {
            return;
        }

        for (int i = 0; i < count; i++)
        {
            RGBA8 c = m_circles[i].rgba;
            glColor3f(c.r, c.g, c.b);

            b2Vec2 center = m_circles[i].position;
            float radius  = m_circles[i].radius;

            glBegin(GL_LINE_LOOP);
            const int segments = 32;
            for (int i = 0; i < segments; ++i)
            {
                float theta = 2.0f * M_PI * i / segments;
                glVertex2f(center.x + radius * cosf(theta),
                           center.y + radius * sinf(theta));
            }
            glEnd();
        }

        m_circles.clear();
    }

    std::vector<CircleData> m_circles;
};

struct SolidCircleData
{
    b2Transform transform;
    float radius;
    RGBA8 rgba;
};

struct GLSolidCircles
{

    void AddCircle(const b2Transform &transform, float radius, b2HexColor color)
    {
        RGBA8 rgba = MakeRGBA8(color, 1.0f);
        m_circles.push_back(
            {{{transform.p.x, transform.p.y}, {transform.q.c, transform.q.s}},
             radius,
             rgba});
    }

    void Flush()
    {
        int count = (int)m_circles.size();
        if (count == 0)
        {
            return;
        }

        for (int i = 0; i < count; i++)
        {
            RGBA8 c = m_circles[i].rgba;
            glColor3f(c.r, c.g, c.b);

            b2Transform transform = m_circles[i].transform;
            float radius          = m_circles[i].radius;

            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < 32; ++i)
            {
                float theta = 2.0f * M_PI * i / 32;
                glVertex2f(transform.p.x + radius * cosf(theta),
                           transform.p.y + radius * sinf(theta));
            }
            glEnd();
        }

        m_circles.clear();
    }

    std::vector<SolidCircleData> m_circles;
};

struct CapsuleData
{
    b2Vec2 p1;
    b2Vec2 p2;
    float radius;
    RGBA8 rgba;
};

// Draw capsules using SDF-based shader
struct GLSolidCapsules
{
    void AddCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor c)
    {
        RGBA8 rgba = MakeRGBA8(c, 1.0f);
        m_capsules.push_back({p1, p2, radius, rgba});
    }

    void Flush()
    {
        int count = (int)m_capsules.size();
        if (count == 0)
        {
            return;
        }

        for (int i = 0; i < count; i++)
        {
            RGBA8 c = m_capsules[i].rgba;
            glColor3f(c.r, c.g, c.b);

            b2Vec2 p1    = m_capsules[i].p1;
            b2Vec2 p2    = m_capsules[i].p2;
            float radius = m_capsules[i].radius;

            const int segments = 16;  // Number of segments per semicircle
            float dx           = p2.x - p1.x;  // Capsule axis delta x
            float dy           = p2.y - p1.y;  // Capsule axis delta y
            // float length       = sqrtf(dx * dx + dy * dy);
            float angle = atan2f(dy, dx);

            // Step 1: Draw rectangle body
            glBegin(GL_QUADS);
            float sinA = sinf(angle), cosA = cosf(angle);
            float offsetX = radius * sinA, offsetY = radius * cosA;

            glVertex2f(p1.x - offsetX, p1.y + offsetY);
            glVertex2f(p1.x + offsetX, p1.y - offsetY);
            glVertex2f(p2.x + offsetX, p2.y - offsetY);
            glVertex2f(p2.x - offsetX, p2.y + offsetY);
            glEnd();

            // Step 2: Draw semicircle at p1
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(p1.x, p1.y);
            for (int i = 0; i <= segments; ++i)
            {
                float theta = angle + M_PI / 2 + M_PI * i / segments;
                glVertex2f(p1.x + radius * cosf(theta),
                           p1.y + radius * sinf(theta));
            }
            glEnd();

            // Step 3: Draw semicircle at p2
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(p2.x, p2.y);
            for (int i = 0; i <= segments; ++i)
            {
                float theta = angle - M_PI / 2 - M_PI * i / segments;
                glVertex2f(p2.x + radius * cosf(theta),
                           p2.y + radius * sinf(theta));
            }
            glEnd();
        }

        m_capsules.clear();
    }

    std::vector<CapsuleData> m_capsules;
};

struct PolygonData
{
    b2Transform transform;
    b2Vec2 p1, p2, p3, p4, p5, p6, p7, p8;
    int count;
    float radius;

    // keep color small
    RGBA8 color;
};

// Rounded and non-rounded convex polygons using an SDF-based shader.
struct GLSolidPolygons
{
    void AddPolygon(const b2Transform &transform,
                    const b2Vec2 *points,
                    int count,
                    float radius,
                    b2HexColor color)
    {
        PolygonData data = {};
        data.transform   = transform;

        int n      = count < 8 ? count : 8;
        b2Vec2 *ps = &data.p1;
        for (int i = 0; i < n; ++i)
        {
            ps[i] = points[i];
        }

        data.count  = n;
        data.radius = radius;
        data.color  = MakeRGBA8(color, 1.0f);

        m_polygons.push_back(data);
    }

    void Flush()
    {
        int count = (int)m_polygons.size();
        if (count == 0)
        {
            return;
        }

        for (int i = 0; i < count; i++)
        {
            RGBA8 c = m_polygons[i].color;
            glColor3f(c.r, c.g, c.b);

            glBegin(GL_TRIANGLE_FAN);

            b2Vec2 vertices[8] = {m_polygons[i].p1, m_polygons[i].p2,
                                  m_polygons[i].p3, m_polygons[i].p4,
                                  m_polygons[i].p5, m_polygons[i].p6,
                                  m_polygons[i].p7, m_polygons[i].p8};

            int vertexCount = m_polygons[i].count;
            for (int i = 0; i < vertexCount; ++i)
            {
                glVertex2f(vertices[i].x, vertices[i].y);
            }
            glEnd();
        }

        m_polygons.clear();
    }

    std::vector<PolygonData> m_polygons;
};

void DrawPolygonFcn(const b2Vec2 *vertices,
                    int vertexCount,
                    b2HexColor color,
                    void *context)
{
    static_cast<Draw *>(context)->DrawPolygon(vertices, vertexCount, color);
}

void DrawSolidPolygonFcn(b2Transform transform,
                         const b2Vec2 *vertices,
                         int vertexCount,
                         float radius,
                         b2HexColor color,
                         void *context)
{
    static_cast<Draw *>(context)->DrawSolidPolygon(transform, vertices,
                                                   vertexCount, radius, color);
}

void DrawCircleFcn(b2Vec2 center, float radius, b2HexColor color, void *context)
{
    static_cast<Draw *>(context)->DrawCircle(center, radius, color);
}

void DrawSolidCircleFcn(b2Transform transform,
                        float radius,
                        b2HexColor color,
                        void *context)
{
    static_cast<Draw *>(context)->DrawSolidCircle(transform, b2Vec2_zero,
                                                  radius, color);
}

void DrawSolidCapsuleFcn(
    b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void *context)
{
    static_cast<Draw *>(context)->DrawSolidCapsule(p1, p2, radius, color);
}

void DrawSegmentFcn(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void *context)
{
    static_cast<Draw *>(context)->DrawSegment(p1, p2, color);
}

void DrawTransformFcn(b2Transform transform, void *context)
{
    static_cast<Draw *>(context)->DrawTransform(transform);
}

void DrawPointFcn(b2Vec2 p, float size, b2HexColor color, void *context)
{
    static_cast<Draw *>(context)->DrawPoint(p, size, color);
}

void DrawStringFcn(b2Vec2 p, const char *s, void *context)
{
    static_cast<Draw *>(context)->DrawString(p, s);
}

Draw::Draw()
{
    m_showUI        = true;
    m_points        = nullptr;
    m_lines         = nullptr;
    m_circles       = nullptr;
    m_solidCircles  = nullptr;
    m_solidCapsules = nullptr;
    m_solidPolygons = nullptr;
    m_debugDraw     = {};
}

Draw::~Draw()
{
    assert(m_points == nullptr);
    assert(m_lines == nullptr);
    assert(m_circles == nullptr);
    assert(m_solidCircles == nullptr);
    assert(m_solidCapsules == nullptr);
    assert(m_solidPolygons == nullptr);
}

void Draw::Create()
{
    m_points        = new GLPoints;
    m_lines         = new GLLines;
    m_circles       = new GLCircles;
    m_solidCircles  = new GLSolidCircles;
    m_solidCapsules = new GLSolidCapsules;
    m_solidPolygons = new GLSolidPolygons;

    b2AABB bounds = {{0, 0}, {32, 18}};

    m_debugDraw = {DrawPolygonFcn,
                   DrawSolidPolygonFcn,
                   DrawCircleFcn,
                   DrawSolidCircleFcn,
                   DrawSolidCapsuleFcn,
                   DrawSegmentFcn,
                   DrawTransformFcn,
                   DrawPointFcn,
                   DrawStringFcn,
                   bounds,
                   false,  // drawUsingBounds
                   true,   // shapes
                   true,   // joints
                   false,  // joint extras
                   false,  // aabbs
                   false,  // mass
                   false,  // contacts
                   false,  // colors
                   false,  // normals
                   false,  // impulse
                   false,  // friction
                   this};
}

void Draw::Destroy()
{
    delete m_points;
    m_points = nullptr;

    delete m_lines;
    m_lines = nullptr;

    delete m_circles;
    m_circles = nullptr;

    delete m_solidCircles;
    m_solidCircles = nullptr;

    delete m_solidCapsules;
    m_solidCapsules = nullptr;

    delete m_solidPolygons;
    m_solidPolygons = nullptr;
}

void Draw::DrawPolygon(const b2Vec2 *vertices,
                       int vertexCount,
                       b2HexColor color)
{
    b2Vec2 p1 = vertices[vertexCount - 1];
    for (int i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p2 = vertices[i];
        m_lines->AddLine(p1, p2, color);
        p1 = p2;
    }
}

void Draw::DrawSolidPolygon(b2Transform transform,
                            const b2Vec2 *vertices,
                            int vertexCount,
                            float radius,
                            b2HexColor color)
{
    m_solidPolygons->AddPolygon(transform, vertices, vertexCount, radius,
                                color);
}

void Draw::DrawCircle(b2Vec2 center, float radius, b2HexColor color)
{
    m_circles->AddCircle(center, radius, color);
}

void Draw::DrawSolidCircle(b2Transform transform,
                           b2Vec2 center,
                           float radius,
                           b2HexColor color)
{
    transform.p = b2TransformPoint(transform, center);
    m_solidCircles->AddCircle(transform, radius, color);
}

void Draw::DrawSolidCapsule(b2Vec2 p1,
                            b2Vec2 p2,
                            float radius,
                            b2HexColor color)
{
    m_solidCapsules->AddCapsule(p1, p2, radius, color);
}

void Draw::DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color)
{
    m_lines->AddLine(p1, p2, color);
}

void Draw::DrawTransform(b2Transform transform)
{
    const float k_axisScale = 0.2f;
    b2Vec2 p1               = transform.p;

    b2Vec2 p2 = b2MulAdd(p1, k_axisScale, b2Rot_GetXAxis(transform.q));
    m_lines->AddLine(p1, p2, b2_colorRed);

    p2 = b2MulAdd(p1, k_axisScale, b2Rot_GetYAxis(transform.q));
    m_lines->AddLine(p1, p2, b2_colorGreen);
}

void Draw::DrawPoint(b2Vec2 p, float size, b2HexColor color)
{
    m_points->AddPoint(p, size, color);
}

void Draw::DrawString(int x, int y, const char *string, ...)
{
    // if (m_showUI == false)
    //{
    //	return;
    // }

    // HAHAHAHA you
}

void Draw::DrawString(b2Vec2 p, const char *string, ...)
{
    // HHAHAHA yu again
}

void Draw::DrawAABB(b2AABB aabb, b2HexColor c)
{
    b2Vec2 p1 = aabb.lowerBound;
    b2Vec2 p2 = {aabb.upperBound.x, aabb.lowerBound.y};
    b2Vec2 p3 = aabb.upperBound;
    b2Vec2 p4 = {aabb.lowerBound.x, aabb.upperBound.y};

    m_lines->AddLine(p1, p2, c);
    m_lines->AddLine(p2, p3, c);
    m_lines->AddLine(p3, p4, c);
    m_lines->AddLine(p4, p1, c);
}

void Draw::Flush()
{
    m_solidCircles->Flush();
    m_solidCapsules->Flush();
    m_solidPolygons->Flush();
    m_circles->Flush();
    m_lines->Flush();
    m_points->Flush();
}

void Draw::DrawBackground() {}

}  // namespace Debug
