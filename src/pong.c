/*
  pong.c
  Written: 11/15/2026, by Ashton Cross
  Github.com/AshtonCross

  TODO:
        - Rework the ball logic to make it more fun.
        - Make the text look less weird.
 */

#include <raylib.h>

float newSpeed() {
  return (float)GetRandomValue(110, 400);
}

int main ( void ) {

  // init

  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Pong");

  SetTargetFPS(60);

  Rectangle ball = {screenWidth / 2 - 12, screenHeight / 2 - 12, 25, 25};
  enum direction {LEFT, RIGHT};
  enum direction ballDirection = RIGHT; /* p1 serves */
  Vector2 ballSpeed = {newSpeed(), newSpeed()};

  const float paddleSpeed = 850.0f;
  Rectangle paddleOne = { 10, 200, 25, 200 };
  Rectangle paddleTwo = { 765, 200, 25, 200 };

  bool collisionOne = false;	/* collision with paddle one */
  bool collisionTwo = false;	/* collision with paddle two */
  bool offScreen = false;
  
  int p1Score = 0;
  int p2Score = 0;
  
  while (!WindowShouldClose()) {
    // Check input & update positions
    if (IsKeyDown(KEY_W)) paddleOne.y -= paddleSpeed * GetFrameTime();
    if (IsKeyDown(KEY_S)) paddleOne.y += paddleSpeed * GetFrameTime();
    if (IsKeyDown(KEY_UP)) paddleTwo.y -= paddleSpeed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) paddleTwo.y += paddleSpeed * GetFrameTime();
    
    ball.x += ballSpeed.x * GetFrameTime();
    ball.y += ballSpeed.y * GetFrameTime();

    // Check for collision & boundries, update ball direction
    if (ball.y >= screenHeight - 25 || ball.y <= 0)
      ballSpeed.y *= -1;

    if (paddleOne.y < 0) paddleOne.y = 0;
    if (paddleOne.y > screenHeight - 200) paddleOne.y = screenHeight - 200;
    if (paddleTwo.y < 0) paddleTwo.y = 0;
    if (paddleTwo.y > screenHeight - 200) paddleTwo.y = screenHeight - 200;

    collisionOne = CheckCollisionRecs(paddleOne, ball);
    collisionTwo = CheckCollisionRecs(paddleTwo, ball);

    if (collisionOne || collisionTwo) ballSpeed.x *= -1.1;
    // useful for later?
    /* if (collisionOne)  */
    /* if (collisionTwo)  */

    // Update Score

    if (ball.x < -25) {
      p2Score++;
      offScreen = true;
    }

    if (ball.x > 800) {
      p1Score++;
      offScreen = true;
    }    

    if (offScreen) {
      ballSpeed.x = newSpeed();	/* TODO randint this */
      ballSpeed.y = newSpeed();
      ball.x = screenWidth / 2 - 12;
      ball.y = screenHeight / 2 + 12; /* idk */
      offScreen = false;
    }
    
    // Draw
    BeginDrawing();
    {
      ClearBackground(BLACK);

      DrawRectangleRec(paddleOne, WHITE);
      DrawRectangleRec(paddleTwo, WHITE);
      DrawRectangleRec(ball, WHITE);

      DrawText(TextFormat("%i", p1Score), 50, 70, 30, WHITE);
      DrawText(TextFormat("%i", p2Score), 600, 70, 30, WHITE);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;  
}
