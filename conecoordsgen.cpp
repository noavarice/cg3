#include "conecoordsgen.h"

#include <QVector3D>

#define _USE_MATH_DEFINES
#include <cmath>

static const QVector3D START_POINT{0.0f, 0.0f, 0.0f};
static const short CIRCLE_POINTS_COUNT = 360;
static const float RADIAN_PART = 2 * M_PI / CIRCLE_POINTS_COUNT;

QVector3D* generateConeCoords(
        float height,
        float radius
        )
{
    QVector3D* resultArray = new QVector3D[CIRCLE_POINTS_COUNT * 2];
    float currentAngle = 0.0f;
    QVector3D currentPoint;
    QVector3D coneTop{0.0f, 0.0f, height};
    for (short i = 0; i < CIRCLE_POINTS_COUNT; ++i) {
        resultArray[i] = START_POINT;
        resultArray[i + CIRCLE_POINTS_COUNT] = coneTop;

        currentPoint = QVector3D(cos(currentAngle) * radius, sin(currentAngle) * radius, 0.0f);
        resultArray[i + 1] = resultArray[i + CIRCLE_POINTS_COUNT + 1] = currentPoint;

        currentAngle += RADIAN_PART;

        currentPoint = QVector3D(cos(currentAngle) * radius, sin(currentAngle) * radius, 0.0f);
        resultArray[i + 2] = resultArray[i + CIRCLE_POINTS_COUNT + 2] = currentPoint;
    }
    return resultArray;
}
