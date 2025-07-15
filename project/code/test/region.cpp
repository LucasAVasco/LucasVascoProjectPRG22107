#include "../src/region.hpp"
#include "./lib/app.hpp"
#include "./lib/sprite.hpp"
#include "lib/scene.hpp"

#include <gtest/gtest.h>
#include <memory>

std::unique_ptr<Region> getRegion(QGraphicsScene *scene,
                                  const Region::Area &area) {

    return std::make_unique<Region>(scene, test::default_sprite_pixmap,
                                    Region::Area{area});
}

TEST(Region, position) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto region = getRegion(scene.get(), {1, 2, 8, 8});

    EXPECT_EQ(1, region->getXPosition());
    EXPECT_EQ(2, region->getYPosition());
}

TEST(Region, isInside) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto region = getRegion(scene.get(), {1, 1, 8, 8});
    auto other_region = getRegion(scene.get(), {0, 0, 10, 10});
    EXPECT_TRUE(region->isInside(*other_region));
}

TEST(Region, isOutInside) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto region = getRegion(scene.get(), {0, 0, 100, 100});
    auto other_region = getRegion(scene.get(), {5, 5, 10, 10});
    EXPECT_FALSE(region->isInside(*other_region));
}

TEST(Region, isPartiallyInside) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto region = getRegion(scene.get(), {0, 0, 5, 100});
    auto other_region = getRegion(scene.get(), {0, 0, 10, 10});
    EXPECT_FALSE(region->isInside(*other_region));
}

TEST(Region, isColliding) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto region = getRegion(scene.get(), {0, 0, 10, 10});
    auto other_region = getRegion(scene.get(), {0, 10, 10, 10});
    EXPECT_TRUE(region->isColliding(*other_region));
}

TEST(Region, isNotColliding) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto region = getRegion(scene.get(), {0, 0, 10, 10});
    auto other_region = getRegion(scene.get(), {0, 11, 10, 10});
    EXPECT_FALSE(region->isColliding(*other_region));
}
