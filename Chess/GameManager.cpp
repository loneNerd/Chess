#include "GameManager.h"

King* kingWhite = new King(FigureColor::White, Position(4, 7));
King* kingBlack = new King(FigureColor::Black, Position(4, 0));

Queen* queenWhite = new Queen(FigureColor::White, Position(3, 7));
Queen* queenBlack = new Queen(FigureColor::Black, Position(3, 0));

Bishop* bishopWhiteLeft = new Bishop(FigureColor::White, Position(2, 7));
Bishop* bishopWhiteRight = new Bishop(FigureColor::White, Position(5, 7));
Bishop* bishopBlackLeft = new Bishop(FigureColor::Black, Position(2, 0));
Bishop* bishopBlackRight = new Bishop(FigureColor::Black, Position(5, 0));

Knight* knightWhiteLeft = new Knight(FigureColor::White, Position(1, 7));
Knight* knightWhiteRight = new Knight(FigureColor::White, Position(6, 7));
Knight* knightBlackLeft = new Knight(FigureColor::Black, Position(1, 0));
Knight* knightBlackRight = new Knight(FigureColor::Black, Position(6, 0));

Rook* rookWhiteLeft = new Rook(FigureColor::White, Position(0, 7));
Rook* rookWhiteRight = new Rook(FigureColor::White, Position(7, 7));
Rook* rookBlackLeft = new Rook(FigureColor::Black, Position(0, 0));
Rook* rookBlackRight = new Rook(FigureColor::Black, Position(7, 0));

Pawn* pawnWhite1 = new Pawn(FigureColor::White, Position(0, 6));
Pawn* pawnWhite2 = new Pawn(FigureColor::White, Position(1, 6));
Pawn* pawnWhite3 = new Pawn(FigureColor::White, Position(2, 6));
Pawn* pawnWhite4 = new Pawn(FigureColor::White, Position(3, 6));
Pawn* pawnWhite5 = new Pawn(FigureColor::White, Position(4, 6));
Pawn* pawnWhite6 = new Pawn(FigureColor::White, Position(5, 6));
Pawn* pawnWhite7 = new Pawn(FigureColor::White, Position(6, 6));
Pawn* pawnWhite8 = new Pawn(FigureColor::White, Position(7, 6));

Pawn* pawnBlack1 = new Pawn(FigureColor::Black, Position(0, 1));
Pawn* pawnBlack2 = new Pawn(FigureColor::Black, Position(1, 1));
Pawn* pawnBlack3 = new Pawn(FigureColor::Black, Position(2, 1));
Pawn* pawnBlack4 = new Pawn(FigureColor::Black, Position(3, 1));
Pawn* pawnBlack5 = new Pawn(FigureColor::Black, Position(4, 1));
Pawn* pawnBlack6 = new Pawn(FigureColor::Black, Position(5, 1));
Pawn* pawnBlack7 = new Pawn(FigureColor::Black, Position(6, 1));
Pawn* pawnBlack8 = new Pawn(FigureColor::Black, Position(7, 1));

Figure* GameManager::board[BOARD_HEIGHT][BOARD_WIDTH] = {
	rookBlackLeft, knightBlackLeft, bishopBlackLeft, queenBlack, kingBlack,  bishopBlackRight, knightBlackRight, rookBlackRight,
	pawnBlack1,	   pawnBlack2,      pawnBlack3,      pawnBlack4, pawnBlack5, pawnBlack6,       pawnBlack7,       pawnBlack8,
	nullptr,       nullptr,         nullptr,         nullptr,    nullptr,    nullptr,          nullptr,          nullptr,
	nullptr,       nullptr,         nullptr,         nullptr,    nullptr,    nullptr,          nullptr,          nullptr,
	nullptr,       nullptr,         nullptr,         nullptr,    nullptr,    nullptr,          nullptr,          nullptr,
	nullptr,       nullptr,         nullptr,         nullptr,    nullptr,    nullptr,          nullptr,          nullptr,
	pawnWhite1,    pawnWhite2,      pawnWhite3,      pawnWhite4, pawnWhite5, pawnWhite6,       pawnWhite7,       pawnWhite8,
	rookWhiteLeft, knightWhiteLeft, bishopWhiteLeft, queenWhite, kingWhite,  bishopWhiteRight, knightWhiteRight, rookWhiteRight,
};

GameState GameManager::gameState = GameState::WhiteMove;

void GameManager::Initialize() 
{
	for (int i = 0; i < BOARD_HEIGHT; ++i)
	{
		for (int j = 0; j < BOARD_WIDTH; ++j)
		{
			if (board[j][i] != nullptr)
				board[j][i]->MoveToCoordinate(i * FIGURE_WIDTH, j * FIGURE_HEIGHT);
		}
	}
}

void GameManager::Destroy() 
{
	for (int i = 0; i < BOARD_HEIGHT; ++i)
	{
		for (int j = 0; j < BOARD_WIDTH; ++j)
		{
			if (board[j][i] != nullptr)
				delete board[j][i];

			board[j][i] = nullptr;
		}
	}
}

void GameManager::DeleteFigureAtPosition(int height, int width)
{
	if (board[height][width] != nullptr)
		delete board[height][width];
}

void GameManager::SetFigureToPositionn(int height, int width, Figure* figure)
{
	if (board[height][width] != nullptr)
		delete board[height][width];

	board[height][width] = figure;
}

bool GameManager::IsCheck(Figure* figure, Position newPosition)
{
	bool isCheck = false;

	if (figure->GetFigureType() != FigureType::King)
	{
		Figure* temp;

		temp = board[newPosition.Height][newPosition.Width];
		board[newPosition.Height][newPosition.Width] = figure;
		board[figure->GetHeight()][figure->GetWidth()] = nullptr;

		Figure* king = figure->GetFigureColor() == FigureColor::Black ? kingBlack : kingWhite;

		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				if (board[i][j] != nullptr && board[i][j]->GetFigureColor() != figure->GetFigureColor() && board[i][j]->IsMovePosible(Position(king->GetWidth(), king->GetHeight())))
				{
					isCheck = true;
					break;
				}
			}
		}

		board[newPosition.Height][newPosition.Width] = temp;
		board[figure->GetHeight()][figure->GetWidth()] = figure;
	}
	else
	{
		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				if (board[i][j] != nullptr && board[i][j]->GetFigureColor() != figure->GetFigureColor() && board[i][j]->IsMovePosible(newPosition))
				{
					isCheck = true;
					break;
				}
			}
		}
	}

	return isCheck;
}

bool GameManager::IsCheckMate(Figure* figure)
{
	for (int height = 0; height < BOARD_HEIGHT; ++height)
	{
		for (int width = 0; width < BOARD_WIDTH; ++width)
		{
			if (board[height][width] != nullptr && board[height][width]->GetFigureColor() != figure->GetFigureColor())
			{
				for (int i = 0; i < BOARD_HEIGHT; ++i)
				{
					for (int j = 0; j < BOARD_WIDTH; ++j)
					{
						if (board[height][width]->IsMovePosible(Position(j, i)) && !GameManager::IsCheck(board[height][width], Position(j, i)))
							return false;
					}
				}
			}
		}
	}


	return true;
}

void GameManager::RestartGame()
{
	Destroy();

	kingWhite = new King(FigureColor::White, Position(4, 7));
	board[7][4] = kingWhite;
	
	kingBlack = new King(FigureColor::Black, Position(4, 0));
	board[0][4] = kingBlack;

	queenWhite = new Queen(FigureColor::White, Position(3, 7));
	board[7][3] = queenWhite;

	queenBlack = new Queen(FigureColor::Black, Position(3, 0));
	board[0][3] = queenBlack;

	bishopWhiteLeft = new Bishop(FigureColor::White, Position(2, 7));
	board[7][2] = bishopWhiteLeft;

	bishopWhiteRight = new Bishop(FigureColor::White, Position(5, 7));
	board[7][5] = bishopWhiteRight;

	bishopBlackLeft = new Bishop(FigureColor::Black, Position(2, 0));
	board[0][2] = bishopBlackLeft;
	
	bishopBlackRight = new Bishop(FigureColor::Black, Position(5, 0));
	board[0][5] = bishopBlackRight;

	knightWhiteLeft = new Knight(FigureColor::White, Position(1, 7));
	board[7][1] = knightWhiteLeft;
	
	knightWhiteRight = new Knight(FigureColor::White, Position(6, 7));
	board[7][6] = knightWhiteRight;
	
	knightBlackLeft = new Knight(FigureColor::Black, Position(1, 0));
	board[0][1] = knightBlackLeft;
	
	knightBlackRight = new Knight(FigureColor::Black, Position(6, 0));
	board[0][6] = knightBlackRight;

	rookWhiteLeft = new Rook(FigureColor::White, Position(0, 7));
	board[7][0] = rookWhiteLeft;
	
	rookWhiteRight = new Rook(FigureColor::White, Position(7, 7));
	board[7][7] = rookWhiteRight;
	
	rookBlackLeft = new Rook(FigureColor::Black, Position(0, 0));
	board[0][0] = rookBlackLeft;
	
	rookBlackRight = new Rook(FigureColor::Black, Position(7, 0));
	board[0][7] = rookBlackRight;

	pawnWhite1 = new Pawn(FigureColor::White, Position(0, 6));
	board[6][0] = pawnWhite1;
	
	pawnWhite2 = new Pawn(FigureColor::White, Position(1, 6));
	board[6][1] = pawnWhite2;
	
	pawnWhite3 = new Pawn(FigureColor::White, Position(2, 6));
	board[6][2] = pawnWhite3;
	
	pawnWhite4 = new Pawn(FigureColor::White, Position(3, 6));
	board[6][3] = pawnWhite4;
	
	pawnWhite5 = new Pawn(FigureColor::White, Position(4, 6));
	board[6][4] = pawnWhite5;
	
	pawnWhite6 = new Pawn(FigureColor::White, Position(5, 6));
	board[6][5] = pawnWhite6;
	
	pawnWhite7 = new Pawn(FigureColor::White, Position(6, 6));
	board[6][6] = pawnWhite7;

	pawnWhite8 = new Pawn(FigureColor::White, Position(7, 6));
	board[6][7] = pawnWhite8;

	pawnBlack1 = new Pawn(FigureColor::Black, Position(0, 1));
	board[1][0] = pawnBlack1;
	
	pawnBlack2 = new Pawn(FigureColor::Black, Position(1, 1));
	board[1][1] = pawnBlack2;
	
	pawnBlack3 = new Pawn(FigureColor::Black, Position(2, 1));
	board[1][2] = pawnBlack3;
	
	pawnBlack4 = new Pawn(FigureColor::Black, Position(3, 1));
	board[1][3] = pawnBlack4;
	
	pawnBlack5 = new Pawn(FigureColor::Black, Position(4, 1));
	board[1][4] = pawnBlack5;

	pawnBlack6 = new Pawn(FigureColor::Black, Position(5, 1));
	board[1][5] = pawnBlack6;
	
	pawnBlack7 = new Pawn(FigureColor::Black, Position(6, 1));
	board[1][6] = pawnBlack7;
	
	pawnBlack8 = new Pawn(FigureColor::Black, Position(7, 1));
	board[1][7] = pawnBlack8;

	Initialize();

	gameState = GameState::WhiteMove;
}