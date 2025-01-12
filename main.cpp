#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000 // Delay between frames in microseconds

// Field dimensions
const int WIDTH = 40;
const int HEIGHT = 20;

// Object coordinates and velocities
int ball_x, ball_y;
int ball_dx = 1, ball_dy = 1;
int paddle_left_y, paddle_right_y;

// Score
int score_left = 0;
int score_right = 0;

// Game initialization
void init_game() {
ball_x = WIDTH / 2;
ball_y = HEIGHT / 2;
paddle_left_y = HEIGHT / 2 - 2;
paddle_right_y = HEIGHT / 2 - 2;
}

// Draw the game field
void draw_game() {
clear();

// Draw the borders
for (int i = 0; i < WIDTH; ++i) {
mvprintw(0, i, "#");
mvprintw(HEIGHT - 1, i, "#");
}
for (int i = 0; i < HEIGHT; ++i) {
mvprintw(i, 0, "#");
mvprintw(i, WIDTH - 1, "#");
}

// Draw the ball
mvprintw(ball_y, ball_x, "O");

// Draw the left paddle
for (int i = 0; i < 4; ++i) {
mvprintw(paddle_left_y + i, 1, "|");
}

// Draw the right paddle
for (int i = 0; i < 4; ++i) {
mvprintw(paddle_right_y + i, WIDTH - 2, "|");
}

// Display the score
mvprintw(0, WIDTH / 2 - 5, " %d : %d ", score_left, score_right);

refresh();
}

// Update the game state
void update_game() {
// Move the ball
ball_x += ball_dx;
ball_y += ball_dy;

// Reflect off the top and bottom walls
if (ball_y <= 1 || ball_y >= HEIGHT - 2) {
ball_dy = -ball_dy;
}

// Reflection from the left paddle
if (ball_x == 2 && ball_y >= paddle_left_y && ball_y < paddle_left_y + 4) {
ball_dx = -ball_dx;
}

// Reflection from the right paddle
if (ball_x == WIDTH - 3 && ball_y >= paddle_right_y && ball_y < paddle_right_y + 4) {
ball_dx = -ball_dx;
}

// Score and reset the ball
if (ball_x <= 1) {
score_right++;
init_game();
} else if (ball_x >= WIDTH - 1) {
score_left++;
init_game();
}

// Check if the game is over
if (score_left == 11 || score_right == 11) {
clear();
mvprintw(HEIGHT / 2, WIDTH / 2 - 10, "Game Over! Winner: %s", score_left == 11 ? "Left Player" : "Right Player");
refresh();
usleep(3000000); // Delay before exiting
endwin();
_exit(0);
}
}

// Handle keyboard input
void process_input() {
int ch = getch();

switch (ch) {
case 'w': // Left paddle up
if (paddle_left_y > 1) {
paddle_left_y--;
}
break;
case 's': // Left paddle down
if (paddle_left_y < HEIGHT - 5) {
paddle_left_y++;
}
break;
case 'i': // Right paddle up
if (paddle_right_y > 1) {
paddle_right_y--;
}
break;
case 'k': // Right paddle down
if (paddle_right_y < HEIGHT - 5) {
paddle_right_y++;
}
break;
case 27: // ESC key to pause
while (true) {
mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Paused. Press ESC to continue.");
refresh();
int pause_ch = getch();
if (pause_ch == 27) {
break;
}
}
break;
}
}

int main() {
 // Initialize ncurses
 initscr();
 noecho();
 curs_set(FALSE);
 keypad(stdscr, TRUE);
 nodelay(stdscr, TRUE);

 init_game();

 while (true) {
 draw_game();
 process_input();
 update_game();
 usleep(DELAY);
 }

 // End ncurses
 endwin();
 return 0;
}
