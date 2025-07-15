# Testes

This project tests can be classified as follows:

- Automatic unit tests

- Manual tests

## Automatic unit tests

These tests are managed by [GoogleTest](https://github.com/google/googletest). The instructions to configure, build and run them are
available at [./code/README.md](./code/README.md).

These tests disables the GUI, so not all functionalities can be tested.

The game us automatically tested using a [Github workflow](https://docs.github.com/en/actions) available at
[../.github/workflows/unit-tests.yml](../.github/workflows/unit-tests.yml). This workflow is triggered at each push to the repository. You
can see its result at [Repository - Actions](https://github.com/LucasAVasco/LucasVascoProjectPRG22107/actions).

## Manual tests

These tests are available as videos uploaded on [YouTube](https://www.youtube.com/).

- Initial menu test [video](https://youtu.be/Uh2gP6EjUpw):

    - Shows the start game button creating a new game session every time it is pressed, and the exit button closing the application.

- Pause game menu test [video](https://youtu.be/WwRPncE4Yzw):

    - Show the pause game menu. When the game is paused, the game is not updated and the player can see the current game state. The exit
      button returns to the initial menu. The resume button resumes the game. The restart button restarts the game session.

- End game menu test [video](https://youtu.be/Il_p4pZcT18):

    - Show the player's score before death. When the game ends, the game is not updated and the player can see the current game state. The
      exit button returns to the initial menu. The restart button restarts the game session.

- Game-play test [video](https://youtu.be/_6s7wZUGdqU):

    - Shows the game=play. The following list shows all the requirements that this game play satisfies (copied from
      [analise.md](./analise.md)):

        - Functional Requirements

            - [x] The player must be able to move the laser canon to the left and right using keyboard arrows. The laser canon cannot leave
                  the game scene.

            - [x] The player must be able to shoot bullets to destroy enemies.

            - [x] The game should generate several waves of enemies that move horizontally and down gradually. Enemies cannot leave the game
                  scene.

            - [x] The game must track and display the player score based on the number of dead enemies.

            - [x] The player must have 3 lives, which decrease each time the laser canon is hit by a bullet.

        - Non-functional requirements

            - [x] The game must have smooth gameplay.

            - [x] Game controls must be responsive with a low input delay.

            - [x] The game must be compatible with the Linux platform.

            - [x] The game must not crash when an unexpected input is provided (for example, pressing several keys simultaneously).

            - [x] The game must load fast (fast startup time). The player should not wait long to play the game.

<div align="center">

[Retroceder](implementacao.md) | [Início](README.md)

</div>
