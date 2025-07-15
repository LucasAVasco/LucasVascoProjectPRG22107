#ifndef TEST_LIB_SCENE_HPP
#define TEST_LIB_SCENE_HPP

#include <QGraphicsScene>
#include <memory>

namespace test {

inline std::unique_ptr<QGraphicsScene> getScene() {
    return std::make_unique<QGraphicsScene>();
}

} // namespace test

#endif // end of TEST_LIB_SCENE_HPP
