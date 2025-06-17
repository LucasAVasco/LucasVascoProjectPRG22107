#include "game_scene.hpp"

GameScene::GameScene(int width, int height, Callback exit_button_callback)
    : _width(width), _height(height),
      _exit_button_callback(exit_button_callback),
      QGraphicsScene(0, 0, width, height), _position_timer(this),
      _enemies_shot_timer(this), _render_timer(this),
      _pause_menu([this](PauseGameMenu::PressedButton pressed_button) {
          switch (pressed_button) {

          case PauseGameMenu::PressedButton::RESUME:
              this->_pause_menu_proxy->hide();
              break;

          case PauseGameMenu::PressedButton::RESTART:
              this->_restart();
              break;

          case PauseGameMenu::PressedButton::EXIT:
              this->_exit_button_callback();
              break;
          }
      }),
      _end_game_menu([this](EndGameMenu::PressedButton pressed_button) {
          switch (pressed_button) {

          case EndGameMenu::PressedButton::RESTART:
              this->_restart();
              break;

          case EndGameMenu::PressedButton::EXIT:
              this->_exit_button_callback();
              break;
          }
      }) {

    // Scene
    this->setBackgroundBrush(Qt::black);
    this->setSceneRect(0, 0, _width, _height);

    // Pause game menu
    _pause_menu_proxy = this->addWidget(_pause_menu.getWidget());
    _pause_menu_proxy->setPos((double)_width / 2 - MENU_WIDTH / 2,
                              (double)height / 2 - MENU_HEIGHT / 2);
    _pause_menu_proxy->setMinimumSize(MENU_WIDTH, MENU_HEIGHT);
    _pause_menu_proxy->setZValue(
        1000); // On top of all other elements (except the end game menu)
    _pause_menu_proxy->hide();

    // End game menu
    _end_game_menu_proxy = this->addWidget(_end_game_menu.getWidget());
    _end_game_menu_proxy->setPos((double)_width / 2 - MENU_WIDTH / 2,
                                 (double)height / 2 - MENU_HEIGHT / 2);
    _end_game_menu_proxy->setMinimumSize(MENU_WIDTH, MENU_HEIGHT);
    _end_game_menu_proxy->setZValue(
        2000); // On top of all other elements (including the pause menu)
    _end_game_menu_proxy->hide();

    // Initialization of laser canon, enemies, bunkers, etc.
    _restart();

    // Score text
    QFont font("Arial", 16, QFont::Bold);
    _score_text.setFont(font);
    _score_text.setDefaultTextColor(Qt::white);
    _score_text.setPos(0, 0);
    this->addItem(&_score_text);

    // Position timer
    this->connect(&_position_timer, SIGNAL(timeout()), this,
                  SLOT(_updatePosition()));
    _position_timer.start(40);

    // Enemy shot timer
    this->connect(&_enemies_shot_timer, SIGNAL(timeout()), this,
                  SLOT(_enemiesShotLaserCanon()));
    _enemies_shot_timer.start(3000);

    // Render timer
    this->connect(&_render_timer, SIGNAL(timeout()), this, SLOT(_render()));
    _render_timer.start(40);
};

GameScene::~GameScene() {}
