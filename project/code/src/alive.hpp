#ifndef ALIVE_HPP
#define ALIVE_HPP

#include <cstdint>

class Alive {
  public:
    Alive(uint32_t lives) : _lives(lives) {};

    bool isAlive() const { return _lives > 0; }
    uint32_t getNumLives() const { return _lives; }

    void takeDamage(uint32_t lives = 1) {
        if (lives > _lives) {
            _lives = 0;
        } else {
            _lives -= lives;
        }
    }

  protected:
    uint32_t _lives = 3;
};
#endif // end of ALIVE_HPP
