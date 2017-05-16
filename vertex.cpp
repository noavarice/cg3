#include "vertex.h"

Vertex::Vertex(const QVector3D& position, const QVector3D& normal, const QVector2D& textureCoords)
    : position{position}
    , normal{normal}
    , texCoords{textureCoords}
{
}

Vertex::Vertex(const QVector3D &position)
    : position{position}
{
}

Vertex::Vertex()
{
}
