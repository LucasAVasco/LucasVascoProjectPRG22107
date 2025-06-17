#ifndef INITIAL_MENU_HPP
#define INITIAL_MENU_HPP

#include <QGraphicsProxyWidget>
#include <qboxlayout.h>
#include <qgraphicsscene.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qwidget.h>

class InitialMenuScene : public QGraphicsScene {
    Q_OBJECT;

  public:
    enum class PressedButton {
        START,
        EXIT,
    };

    typedef std::function<void(PressedButton pressed_button)> Callback;

    InitialMenuScene(int width, int height, Callback callback);
    ~InitialMenuScene();

  private:
    int _width;
    int _height;
    Callback _callback;

    QWidget _widget;
    QVBoxLayout _layout;
    QLabel _text = QLabel("Space invaders");
    QPushButton _start_button = QPushButton("Start");
    QPushButton _exit_button = QPushButton("Exit");
};

#endif // end of INITIAL_MENU_HPP
