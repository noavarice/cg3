#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

class QOpenGLShaderProgram;

class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions
{
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

public slots:
    void drawCone(float height, float radius);

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;

    float height;
    float radius;
};

#endif // OPENGLWIDGET_H
