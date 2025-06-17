#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <optional>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <string>

class SpritePixmap {
  public:
    SpritePixmap(const std::string path, int width, int height)
        : _path(path), _width(width), _height(height) {
        // INFO(LucasAVasco): can not initialize the `QPixmap` before the
        // `QGuiApplication`. This rises the following error at runtime:
        //
        // QPixmap: Must construct a QGuiApplication before a QPixmap
        //
        // Solution: initialize the `QPixmap` at the `addToScene()` method. This
        // method is not called before the application initialization
    }

    QGraphicsPixmapItem *addToScene(QGraphicsScene *scene) {
        // Pixmap initialization
        if (!_pixmap.has_value()) {
            _pixmap = QPixmap(_path.c_str()).scaled(_width, _height);
        }

        // Instance of the Pixmap in the scene
        auto pixmap_item = scene->addPixmap(_pixmap.value());

        if (pixmap_item == nullptr) {
            throw "Can not load pixmap item";
            return nullptr;
        }

        return pixmap_item;
    }

  private:
    std::optional<QPixmap> _pixmap;
    const std::string _path;
    const int _width;
    const int _height;
};

class Sprite {
  public:
    Sprite(SpritePixmap &sprite, QGraphicsScene *scene) {
        _pixmap_item = sprite.addToScene(scene);
    };

    ~Sprite() { this->removeFromScene(); }

    void updatePosition(double x, double y) const {
        _pixmap_item->setPos(x, y);
    };

    void removeFromScene() {
        if (_pixmap_item != nullptr) { // Only removes once
            _pixmap_item->scene()->removeItem(_pixmap_item);
            delete _pixmap_item;
            _pixmap_item = nullptr;
        }
    }

  private:
    QGraphicsPixmapItem *_pixmap_item = nullptr;
};

#endif // end of SPRITE_HPP
