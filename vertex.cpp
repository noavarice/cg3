#include "vertex.h"

Vertex::Vertex(const QVector3D& position, const QVector3D& normal)
    : position{position}
    , normal{normal}
{
}

Vertex::Vertex(const QVector3D &position)
    : position{position}
{
}

Vertex::Vertex()
{
}

void Vertex::setPosition(const QVector3D& newPosition)
{
    position = newPosition;
}

void Vertex::setNormal(const QVector3D &newNormal)
{
    normal = newNormal;
}
