#pragma once
#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Figure.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

enum class GameState {
	BlackMove,
	WhiteMove
};

class GameManager
{
public:
	static void Initialize();
	static void Destroy();
	static Figure* GetFigureAtPosition(int height, int width) { return board[height][width]; }
	static void DeleteFigureAtPosition(int height, int width);
	static void RomeveFigureFromPosition(int height, int width) { board[height][width] = nullptr; }
	static void SetFigureToPositionn(int height, int width, Figure* figure);
	static const GameState& GetGameState() { return gameState; }
	static const void SetGameState(GameState state) { gameState = state; }
	static bool IsCheck(Figure* figure, Position newPosition);
	static bool IsCheckMate(Figure* figure);
	static void RestartGame();

private:
	static Figure* board[BOARD_HEIGHT][BOARD_WIDTH];
	static GameState gameState;

};

#endif //GAMEMANAGER_H_
