#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "vertex.h"

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

class QOpenGLShaderProgram;

class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

    void setFirstLightSourcePosition(const QVector3D& position);
    void setFirstLightSourceColor(const QVector3D& color);
    void setSecondLightSourcePosition(const QVector3D& position);
    void setSecondLightSourceColor(const QVector3D& color);
    void setCameraPosition(const QVector3D& newPosition);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;

    float height;
    float radius;
    Vertex vertices[2160];

    QPair<QVector3D, QVector3D> source1;
    QPair<QVector3D, QVector3D> source2;

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    QPoint lastMousePosition;
    bool isDefaultMousePosition;
};

#endif // OPENGLWIDGET_H
