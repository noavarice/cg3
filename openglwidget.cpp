#include "openglwidget.h"

#include "conecoordsgen.h"
#include "vertex.h"

#include <QOpenGLShaderProgram>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , height{1.0f}
    , radius{1.0f}
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
    shaderProgram->enableAttributeArray(0);
    shaderProgram->enableAttributeArray(1);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, Vertex::stride());
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, Vertex::colorOffset(), 3, Vertex::stride());
    shaderProgram->release();

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.release();

    vertexArrayObject.create();
}

void OpenGLWidget::drawCone(float height, float radius)
{
    this->height = height;
    this->radius = radius;
    update();
}

void OpenGLWidget::paintGL()
{
    QVector3D vertices[720];
    generateConeCoords(vertices, height, radius);
    glClear(GL_COLOR_BUFFER_BIT);
    vertexBuffer.bind();
    {
        vertexArrayObject.bind();
        glDrawArrays(GL_TRIANGLES, 0, 720);
        vertexArrayObject.release();
    }
    vertexBuffer.release();
}
