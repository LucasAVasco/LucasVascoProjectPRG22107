#include "../src/bunker.hpp"
#include "./lib/app.hpp"
#include "./lib/bullet.hpp"
#include "./lib/scene.hpp"

#include <gtest/gtest.h>

std::unique_ptr<Bunker> getBunker(QGraphicsScene *scene, int x, int y) {
    return std::make_unique<Bunker>(scene, x, y);
}

TEST(Bunker, isShot) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto bunker = getBunker(scene.get(), 1, 2);
    auto bullet = test::getBullet(scene.get(), Bullet::Target::ENEMY, 1, 2);
    EXPECT_TRUE(bunker->isShot(*bullet));

    auto bullet_out =
        test::getBullet(scene.get(), Bullet::Target::ENEMY, 1000, 2000);
    EXPECT_FALSE(bunker->isShot(*bullet_out));
}
