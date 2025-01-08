#include "raylib.h"
#include "input.h"
#include <string.h>

void handleInput(char *text, int *letterCount) {
    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (*letterCount < MAX_INPUT_LENGTH)) {
            text[*letterCount] = (char)key;
            text[*letterCount + 1] = '\0';
            *letterCount = *letterCount + 1;
        }
        key = GetCharPressed();
    }
    
    if (IsKeyPressed(KEY_BACKSPACE)) {
        *letterCount = *letterCount - 1;
        if (*letterCount < 0) *letterCount = 0;
        text[*letterCount] = '\0';
    }
}