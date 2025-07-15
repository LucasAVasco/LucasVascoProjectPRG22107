#include "../src/alive.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>

void setupRand() { srand(time(0)); }

TEST(Alive, testGetNumLives) {
    setupRand();

    uint32_t numLives = rand();
    auto alive = Alive(numLives);
    EXPECT_EQ(numLives, alive.getNumLives());
}

TEST(Alive, testTakeOneDamage) {
    setupRand();

    uint32_t numLives = std::clamp(rand(), 10, 100);
    auto alive = Alive(numLives);
    EXPECT_EQ(numLives, alive.getNumLives());

    alive.takeDamage();
    EXPECT_EQ(numLives - 1, alive.getNumLives());
}

TEST(Alive, testTakeDamage) {
    setupRand();

    uint32_t numLives = std::clamp(rand(), 10, 100);
    auto alive = Alive(numLives);

    EXPECT_EQ(numLives, alive.getNumLives());
    uint32_t damage = std::clamp(rand(), 1, 10);

    alive.takeDamage(damage);
    EXPECT_EQ(numLives - damage, alive.getNumLives());
}

TEST(Alive, testDie) {
    setupRand();

    uint32_t numLives = std::clamp(rand(), 10, 100);
    auto alive = Alive(numLives);

    EXPECT_TRUE(alive.isAlive());

    alive.die();
    EXPECT_FALSE(alive.isAlive());
    EXPECT_EQ(0, alive.getNumLives());
}
