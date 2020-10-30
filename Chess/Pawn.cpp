#include "Pawn.h"

Pawn::Pawn(FigureColor color, Position position)
{
	if (color == FigureColor::Black)
		this->texture.loadFromFile("Images/PawnBlack.png");
	else
		this->texture.loadFromFile("Images/PawnWhite.png");

	this->color = color;
	this->type = FigureType::Pawn;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(-FIGURE_WIDTH - 10, -FIGURE_HEIGHT - 10);
	this->currentPosition.Width = position.Width;
	this->currentPosition.Height = position.Height;
}

bool Pawn::IsMovePosible(Position newPosition)
{
	if (newPosition.Width < 0 || newPosition.Width >= BOARD_WIDTH || newPosition.Height < 0 || newPosition.Height >= BOARD_HEIGHT)
		return false;

	if (GetFigureColor() == FigureColor::Black && currentPosition.Height == 1 && newPosition.Height - currentPosition.Height == 2)
	{
		if (currentPosition.Height < newPosition.Height && currentPosition.Width == newPosition.Width &&
			GameManager::GetFigureAtPosition(currentPosition.Height + 1, currentPosition.Width) == nullptr &&
			GameManager::GetFigureAtPosition(currentPosition.Height + 2, currentPosition.Width) == nullptr)
		{
			return true;
		}
	}
	else if (GetFigureColor() == FigureColor::Black)
	{
		if (currentPosition.Height < newPosition.Height && newPosition.Height - currentPosition.Height == 1 && currentPosition.Width == newPosition.Width &&
			GameManager::GetFigureAtPosition(currentPosition.Height + 1, currentPosition.Width) == nullptr)
		{
			return true;

		}
		else if (abs(currentPosition.Width - newPosition.Width) == 1 && currentPosition.Height < newPosition.Height && newPosition.Height - currentPosition.Height == 1 &&
			GameManager::GetFigureAtPosition(newPosition.Height, newPosition.Width) != nullptr &&
			GameManager::GetFigureAtPosition(newPosition.Height, newPosition.Width)->GetFigureColor() != GetFigureColor())
		{
			return true;
		}
	}
	else if (GetFigureColor() == FigureColor::White && currentPosition.Height == 6 && currentPosition.Height - newPosition.Height == 2)
	{
		if (currentPosition.Height > newPosition.Height && currentPosition.Width == newPosition.Width &&
			GameManager::GetFigureAtPosition(currentPosition.Height - 1, currentPosition.Width) == nullptr &&
			GameManager::GetFigureAtPosition(currentPosition.Height - 2, currentPosition.Width) == nullptr)
		{
			return true;
		}
	}
	else if (GetFigureColor() == FigureColor::White)
	{
		if (currentPosition.Height > newPosition.Height && currentPosition.Height - newPosition.Height == 1 && currentPosition.Width == newPosition.Width &&
			GameManager::GetFigureAtPosition(currentPosition.Height - 1, currentPosition.Width) == nullptr)
		{
			return true;

		}
		else if (abs(currentPosition.Width - newPosition.Width) == 1 && currentPosition.Height > newPosition.Height && currentPosition.Height - newPosition.Height == 1 &&
			GameManager::GetFigureAtPosition(newPosition.Height, newPosition.Width) != nullptr &&
			GameManager::GetFigureAtPosition(newPosition.Height, newPosition.Width)->GetFigureColor() != GetFigureColor())
		{
			return true;
		}
	}

	return false;
}

void Pawn::MoveToPosition(Position newPosition)
{
	GameManager::RomeveFigureFromPosition(currentPosition.Height, currentPosition.Width);

	currentPosition = newPosition;

	MoveToCoordinate(currentPosition.Width * FIGURE_WIDTH, currentPosition.Height * FIGURE_HEIGHT);

	GameManager::SetFigureToPositionn(currentPosition.Height, currentPosition.Width, this);

	if((GetFigureColor() == FigureColor::Black && currentPosition.Height == 7) || (GetFigureColor() == FigureColor::White && currentPosition.Height == 0))
	{
		Figure* figure;

		if (currentPosition.Width == 0 || currentPosition.Width == 7)
			figure = new Rook(GetFigureColor(), Position(currentPosition.Width, currentPosition.Height));
		else if (currentPosition.Width == 1 || currentPosition.Width == 6)
			figure = new Knight(GetFigureColor(), Position(currentPosition.Width, currentPosition.Height));
		else if (currentPosition.Width == 2 || currentPosition.Width == 5)
			figure = new Bishop(GetFigureColor(), Position(currentPosition.Width, currentPosition.Height));
		else if (currentPosition.Width == 3 || currentPosition.Width == 4)
			figure = new Queen(GetFigureColor(), Position(currentPosition.Width, currentPosition.Height));
		else
			figure = nullptr;

		if (figure != nullptr)
		{
			figure->MoveToCoordinate(currentPosition.Width * 100, currentPosition.Height * 100);
			GameManager::SetFigureToPositionn(currentPosition.Height, currentPosition.Width, figure);
		}
	}
}