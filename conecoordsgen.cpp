#include "conecoordsgen.h"

#include "vertex.h"

#define _USE_MATH_DEFINES
#include <cmath>

static constexpr QVector3D START_POINT{0.0f, 0.0f, 0.0f};
static constexpr short CIRCLE_POINTS_COUNT = 360;
static constexpr float RADIAN_PART = 2 * M_PI / CIRCLE_POINTS_COUNT;

void generateConeCoords(
        OUT Vertex* resultArray,
        float height,
        float radius
        )
{
    float currentAngle = 0.0f;
    QVector3D currentPoint;
    QVector3D coneTop{0.0f, 0.0f, height};
    for (short i = 0; i < CIRCLE_POINTS_COUNT; ++i) {
        resultArray[i * 3] = Vertex(START_POINT);
        resultArray[(i + CIRCLE_POINTS_COUNT) * 3] = Vertex(coneTop);

        currentPoint = QVector3D(cos(currentAngle) * radius, sin(currentAngle) * radius, 0.0f);
        resultArray[i * 3 + 1] = resultArray[(i + CIRCLE_POINTS_COUNT) * 3 + 1] = Vertex(currentPoint);

        currentAngle += RADIAN_PART;

        currentPoint = QVector3D(cos(currentAngle) * radius, sin(currentAngle) * radius, 0.0f);
        resultArray[i * 3 + 2] = resultArray[(i + CIRCLE_POINTS_COUNT) * 3 + 2] = Vertex(currentPoint);
    }
}
