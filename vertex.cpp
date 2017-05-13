#include "vertex.h"

Vertex::Vertex(const QVector3D& position, const QVector3D& color)
    : position{position}
    , color{color}
{
}

Vertex::Vertex(const QVector3D &position)
    : position{position}
    , color{}
{
}

Q_DECL_CONSTEXPR size_t Vertex::positionOffset()
{
    return offsetof(Vertex, position);
}

Q_DECL_CONSTEXPR size_t Vertex::colorOffset()
{
    return offsetof(Vertex, color);
}

Q_DECL_CONSTEXPR size_t Vertex::stride()
{
    return sizeof(Vertex);
}

void Vertex::setColor(const QVector3D& newColor)
{
    color = newColor;
}

void Vertex::setPosition(const QVector3D& newPosition)
{
    position = newPosition;
}
