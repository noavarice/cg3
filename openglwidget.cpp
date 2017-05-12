#include "openglwidget.h"

#include <QOpenGLShaderProgram>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    shaderProgram->link();
    shaderProgram->bind();

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);

    vertexArrayObject.create();
    vertexArrayObject.bind();

    vertexBuffer.release();
    vertexArrayObject.release();
    shaderProgram->release();
}

void OpenGLWidget::resizeGL(int width, int height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
}

void OpenGLWidget::paintGL()
{
}
