#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "raylib.h"

#define GRID_SIZE 4
#define MAX_PLAYERS 8

typedef enum {
    INPUT_NONE,
    INPUT_KEYBOARD,
    INPUT_GAMEPAD
} InputType;

typedef struct PlayerInput {
    int id;
    Color color;
    int selectX, selectY;

    InputType inputType;
    int gamepadId;

    // �L�[�{�[�h�p
    bool usesKeyboard;
} PlayerInput;

void InitPlayerInput(PlayerInput* player, int id, InputType type, int gamepadId);
void UpdatePlayerInput(PlayerInput* player);
bool IsKeyboardUsed();
void RegisterKeyboardUsage(); // �L�[�{�[�h��1�l�����g���Ȃ��Ɖ���

#endif
