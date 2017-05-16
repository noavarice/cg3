#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "openglwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , w(new OpenGLWidget(this))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int value)
{
    w->setCameraPosition({value, 5.0f, 4.0f});
}
