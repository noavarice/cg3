#ifndef CONECOORDSGEN_H
#define CONECOORDSGEN_H

#define OUT

class QVector3D;

static constexpr short CIRCLE_POINTS_COUNT = 360;

void generateConeCoords(
        OUT QVector3D coords[CIRCLE_POINTS_COUNT * 2],
        float height,
        float radius
        );

#endif // CONECOORDSGEN_H
