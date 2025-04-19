#include "raylib.h"
#include "player_input.h"

#define BUTTON_SIZE 100
#define BUTTON_PADDING 10

class Test {
private:
    int i = 0;
};

class SubTest : Test {

};

int main(void) {
    InitWindow(800, 600, "Dynamic Player Join Example");

    PlayerInput players[MAX_PLAYERS];
    int playerCount = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 入力チェック → プレイヤー登録
        if (!IsKeyboardUsed()) {
            if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
                if (playerCount < MAX_PLAYERS) {
                    InitPlayerInput(&players[playerCount], playerCount + 1, INPUT_KEYBOARD, -1);
                    RegisterKeyboardUsage();
                    playerCount++;
                }
            }
        }

        for (int gp = 0; gp < 4; gp++) {
            if (IsGamepadAvailable(gp)) {
                if (IsGamepadButtonPressed(gp, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
                    bool alreadyUsed = false;
                    for (int i = 0; i < playerCount; i++) {
                        if (players[i].inputType == INPUT_GAMEPAD && players[i].gamepadId == gp) {
                            alreadyUsed = true;
                            break;
                        }
                    }
                    if (!alreadyUsed && playerCount < MAX_PLAYERS) {
                        InitPlayerInput(&players[playerCount], playerCount + 1, INPUT_GAMEPAD, gp);
                        playerCount++;
                    }
                }
            }
        }

        // 入力更新
        for (int i = 0; i < playerCount; i++) {
            UpdatePlayerInput(&players[i]);
        }

        // 描画
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int y = 0; y < GRID_SIZE; y++) {
            for (int x = 0; x < GRID_SIZE; x++) {
                int posX = x * (BUTTON_SIZE + BUTTON_PADDING) + 100;
                int posY = y * (BUTTON_SIZE + BUTTON_PADDING) + 50;
                Rectangle btn = { posX, posY, BUTTON_SIZE, BUTTON_SIZE };
                DrawRectangleRec(btn, LIGHTGRAY);

                for (int i = 0; i < playerCount; i++) {
                    if (players[i].selectX == x && players[i].selectY == y)
                        DrawRectangleLinesEx(btn, 4, players[i].color);
                }
            }
        }

        DrawText("Press WASD or Gamepad to Join", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
