#include "openglview.h"
#include <QDebug>
#include "constants.h"

OpenGLView::OpenGLView(QWidget *parent) : QOpenGLWidget(parent), sets(new QList<QSet<Point>*>) { }

void OpenGLView::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OpenGLView::resizeGL(int w, int h)
{
    width = w;
    height = h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLView::drawInput()
{
    if(currentPoints != nullptr){
        glPointSize(10.0f);
        glLineWidth(10.0f);
        glColor3f(0.0, 1.0, 0.0);
        for(auto set: *sets){
            glBegin(GL_LINE_STRIP);
             for(auto p: *set){
               glVertex2i(p.x, p.y);
             }
            glEnd();
        }
    }
}

void OpenGLView::clear()
{
    for(auto set: *sets){
        delete set;
    }
    sets->clear();
    update();
}

void OpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawGrid();
    drawInput();
}

void OpenGLView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
    *currentPoints << Point(event->pos().x(), event->pos().y());
    update();
}

void OpenGLView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->type();
    currentPoints = new QSet<Point>;
    *sets << currentPoints;
}

void OpenGLView::drawGrid()
{
    glLineWidth(1.0f);
    glColor3f(1.0, 0.0, 0.0);
    int c = 0;
    glBegin(GL_LINES);
    for(int i = COLUMN_COUNT; i > 0; --i){
        glVertex2i(0,c);
        glVertex2i(width, c);
        glVertex2i(c,0);
        glVertex2i(c, height);
        c += COLUMN_WIDTH;
    }
    glEnd();
}

OpenGLView::~OpenGLView()
{
    for(auto set: *sets){
        delete set;
    }

    delete sets;
}
