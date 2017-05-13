#ifndef CONECOORDSGEN_H
#define CONECOORDSGEN_H

#define OUT

#include <memory>

class QVector3D;

std::unique_ptr<QVector3D[]> generateConeCoords(
        float height,
        float radius
        );

#endif // CONECOORDSGEN_H
