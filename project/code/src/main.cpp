#include "game.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Game game(&app, 700, 900);
    return game.start();
}
