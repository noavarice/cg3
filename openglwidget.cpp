#include "openglwidget.h"

#include "conecoordsgen.h"

#include <QOpenGLShaderProgram>

enum AttributeBuffer
{
    VERTEX_POSITION,
    NORMAL_VECTOR
};

static const uint8_t MAX_LIGHT_SOURCES_COUNT = 5;

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , height{1.0f}
    , radius{1.0f}
    , model{}
    , view{}
    , projection{}
{
    model.setToIdentity();
    view.lookAt({4.0f, 5.0f, 3.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f});
    projection.perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
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
    glEnable(GL_CULL_FACE);

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
    shaderProgram->enableAttributeArray(VERTEX_POSITION);
    shaderProgram->enableAttributeArray(NORMAL_VECTOR);
    shaderProgram->setAttributeBuffer(VERTEX_POSITION,
                                      GL_FLOAT,
                                      Vertex::positionOffset(),
                                      3,
                                      Vertex::stride());
    shaderProgram->setAttributeBuffer(NORMAL_VECTOR,
                                      GL_FLOAT,
                                      Vertex::normalOffset(),
                                      3,
                                      Vertex::stride());

    GLuint shaderProgramId = shaderProgram->programId();

    GLint objectColorLoc = glGetUniformLocation(shaderProgramId, "objectColor");
    glUniform3f(objectColorLoc, 0.0f, 0.5f, 0.31f);

    int lightPosLoc = glGetUniformLocation(shaderProgramId, "lightPosition");
    glUniform3f(lightPosLoc, -1.0f, -5.0f, 3.0f);
    GLint lightColorLoc  = glGetUniformLocation(shaderProgramId, "lightColor");
    glUniform3f(lightColorLoc,  1.0f, 0.9f, 1.0f);

    int lightPosLoc1 = glGetUniformLocation(shaderProgramId, "lightPosition1");
    glUniform3f(lightPosLoc1, 10.0f, 15.0f, 3.0f);
    GLint lightColorLoc1  = glGetUniformLocation(shaderProgramId, "lightColor1");
    glUniform3f(lightColorLoc1,  0.9f, 0.0f, 0.3f);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
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
