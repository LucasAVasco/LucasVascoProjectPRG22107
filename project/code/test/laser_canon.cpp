#include "../src/laser_canon.hpp"
#include "./lib/app.hpp"
#include "./lib/bullet.hpp"
#include "./lib/scene.hpp"

#include <gtest/gtest.h>

std::unique_ptr<LaserCanon> getPlayer(QGraphicsScene *scene, int x, int y) {
    return std::make_unique<LaserCanon>(scene, x, y);
}

TEST(LaserCanon, isShot) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto player = getPlayer(scene.get(), 1, 2);
    auto bullet = test::getBullet(scene.get(), Bullet::Target::PLAYER, 1, 2);
    EXPECT_TRUE(player->isShot(*bullet));

    auto bullet_out =
        test::getBullet(scene.get(), Bullet::Target::PLAYER, 1000, 2000);
    EXPECT_FALSE(player->isShot(*bullet_out));

    auto laser_canon_bullet =
        test::getBullet(scene.get(), Bullet::Target::ENEMY, 1, 2);
    EXPECT_FALSE(player->isShot(*bullet_out));
}

TEST(LaserCanon, shot) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    // Bullet target
    auto player = getPlayer(scene.get(), 1, 2);
    auto bullet = player->shot();
    EXPECT_NE(nullptr, bullet.get());
    EXPECT_EQ(Bullet::Target::ENEMY, bullet->getTarget());

    // Can not sot several bullets at the same time (there are a delay
    // between each shots)
    auto bullet2 = player->shot();
    EXPECT_EQ(nullptr, bullet2.get());
}
