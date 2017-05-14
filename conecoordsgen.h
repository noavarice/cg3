#ifndef CONECOORDSGEN_H
#define CONECOORDSGEN_H

#define OUT

class Vertex;

void generateConeCoords(
        OUT Vertex* coords,
        float height,
        float radius
        );

#endif // CONECOORDSGEN_H
