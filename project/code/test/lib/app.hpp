#ifndef TEST_LIB_APP_HPP
#define TEST_LIB_APP_HPP

#include <QApplication>
#include <memory>

namespace test {

inline std::unique_ptr<QApplication> getApplication() {
    int argc = 0;
    char arg[] = "";
    char *argv[10] = {arg};

    return std::make_unique<QApplication>(argc, argv);
}

} // namespace test

#endif // end of TEST_LIB_APP_HPP
