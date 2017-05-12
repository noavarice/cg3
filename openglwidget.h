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

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private:
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;
};

#endif // OPENGLWIDGET_H
