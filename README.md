# Console ping pong in C++

This is a simple implementation of the classic **Pong** game in C++, using the **ncurses** library to render the game in the terminal.

## Description

This program is a text-based implementation of the classic **Pong** game, where two players control paddles and compete to hit the ball. The game ends when one player scores 11 points. Players control paddles using keyboard input and observe the ball's movement, bouncing off walls and paddles.

### How the Code Works

1. **Constants and Variables**

   At the beginning of the program, constants and variables are defined:
   
   - `DELAY`: delay between frames in microseconds (controls the game speed).
   - Field dimensions:
     - `WIDTH = 40`: width of the game field.
     - `HEIGHT = 20`: height of the game field.
   - Variables for the ball and paddles:
     - `ball_x`, `ball_y`: current coordinates of the ball.
     - `ball_dx`, `ball_dy`: ball speed in the X and Y directions (determining its movement).
     - `paddle_left_y`, `paddle_right_y`: vertical coordinates of the left and right paddles.
   - Variables for score:
     - `score_left`, `score_right`: score for each player.

2. **Game Initialization: `init_game()`**

   The `init_game()` function sets the initial position of the ball and paddles:
   - The ball starts in the center of the field: `ball_x = WIDTH / 2`, `ball_y = HEIGHT / 2`.
   - Paddles are also placed at the center vertically: `paddle_left_y` and `paddle_right_y` are set to the middle of the field minus 2 because the paddles occupy 4 rows vertically.

3. **Rendering the Game Field: `draw_game()`**

   The `draw_game()` function is responsible for rendering the entire game field on the screen:
   - The screen is cleared using `clear()`.
   - The field boundaries are drawn:
     - Horizontal boundaries: `mvprintw(0, i, "#")` and `mvprintw(HEIGHT - 1, i, "#")`.
     - Vertical boundaries: `mvprintw(i, 0, "#")` and `mvprintw(i, WIDTH - 1, "#")`.
   - Game elements are displayed:
     - The ball is drawn with `mvprintw(ball_y, ball_x, "O")`.
     - The left and right paddles are drawn using loops to print vertical bars `|` at the `paddle_left_y` and `paddle_right_y` coordinates.
   - The current score is displayed using `mvprintw(0, WIDTH / 2 - 5, " %d : %d ", score_left, score_right)`.

4. **Updating the Game State: `update_game()`**

   This function updates the game state:
   - **Ball movement**: 
     - The ball moves along the X and Y axes using `ball_dx` and `ball_dy`.
   - **Ball reflection**:
     - The ball bounces off the top and bottom walls: `ball_dy = -ball_dy`.
     - The ball bounces off the paddles:
       - For the left paddle, the ball's position is checked to see if it is within the paddle's Y range and at the left boundary in X.
       - The same is done for the right paddle.
   - **Scoring**:
     - If the ball crosses the left or right boundary, the corresponding player's score increases, and the ball is reset to the center.
   - **Game Over**:
     - The game ends when one player reaches 11 points. A "Game Over!" message is displayed, showing the winner.

5. **Handling Input: `process_input()`**

   The `process_input()` function processes keyboard input:
   - The left paddle is controlled with the `w` (up) and `s` (down) keys.
   - The right paddle is controlled with the `i` (up) and `k` (down) keys.
   - The `ESC` key pauses the game:
     - After pressing `ESC`, a pause message appears, and the game waits for another `ESC` key press to resume.

6. **Main Game Loop**

   In the main function `main()`, ncurses is initialized:
   - `initscr()`: initializes ncurses.
   - `noecho()`: disables displaying typed characters.
   - `curs_set(FALSE)`: hides the cursor.
   - `keypad(stdscr, TRUE)`: enables handling of special keys (like arrow keys).
   - `nodelay(stdscr, TRUE)`: sets non-blocking mode for input.

   Then, an infinite game loop starts:
   - `draw_game()` renders the current game state.
   - `process_input()` handles user input.
   - `update_game()` updates the game state (ball movement, reflections, and score).
   - `usleep(DELAY)` controls the refresh rate of the game.

7. **Game Over**

   When the game is over (one player reaches 11 points), the program displays a victory message and ends the game using `endwin()`.

