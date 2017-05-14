#include "vertex.h"

Vertex::Vertex(const QVector3D& position, const QVector3D& color)
    : position{position}
    , color{color}
{
}

Vertex::Vertex(const QVector3D &position)
    : position{position}
    , color{0.0f, 0.0f, 0.0f}
{
}

Vertex::Vertex()
    : position{}
    , color{}
{
}

void Vertex::setColor(const QVector3D& newColor)
{
    color = newColor;
}

void Vertex::setPosition(const QVector3D& newPosition)
{
    position = newPosition;
}
