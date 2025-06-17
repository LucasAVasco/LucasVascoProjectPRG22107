#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "./pause_game_menu.hpp"
#include "bullet.hpp"
#include "bunker.hpp"
#include "end_game_menu.hpp"
#include "laser_canon.hpp"
#include "wave.hpp"
#include <QApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <memory>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qevent.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpixmap.h>
#include <qtmetamacros.h>
#include <qwidget.h>
#include <string>

class GameScene : public QGraphicsScene {
    Q_OBJECT;

    static constexpr int BUNKER_OFFSET = -Bunker::HEIGHT - 200;
    static constexpr double MENU_WIDTH = 300;
    static constexpr double MENU_HEIGHT = 400;

  public:
    typedef std::function<void()> Callback;

    GameScene(int width, int height, Callback exit_button_callback);
    ~GameScene();

    void keyReleaseEvent(QKeyEvent *key_event) {
        switch (key_event->key()) {

        case Qt::Key_Left:
            if (_laser_canon->getXVelocity() < 0)
                _laser_canon->setXVelocity(0);
            break;

        case Qt::Key_Right:
            if (_laser_canon->getXVelocity() > 0)
                _laser_canon->setXVelocity(0);
            break;
        }
    }

    void keyPressEvent(QKeyEvent *key_event) {
        switch (key_event->key()) {

        case Qt::Key_Left:
            _laser_canon->setXVelocity(-10);
            break;

        case Qt::Key_Right:
            _laser_canon->setXVelocity(10);
            break;

        case Qt::Key_Space:
            if (!_isPaused()) {
                _bullets.push_back(_laser_canon->shot());
            }
            break;

        case Qt::Key_Escape:
            if (_pause_menu_proxy->isVisible()) {
                _pause_menu_proxy->hide();

            } else {
                _pause_menu_proxy->show();
            }
            break;
        }
    }

  public slots:
    void _render() {
        if (_isPaused()) {
            return;
        }

        _laser_canon->updateSpritePosition();

        for (auto &&bullet : _bullets) {
            bullet->updateSpritePosition();
        }

        if (_wave != nullptr) {
            _wave->updateSpritesPosition();
        }

        for (auto &&bunker : _bunkers) {
            bunker.updateSpritePosition();
        }

        _updateScoreText();
    };

    void _updatePosition() {
        if (_isPaused()) {
            return;
        }

        _laser_canon->updatePosition();
        _wave->updatePosition();

        for (auto &&bullet : _bullets) {
            bullet->updatePosition();
        }

        _deleteOutOfRangeBullets();
        _killShotEnemies();
        _checkShotsOnLaserCanon();
        _checkShotsOnBunkers();
    }

    void _enemiesShotLaserCanon() { _wave->shot(_bullets); }

  private:
    void _restart() {
        this->_pause_menu_proxy->hide();
        this->_end_game_menu_proxy->hide();

        // Bunkers
        _bunkers.clear();

        for (auto x :
             {0, _width / 2 - Bunker::WIDTH / 2, _width - Bunker::WIDTH}) {
            _bunkers.emplace_back(this, x, _height + BUNKER_OFFSET);
        }

        // Laser Canon
        if (_laser_canon != nullptr) {
            delete _laser_canon;
        }
        _laser_canon = new LaserCanon(this, _width / 2 - LaserCanon::WIDTH / 2,
                                      _height - LaserCanon::HEIGHT - 50);

        // Laser canon max area
        Movable::LimitedArea area = {
            .begin = {0, 0},
            .end = {_width, _height},
        };
        _laser_canon->setLimitedArea(area);

        // Enemies
        _newWave();

        // Bullets
        _bullets.clear();
    }

    bool _isPaused() {
        return !_laser_canon->isAlive() || _pause_menu_proxy->isVisible() ||
               _end_game_menu_proxy->isVisible();
    }

    void _newWave() {
        if (_wave != nullptr) {
            delete _wave;
        }
        _wave = new Wave(this, _width, _height, _width / 2, 10);
    }

    void _deleteOutOfRangeBullets() {
        _bullets.remove_if([this](std::unique_ptr<Bullet> &bullet) {
            if (!bullet->isInside(0, 0, this->_width, this->_height)) {
                return true;
            }
            return false;
        });
    };

    void _checkShotsOnLaserCanon() {
        for (auto &&bullet : this->_bullets) {
            if (_laser_canon->isShot(*bullet)) {
                this->_bullets.remove(bullet);
                _laser_canon->takeDamage();
                break;
            }
        }

        if (!_laser_canon->isAlive()) {
            _end_game_menu.updateScore(_laser_canon->getScore());
            _end_game_menu_proxy->show();
        }
    }

    void _checkShotsOnBunkers() {
        _bullets.remove_if([this](auto &bullet) {
            for (auto &&bunker : this->_bunkers) {
                if (bunker.isShot(*bullet)) {
                    bunker.takeDamage();
                    return true;
                }
            }

            return false;
        });

        _bunkers.remove_if(
            [this](Bunker &bunker) { return !bunker.isAlive(); });
    }

    void _killShotEnemies() {
        auto score = _wave->killShotSpaceShips(_bullets);
        _laser_canon->addScore(score);

        if (_wave->getNumSpaceShips() == 0) {
            _newWave();
        }
    }

    void _updateScoreText() {
        if (_isPaused()) {
            return;
        }

        std::string text = "Score: " + std::to_string(_laser_canon->getScore());
        _score_text.setPlainText(text.c_str());
    }

    int _width;
    int _height;
    Callback _exit_button_callback;

    QTimer _position_timer;
    QTimer _enemies_shot_timer;
    QTimer _render_timer;

    LaserCanon *_laser_canon = nullptr;
    Wave *_wave = nullptr;
    std::list<Bunker> _bunkers;
    std::list<std::unique_ptr<Bullet>> _bullets;

    QGraphicsTextItem _score_text = QGraphicsTextItem("Score: ");
    PauseGameMenu _pause_menu;
    QGraphicsProxyWidget *_pause_menu_proxy = nullptr;
    EndGameMenu _end_game_menu;
    QGraphicsProxyWidget *_end_game_menu_proxy;
};

#endif // end of GAME_SCENE_HPP
