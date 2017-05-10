#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions
{
public:
    OpenGLWidget();
};

#endif // OPENGLWIDGET_H
