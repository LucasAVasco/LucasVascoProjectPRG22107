#include "../src/sprite.hpp"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <gtest/gtest.h>

#include <QApplication>
#include <qapplication.h>
#include <qnamespace.h>

#include "./lib/app.hpp"

TEST(SpriteSpritePixmap, testAddToScene) {
    auto app = test::getApplication();

    auto pixmap = SpritePixmap("../assets/bullet.png", 10, 10);
    auto scene = QGraphicsScene(0, 0, 100, 100);

    EXPECT_EQ(0, scene.items().size());
    auto sprite = pixmap.addToScene(&scene);
    EXPECT_EQ(1, scene.items().size());
    scene.removeItem(sprite);
}

TEST(SpriteSprite, testCreateSprite) {
    auto app = test::getApplication();

    auto pixmap = SpritePixmap("../assets/bullet.png", 10, 10);
    auto scene = QGraphicsScene(0, 0, 100, 100);

    EXPECT_EQ(0, scene.items().size());

    // Add one element to scene
    auto sprite = Sprite(pixmap, &scene);
    EXPECT_EQ(1, scene.items().size());

    // Remove the element from scene
    sprite.removeFromScene();
    EXPECT_EQ(0, scene.items().size());
}

TEST(SpriteSprite, testDestroySprite) {
    auto app = test::getApplication();

    auto pixmap = SpritePixmap("../assets/bullet.png", 10, 10);
    auto scene = QGraphicsScene(0, 0, 100, 100);

    EXPECT_EQ(0, scene.items().size());

    // Add one element to scene
    auto sprite = new Sprite(pixmap, &scene);
    EXPECT_EQ(1, scene.items().size());

    // Remove the element from scene
    delete sprite;
    EXPECT_EQ(0, scene.items().size());
}
