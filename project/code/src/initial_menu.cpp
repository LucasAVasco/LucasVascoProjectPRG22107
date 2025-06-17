#include "initial_menu.hpp"

InitialMenuScene::InitialMenuScene(int width, int height,
                                   InitialMenuScene::Callback callback)
    : _width(width), _height(height), _callback(callback) {
    // Scene
    this->setBackgroundBrush(Qt::gray);
    this->setSceneRect(0, 0, _width, _height);

    // Initial message
    QFont font("Arial", 54, QFont::Bold);
    _text.setFont(font);
    _layout.addWidget(&_text);

    // Makes the widget fill the full area of the scene
    auto layout_proxy = this->addWidget(&_widget);
    layout_proxy->setPos(0, 0);
    layout_proxy->setMinimumSize(_width, _height);

    // Layout with the buttons
    _widget.setLayout(&_layout);

    _layout.addWidget(&_start_button);
    QObject::connect(&_start_button, &QPushButton::clicked,
                     [this]() { this->_callback(PressedButton::START); });

    _layout.addWidget(&_exit_button);
    QObject::connect(&_exit_button, &QPushButton::clicked,
                     [this]() { this->_callback(PressedButton::EXIT); });
}

InitialMenuScene::~InitialMenuScene() {}
