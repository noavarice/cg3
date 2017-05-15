#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex
{
public:
    Vertex();
    explicit Vertex(const QVector3D &position);
    Vertex(const QVector3D& position, const QVector3D& normal);

    Q_DECL_CONSTEXPR static size_t positionOffset()
    {
        return offsetof(Vertex, position);
    }

    Q_DECL_CONSTEXPR static size_t normalOffset()
    {
        return offsetof(Vertex, normal);
    }

    Q_DECL_CONSTEXPR static size_t stride()
    {
        return sizeof(Vertex);
    }

    void setNormal(const QVector3D& newNormal);
    void setPosition(const QVector3D& newPosition);

private:
    QVector3D position;
    QVector3D normal;
};

#endif // VERTEX_H
