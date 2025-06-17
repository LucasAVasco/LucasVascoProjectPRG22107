#ifndef GAME_HPP
#define GAME_HPP

#include "game_scene.hpp"
#include "initial_menu.hpp"

class Game {
  public:
    Game(QApplication *app, int width, int height)
        : _width(width), _height(height), _app(app),
          _game_scene(width, height, [this]() { this->_showInitialMenu(); }),
          _initial_scene(
              width, height,
              [this](InitialMenuScene::PressedButton pressed_button) {
                  switch (pressed_button) {
                  case InitialMenuScene::PressedButton::START:
                      this->_startGame();
                      break;

                  case InitialMenuScene::PressedButton::EXIT:
                      this->_exitGame();
                      break;
                  }
              }) {};

    int start() {
        srand(time(NULL)); // Used by the game scene

        // View
        _view.setFixedSize(_width, _height);
        _view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Show
        _showInitialMenu();
        _view.show();
        return this->_app->exec();
    };

  private:
    void _startGame() { _view.setScene(&_game_scene); }

    void _exitGame() { _app->quit(); }

    void _showInitialMenu() { _view.setScene(&_initial_scene); }

    QApplication *_app;
    int _width;
    int _height;

    QGraphicsView _view;
    InitialMenuScene _initial_scene;
    GameScene _game_scene;
};

#endif // GAME_HPP
