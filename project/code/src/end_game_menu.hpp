#ifndef END_GAME_MENU_HPP
#define END_GAME_MENU_HPP

#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QWidget>
#include <cstdint>
#include <functional>
#include <qboxlayout.h>
#include <qgraphicsitem.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <string>

class EndGameMenu {
  public:
    enum class PressedButton {
        RESTART,
        EXIT,
    };

    typedef std::function<void(PressedButton pressed_button)> Callback;

    EndGameMenu(Callback callback) : _callback(callback) {
        this->_widget.setLayout(&_layout);

        QFont font("Arial", 16, QFont::Bold);
        _score_text.setFont(font);
        _layout.addWidget(&_score_text);

        // Button callbacks
        _layout.addWidget(&_restart_button);
        QObject::connect(&_restart_button, &QPushButton::clicked,
                         [this]() { this->_callback(PressedButton::RESTART); });

        _layout.addWidget(&_exit_button);
        QObject::connect(&_exit_button, &QPushButton::clicked,
                         [this]() { this->_callback(PressedButton::EXIT); });
    }

    QWidget *getWidget() { return &_widget; }

    void updateScore(uint32_t score) {
        std::string score_str = "Your final Score: " + std::to_string(score);
        _score_text.setText(score_str.c_str());
    }

  private:
    Callback _callback;
    QWidget _widget;
    QLabel _score_text = QLabel();
    QVBoxLayout _layout = QVBoxLayout();
    QPushButton _restart_button = QPushButton("Restart");
    QPushButton _exit_button = QPushButton("Exit");
};

#endif // end of END_GAME_MENU_HPP
