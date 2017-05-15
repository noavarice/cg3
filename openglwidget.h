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

public slots:
    void drawCone(float height, float radius);

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

    using LightPropeties = QPair<QVector3D, QVector3D>;
    QList<LightPropeties> lightPositions;

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;
};

#endif // OPENGLWIDGET_H
