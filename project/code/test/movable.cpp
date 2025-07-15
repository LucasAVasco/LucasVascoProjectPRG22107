#include "../src/movable.hpp"
#include "./lib/app.hpp"
#include "./lib/scene.hpp"
#include "./lib/sprite.hpp"

#include <gtest/gtest.h>
#include <memory>

std::unique_ptr<Movable> getMovable(QGraphicsScene *scene,
                                    const Region::Area &area) {
    return std::make_unique<Movable>(scene, test::default_sprite_pixmap,
                                     Region::Area{area});
}

TEST(Movable, getPosition) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto movable = getMovable(scene.get(), {1, 2, 8, 8});

    EXPECT_EQ(1, movable->getXPosition());
    EXPECT_EQ(2, movable->getYPosition());
}

TEST(Movable, setPosition) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto movable = getMovable(scene.get(), {1, 2, 8, 8});

    movable->setPosition(3, 4);

    EXPECT_EQ(3, movable->getXPosition());
    EXPECT_EQ(4, movable->getYPosition());
}

TEST(Movable, setVelocity) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto movable = getMovable(scene.get(), {1, 2, 8, 8});

    movable->setVelocity(3, 4);

    EXPECT_EQ(3, movable->getXVelocity());
    EXPECT_EQ(4, movable->getYVelocity());
}

TEST(Movable, updatePosition) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto movable = getMovable(scene.get(), {1, 2, 8, 8});

    movable->setVelocity(3, 4);
    movable->updatePosition();

    EXPECT_EQ(4, movable->getXPosition());
    EXPECT_EQ(6, movable->getYPosition());
}

TEST(Movable, limitedArea) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto movable = getMovable(scene.get(), {1, 2, 8, 8});
    auto limited_area = Movable::LimitedArea{.begin = {0, 0}, .end = {10, 20}};
    movable->setLimitedArea(limited_area);

    movable->setPosition(100, 100);

    EXPECT_EQ(10 - 8, movable->getXPosition());
    EXPECT_EQ(20 - 8, movable->getYPosition());
}

TEST(Movable, limitedAreaColliding) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto movable = getMovable(scene.get(), {1, 2, 8, 8});
    auto limited_area = Movable::LimitedArea{.begin = {0, 0}, .end = {10, 20}};
    movable->setLimitedArea(limited_area);

    // Right
    movable->setPosition(100, 100);
    ASSERT_TRUE(movable->isCollidingAtLimitAreaRight());

    // Left
    movable->setPosition(0, 100);
    ASSERT_TRUE(movable->isCollidingAtLimitAreaLeft());

    // Top
    movable->setPosition(100, 0);
    ASSERT_TRUE(movable->isCollidingAtLimitAreaTop());

    // Bottom
    movable->setPosition(100, 100);
    ASSERT_TRUE(movable->isCollidingAtLimitAreaBottom());
}
