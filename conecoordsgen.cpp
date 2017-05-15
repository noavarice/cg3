#include "conecoordsgen.h"

#include "vertex.h"

#include <QPair>

#define _USE_MATH_DEFINES
#include <cmath>

static constexpr QVector3D START_POINT{0.0f, 0.0f, 0.0f};
static constexpr short CIRCLE_POINTS_COUNT = 360;
static constexpr float RADIAN_PART = 2 * M_PI / CIRCLE_POINTS_COUNT;

static QVector3D getNormalVector(
        const QVector3D& p1,
        const QVector3D& p2,
        const QVector3D& p3
        )
{
    QVector3D u = p2 - p1;
    QVector3D v = p3 - p1;
    return {
        u.y() * v.z() - u.z() * v.y(),
        u.z() * v.x() - u.x() * v.z(),
        u.x() * v.y() - u.y() * v.x(),
    };
}

static QVector3D getVectorFromAngleAndRadius(float angle, float radius)
{
    return QVector3D(cos(angle) * radius, sin(angle) * radius, 0.0f);
}

void generateConeCoords(
        OUT Vertex* resultArray,
        float height,
        float radius
        )
{
    QPair<QVector3D, QVector3D> vertexPair;
    QPair<QVector3D, QVector3D> normalPair;
    float currentAngle = 0.0f;
    QVector3D coneTop{0.0f, 0.0f, height};
    for (short i = 0; i < CIRCLE_POINTS_COUNT; ++i) {
        vertexPair.first = getVectorFromAngleAndRadius(currentAngle, radius);
        currentAngle += RADIAN_PART;
        vertexPair.second = getVectorFromAngleAndRadius(currentAngle, radius);

        normalPair.first = getNormalVector(START_POINT, vertexPair.first, vertexPair.second);
        normalPair.first = getNormalVector(coneTop, vertexPair.first, vertexPair.second);
        resultArray[i * 3] = Vertex(START_POINT, normalPair.first);
        resultArray[(i + CIRCLE_POINTS_COUNT) * 3] = Vertex(coneTop, normalPair.second);

        resultArray[i * 3 + 1] = resultArray[(i + CIRCLE_POINTS_COUNT) * 3 + 1] = Vertex(vertexPair.first, normalPair.first);
        resultArray[i * 3 + 2] = resultArray[(i + CIRCLE_POINTS_COUNT) * 3 + 2] = Vertex(vertexPair.second, normalPair.second);
    }
}
