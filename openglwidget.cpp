#include "openglwidget.h"

#include "conecoordsgen.h"

#include <QImage>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QtMath>

enum AttributeBuffer
{
    VERTEX_POSITION,
    NORMAL_VECTOR,
    TEXTURE_COORDS
};

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , height{2.0f}
    , radius{1.0f}
    , source1{{3.0f, 1.0f, 2.0f}, {1.0f, 1.0f, 0.0f}}
    , source2{{-3.0f, 1.0f, 2.0f}, {0.0f, 1.0f, 1.0f}}
    , model{}
    , view{}
    , projection{}
{
    model.setToIdentity();
    view.lookAt({0.0f, 5.0f, 4.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f});
    projection.perspective(45.0f, 4.0f / 3.0f, 0.1f, 10.0f);
}

OpenGLWidget::~OpenGLWidget()
{
    vertexArrayObject.release();
    vertexArrayObject.destroy();
    vertexBuffer.release();
    vertexBuffer.destroy();
    delete shaderProgram;
    delete tex;
}

void OpenGLWidget::setFirstLightSourcePosition(const QVector3D& position)
{
    source1.first = position;
}

void OpenGLWidget::setFirstLightSourceColor(const QVector3D& color)
{
    source1.second = color;
}

void OpenGLWidget::setSecondLightSourcePosition(const QVector3D& position)
{
    source2.first = position;
}

void OpenGLWidget::setSecondLightSourceColor(const QVector3D& color)
{
    source2.second = color;
}

void OpenGLWidget::setCameraPosition(const QVector3D &newPosition)
{
    view.lookAt(newPosition, {0.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f});
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    shaderProgram->link();
    shaderProgram->bind();

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(sizeof(vertices));

    tex = new QOpenGLTexture(QOpenGLTexture::Target2D);
    tex->setData(QImage(":/textures/stripes.png"));
    vertexArrayObject.create();
    vertexArrayObject.bind();
    shaderProgram->enableAttributeArray(VERTEX_POSITION);
    shaderProgram->enableAttributeArray(NORMAL_VECTOR);
    shaderProgram->enableAttributeArray(TEXTURE_COORDS);
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
    shaderProgram->setAttributeBuffer(TEXTURE_COORDS,
                                      GL_FLOAT,
                                      Vertex::textureCoordsOffset(),
                                      2,
                                      Vertex::stride());

    GLuint shaderProgramId = shaderProgram->programId();

    int lightPosLoc = glGetUniformLocation(shaderProgramId, "lightPosition");
    auto tempVec = source1.first;
    glUniform3f(lightPosLoc, tempVec.x(), tempVec.y(), tempVec.z());
    GLint lightColorLoc  = glGetUniformLocation(shaderProgramId, "lightColor");
    tempVec = source1.second;
    glUniform3f(lightColorLoc,  tempVec.x(), tempVec.y(), tempVec.z());

    int lightPosLoc1 = glGetUniformLocation(shaderProgramId, "lightPosition1");
    tempVec = source2.first;
    glUniform3f(lightPosLoc1,  tempVec.x(), tempVec.y(), tempVec.z());
    GLint lightColorLoc1  = glGetUniformLocation(shaderProgramId, "lightColor1");
    tempVec = source2.second;
    glUniform3f(lightColorLoc1,  tempVec.x(), tempVec.y(), tempVec.z());
}

void OpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    generateConeCoords(vertices, height, radius);
    tex->bind();
    shaderProgram->setUniformValue("sampler", 0);
    vertexBuffer.write(0, vertices, sizeof(vertices));
    shaderProgram->setUniformValue("model", model);
    shaderProgram->setUniformValue("view", view);
    shaderProgram->setUniformValue("projection", projection);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(Vertex));
}
