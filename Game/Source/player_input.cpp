#include "player_input.h"

static bool keyboardUsed = false;

void RegisterKeyboardUsage() {
    keyboardUsed = true;
}

bool IsKeyboardUsed() {
    return keyboardUsed;
}

void InitPlayerInput(PlayerInput* player, int id, InputType type, int gamepadId) {
    player->id = id;
    Color color;
    color.r = (unsigned char)GetRandomValue(50, 255);
    color.g = (unsigned char)GetRandomValue(50, 255);
    color.b = (unsigned char)GetRandomValue(50, 255);
    color.a = 255;

    player->color = color;

    player->selectX = GetRandomValue(0, GRID_SIZE - 1);
    player->selectY = GetRandomValue(0, GRID_SIZE - 1);
    player->inputType = type;
    player->gamepadId = gamepadId;
    player->usesKeyboard = (type == INPUT_KEYBOARD);
}

void UpdatePlayerInput(PlayerInput* player) {
    if (player->inputType == INPUT_KEYBOARD) {
        if (IsKeyPressed(KEY_W)) player->selectY = (player->selectY - 1 + GRID_SIZE) % GRID_SIZE;
        if (IsKeyPressed(KEY_S)) player->selectY = (player->selectY + 1) % GRID_SIZE;
        if (IsKeyPressed(KEY_A)) player->selectX = (player->selectX - 1 + GRID_SIZE) % GRID_SIZE;
        if (IsKeyPressed(KEY_D)) player->selectX = (player->selectX + 1) % GRID_SIZE;
    }
    else if (player->inputType == INPUT_GAMEPAD && IsGamepadAvailable(player->gamepadId)) {
        if (IsGamepadButtonPressed(player->gamepadId, GAMEPAD_BUTTON_LEFT_FACE_UP))
            player->selectY = (player->selectY - 1 + GRID_SIZE) % GRID_SIZE;
        if (IsGamepadButtonPressed(player->gamepadId, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
            player->selectY = (player->selectY + 1) % GRID_SIZE;
        if (IsGamepadButtonPressed(player->gamepadId, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
            player->selectX = (player->selectX - 1 + GRID_SIZE) % GRID_SIZE;
        if (IsGamepadButtonPressed(player->gamepadId, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
            player->selectX = (player->selectX + 1) % GRID_SIZE;
    }
}
