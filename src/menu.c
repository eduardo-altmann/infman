#include "raylib.h"
#include "game_structs.h"
#include <stdio.h>
#include "map.h"
#include "stateHandlers.h"
#include "top5.h"

void drawMenu() {

    //carrega textura
    Texture2D logo = LoadTexture("assets/sprites/inf_man.png");

    //pega a posição do mouse
	Vector2 mouse = GetMousePosition();

    //botão "play"
	Rectangle play = {
	    (GetScreenWidth() / 2) - MeasureText("Play", 70) / 2,
        GetScreenHeight() / 2,
        MeasureText("Play", 70),
        70 };

    //botão "scoreboard"
	Rectangle scoreBoard = {
	    (GetScreenWidth() / 2) - MeasureText("LeaderBoard", 70) / 2,
        (GetScreenHeight() / 2) + 80,
        MeasureText("LeaderBoard", 70),
        70 };

    //botão "quit"
	Rectangle quit = {
        (GetScreenWidth() / 2) - MeasureText("Quit", 70) / 2,
        (GetScreenHeight() / 2) + 160,
        MeasureText("Quit", 70),
        70 };

    //desenha o fundo azul-escuro
	DrawRectangle(
		0,
		0,
		GetScreenWidth(),
		GetScreenHeight(),
		DARKBLUE);

    //desenha o letreiro do menu
	DrawTexture(logo,
		600-250,
		GetScreenHeight() / 2 - 150,
		RAYWHITE);

    //muda a cor do botão "play" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, play)) {
		DrawRectangleRec(
			play,
			BLUE
		);
	}


    //muda a cor do botão "scoreBoard" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, scoreBoard))
		DrawRectangleRec(
			scoreBoard,
			BLUE
		);


    //muda a cor do botão "quit" caso o mouse esteja em cima dele
	if (CheckCollisionPointRec(mouse, quit))
		DrawRectangleRec(
			quit,
			BLUE
		);

    //escreve "Play" acima do botão correspondente
	DrawText(
		"Play",
		(GetScreenWidth() / 2) - MeasureText("Play", 70) / 2,
		GetScreenHeight() / 2,
		70,
		WHITE
	);

	//escreve "LeaderBoard" acima do botão correspondente
	DrawText(
		"LeaderBoard",
		(GetScreenWidth() / 2) - MeasureText("LeaderBoard", 70) / 2,
		(GetScreenHeight() / 2) + 80,
		70,
		WHITE
	);

	//escreve "Quit" acima do botão correspondente
	DrawText(
		"Quit",
		(GetScreenWidth() / 2) - MeasureText("Quit", 70) / 2,
		(GetScreenHeight() / 2) + 160,
		70,
		WHITE
	);

}

void updateAndDrawMenu(GameState *currentState, char fileName[], BLOCK blocks[], int *n_blocks, PLAYER *player, ENEMY enemies[], int *n_enemies) {
    Vector2 mouse = GetMousePosition();
    
    Rectangle play = {
        (GetScreenWidth() / 2) - MeasureText("Play", 70) / 2,
        GetScreenHeight() / 2,
        MeasureText("Play", 70),
        70 
    };
    
    Rectangle scoreBoard = {
        (GetScreenWidth() / 2) - MeasureText("LeaderBoard", 70) / 2,
        (GetScreenHeight() / 2) + 80,
        MeasureText("LeaderBoard", 70),
        70 
    };
    
    Rectangle quit = {
        (GetScreenWidth() / 2) - MeasureText("Quit", 70) / 2,
        (GetScreenHeight() / 2) + 160,
        MeasureText("Quit", 70),
        70 
    };

    if (CheckCollisionPointRec(mouse, play) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        resetGameState(player, enemies, n_enemies, blocks, n_blocks);
        parseMap(fileName, blocks, n_blocks, player, enemies, n_enemies);
        *currentState = GAME_STATE;
        
    }

    if (CheckCollisionPointRec(mouse, scoreBoard) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        
        *currentState = SCORE_STATE;
        
    }
    
    if (CheckCollisionPointRec(mouse, quit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        CloseWindow();
    }
    
    drawMenu();
}

void drawDeathScreen() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    
    const char *gameOver = "GAME OVER";
    const char *retry = "Press ENTER to menu";
    const char *menu = "Press ESC to leave";
    
    DrawText(gameOver, 
        GetScreenWidth()/2 - MeasureText(gameOver, 70)/2,
        GetScreenHeight()/2 - 100,
        70, RED);
        
    DrawText(retry,
        GetScreenWidth()/2 - MeasureText(retry, 30)/2,
        GetScreenHeight()/2,
        30, WHITE);
        
    DrawText(menu,
        GetScreenWidth()/2 - MeasureText(menu, 30)/2,
        GetScreenHeight()/2 + 50,
        30, WHITE);
}

void updateDeathScreen(GameState *currentState, PLAYER *player, ENEMY enemies[], int *n_enemies, BLOCK blocks[], int *n_blocks) {
    if (IsKeyPressed(KEY_ENTER)) {
        resetGameState(player, enemies, n_enemies, blocks, n_blocks);

        *currentState = MENU_STATE;
    }
}

void drawScoreBoard(JOGADOR top5[]){
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKBLUE);

    const char *title = "Score board";
    const char *retry = "Press ENTER to menu";
    const char *menu = "Press ESC to leave";

    for (int i = 0; i < 5; i++){
        char *name = top5[i].nome;

        int points = top5[i].pontos;
        char pointsText[12];
        sprintf(pointsText, "%d", points);

        DrawText(name, 
        280,
        GetScreenHeight()/2 - 180 + (i*60),
        50, YELLOW);

        DrawText(pointsText, 
        800,
        GetScreenHeight()/2 - 180 + (i*60),
        50, YELLOW);
    }

    DrawText(title, 
        GetScreenWidth()/2 - MeasureText(title, 70)/2,
        GetScreenHeight()/2 - 290,
        70, WHITE);
        
    DrawText(retry,
        GetScreenWidth()/2 - MeasureText(retry, 30)/2,
        GetScreenHeight()/2 +210,
        30, WHITE);
        
    DrawText(menu,
        GetScreenWidth()/2 - MeasureText(menu, 30)/2,
        GetScreenHeight()/2 + 260,
        30, WHITE);
}

void updateAndDrawScoreScreen(GameState *currentState, JOGADOR top5[]) {
    if (IsKeyPressed(KEY_ENTER)) {
        *currentState = MENU_STATE;
    }
    drawScoreBoard(top5);
}
