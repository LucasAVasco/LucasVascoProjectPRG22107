#ifndef PAUSE_GAME_MENU_HPP
#define PAUSE_GAME_MENU_HPP

#include <QApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <functional>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qevent.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpixmap.h>
#include <qwidget.h>

class PauseGameMenu {
  public:
    enum class PressedButton {
        RESUME,
        RESTART,
        EXIT,
    };

    typedef std::function<void(PressedButton pressed_button)> Callback;

    PauseGameMenu(Callback callback) : _callback(callback) {
        _widget.setLayout(&_layout);

        // Button callbacks
        _layout.addWidget(&_resume_button);
        QObject::connect(&_resume_button, &QPushButton::clicked,
                         [this]() { this->_callback(PressedButton::RESUME); });

        _layout.addWidget(&_restart_button);
        QObject::connect(&_restart_button, &QPushButton::clicked,
                         [this]() { this->_callback(PressedButton::RESTART); });

        _layout.addWidget(&_exit_button);
        QObject::connect(&_exit_button, &QPushButton::clicked,
                         [this]() { this->_callback(PressedButton::EXIT); });
    }

    QWidget *getWidget() { return &_widget; }

  private:
    const Callback _callback;

    QWidget _widget = QWidget();
    QVBoxLayout _layout = QVBoxLayout();
    QPushButton _resume_button = QPushButton("Resume");
    QPushButton _restart_button = QPushButton("Restart");
    QPushButton _exit_button = QPushButton("Exit");
};

#endif // end of PAUSE_GAME_MENU_HPP
