#include "openglwidget.h"

#include "conecoordsgen.h"
#include "vertex.h"

#include <QOpenGLShaderProgram>

static Vertex vertices[2160];
static QMatrix4x4 model{}, view{}, projection{};

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , height{1.0f}
    , radius{1.0f}
{
}

OpenGLWidget::~OpenGLWidget()
{
    vertexArrayObject.release();
    vertexArrayObject.destroy();
    vertexBuffer.release();
    vertexBuffer.destroy();
    delete shaderProgram;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_LIGHTING);

    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    shaderProgram->link();
    shaderProgram->bind();

    model.setToIdentity();
    view.lookAt({4.0f, 5.0f, 3.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f});
    projection.perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(sizeof(vertices));

    vertexArrayObject.create();
    vertexArrayObject.bind();
    shaderProgram->enableAttributeArray(0);
    shaderProgram->enableAttributeArray(1);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), 3, Vertex::stride());
    shaderProgram->setAttributeBuffer(1, GL_FLOAT, Vertex::normalOffset(), 3, Vertex::stride());

    GLuint shaderProgramId = shaderProgram->programId();
    int lightPosLoc = glGetUniformLocation(shaderProgramId, "lightPosition");
    glUniform3f(lightPosLoc, -1.0f, 5.0f, 3.0f);
    GLint objectColorLoc = glGetUniformLocation(shaderProgramId, "objectColor");
    GLint lightColorLoc  = glGetUniformLocation(shaderProgramId, "lightColor");
    glUniform3f(objectColorLoc, 0.0f, 0.5f, 0.31f);
    glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);
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
    vertexBuffer.write(0, vertices, sizeof(vertices));
    shaderProgram->setUniformValue("model", model);
    shaderProgram->setUniformValue("view", view);
    shaderProgram->setUniformValue("projection", projection);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(Vertex));
}
