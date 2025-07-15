#include "../src/bullet.hpp"
#include "./lib/app.hpp"
#include "./lib/bullet.hpp"
#include "./lib/scene.hpp"

#include <gtest/gtest.h>

TEST(Bullet, getTarget) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto enemy_bullet =
        test::getBullet(scene.get(), Bullet::Target::PLAYER, 1, 2);
    EXPECT_EQ(Bullet::Target::PLAYER, enemy_bullet->getTarget());

    auto player_bullet =
        test::getBullet(scene.get(), Bullet::Target::ENEMY, 1, 2);
    EXPECT_EQ(Bullet::Target::ENEMY, player_bullet->getTarget());
}
