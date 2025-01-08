#include "completeLevel.h"
#include "input.h"
#include "stateHandlers.h"
#include <string.h>
#include "top5.h"
#include <stdio.h>

void drawCompleteLevelScreen(PLAYER *player, JOGADOR top5[], int lowerIndex, char *text) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), YELLOW);
    const char *title = "LEVEL COMPLETE";
    const char *retry = "Press ENTER to menu";
    const char *menu = "Press ESC to leave";
    const char *highscoreText = "YOU HAVE ACHIEVED A NEW HIGH SCORE";
    bool newHighScore = false;
    
    if (player->points > top5[lowerIndex].pontos) newHighScore = true;
    
    DrawText(title, 
        GetScreenWidth()/2 - MeasureText(title, 70)/2,
        GetScreenHeight()/2 - 250,
        70, DARKBLUE);
        
    if(newHighScore) {
        DrawText(highscoreText,
            GetScreenWidth()/2 - MeasureText(highscoreText, 30)/2,
            GetScreenHeight()/2 - 150,
            30, RED);
            
        int posx = 500;
        int posy = 300;

        DrawText("Type your name:",
            posx, posy,
            20, DARKGRAY);
            
        DrawRectangle(posx-70, posy+40, 320, 50, LIGHTGRAY);

        DrawText(text,
            posx - 60, posy + 50,
            30, MAROON);
    }
    
    DrawText(retry,
        GetScreenWidth()/2 - MeasureText(retry, 30)/2,
        GetScreenHeight()/2 + 200,
        30, DARKBLUE);
        
    DrawText(menu,
        GetScreenWidth()/2 - MeasureText(menu, 30)/2,
        GetScreenHeight()/2 + 250,
        30, DARKBLUE);
}

void updateAndDrawCompleteLevelScreen(GameState *currentState, PLAYER *player, ENEMY enemies[], int *n_enemies, BLOCK blocks[], int *n_blocks, JOGADOR top5[], int lowerIndex, char *text, int *letterCount, char *fileName) {
    if (IsKeyPressed(KEY_ENTER)) {
        if(player->points > top5[lowerIndex].pontos){
            JOGADOR novoj;
            strcpy(novoj.nome, text);
            novoj.pontos = player->points;
            
            trocaJogadorCompleto(&novoj, lowerIndex, top5, fileName);
            le_arquivo(fileName, top5);
            
        }
        resetGameState(player, enemies, n_enemies, blocks, n_blocks);
        
        *currentState = MENU_STATE;
    }

    handleInput(text, letterCount);

    drawCompleteLevelScreen(player, top5, lowerIndex, text);
}
