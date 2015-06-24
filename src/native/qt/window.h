
#pragma once

#include <qgl.h>
#include <QTime>
#include <QTimer>

#include "xe/window.h"

class QtScheduler;
class QtMouse;
class QtKeyboard;

class QtWindow : public QGLWidget, public XeWindow
{
    Q_OBJECT

public:
    explicit QtWindow(QWidget *parent = 0);
    ~QtWindow();

    QtScheduler *sched() const;
    void setSched(QtScheduler*);

    QtMouse *mouse() const;
    void setMouse(QtMouse*);

    QtKeyboard *keyboard() const;
    void setKeyboard(QtKeyboard*);
    
    void *handle() const;

    const char *title() const;
    void setTitle(const char *);
    
    XeRect bounds() const;
    void setBounds(const XeRect &);

    void show();
    void hide();

    bool isFullscreen() const;
    void setFullscreen(bool);
    void toggleFullscreen();

private:
    QTime m_updateTime;
    QTime m_renderTime;
    QTimer m_timer;
    QtScheduler *m_sched;
    QtMouse *m_mouse;
    QtKeyboard *m_keyboard;
    bool m_fullscreen;
    bool m_changingState;

    void initializeGL();
    void paintGL();
    void resizeGL(int, int);

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

private slots:
    void tick();
};

