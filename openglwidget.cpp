#include "openglwidget.h"

#include "conecoordsgen.h"
#include "vertex.h"

#include <QOpenGLShaderProgram>

static Vertex vertices[2160];

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , height{1.0f}
    , radius{1.0f}
{
}

OpenGLWidget::~OpenGLWidget()
{
    vertexArrayObject.destroy();
    vertexBuffer.destroy();
    delete shaderProgram;
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
    vertexBuffer.allocate(sizeof(vertices));

    vertexArrayObject.create();
    vertexArrayObject.bind();
    shaderProgram->enableAttributeArray(0);
    shaderProgram->enableAttributeArray(1);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, Vertex::stride());
    shaderProgram->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), 3, Vertex::stride());

    vertexArrayObject.release();
    vertexBuffer.release();
    shaderProgram->release();
}

void OpenGLWidget::drawCone(float height, float radius)
{
    this->height = height;
    this->radius = radius;
    update();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    generateConeCoords(vertices, height, radius);
    shaderProgram->bind();
    {
        vertexBuffer.bind();
        vertexBuffer.write(0, vertices, sizeof(vertices));
        vertexBuffer.release();

        vertexArrayObject.bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(Vertex));
        vertexArrayObject.release();
    }
    shaderProgram->release();
}
