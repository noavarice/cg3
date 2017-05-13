#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex
{
public:
    Vertex(const QVector3D& position, const QVector3D& color);
    explicit Vertex(const QVector3D &position);

    Q_DECL_CONSTEXPR static size_t positionOffset();
    Q_DECL_CONSTEXPR static size_t colorOffset();
    Q_DECL_CONSTEXPR static size_t stride();

    void setColor(const QVector3D& newColor);
    void setPosition(const QVector3D& newPosition);

private:
    QVector3D position;
    QVector3D color;
};

#endif // VERTEX_H