#ifndef VERTEX_H
#define VERTEX_H

#include <QVector2D>
#include <QVector3D>

class Vertex
{
public:
    Vertex();
    explicit Vertex(const QVector3D &position);
    Vertex(const QVector3D& position, const QVector3D& normal, const QVector2D& textureCoords);

    Q_DECL_CONSTEXPR static size_t positionOffset()
    {
        return offsetof(Vertex, position);
    }

    Q_DECL_CONSTEXPR static size_t normalOffset()
    {
        return offsetof(Vertex, normal);
    }

    Q_DECL_CONSTEXPR static size_t textureCoordsOffset()
    {
        return offsetof(Vertex, texCoords);
    }

    Q_DECL_CONSTEXPR static size_t stride()
    {
        return sizeof(Vertex);
    }

private:
    QVector3D position;
    QVector3D normal;
    QVector2D texCoords;
};

#endif // VERTEX_H
