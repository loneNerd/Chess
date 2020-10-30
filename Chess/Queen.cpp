#include "Queen.h"

Queen::Queen(FigureColor color, Position position)
{
	if (color == FigureColor::Black)
		this->texture.loadFromFile("Images/QueenBlack.png");
	else
		this->texture.loadFromFile("Images/QueenWhite.png");

	this->color = color;
	this->type = FigureType::Queen;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(-FIGURE_WIDTH - 10, -FIGURE_HEIGHT - 10);
	this->currentPosition.Width = position.Width;
	this->currentPosition.Height = position.Height;
}

bool Queen::IsMovePosible(Position newPosition)
{
	if (newPosition.Width < 0 || newPosition.Width >= BOARD_WIDTH || newPosition.Height < 0 || newPosition.Height >= BOARD_HEIGHT)
		return false;

	Figure* figure;

	int movesCount = 0;
	int directionWidth = 1;
	int directionHeight = 1;
	int isWidthStraight = 0;
	int isHeightStraight = 0;

	if (newPosition.Width == currentPosition.Width)
	{
		if (currentPosition.Height > newPosition.Height)
		{
			directionWidth = 1;
			directionHeight = -1;
			isWidthStraight = 0;
			isHeightStraight = 1;
			movesCount = currentPosition.Height - newPosition.Height;
		}
		else if (currentPosition.Height < newPosition.Height)
		{
			directionWidth = 1;
			directionHeight = 1;
			isWidthStraight = 0;
			isHeightStraight = 1;
			movesCount = newPosition.Height - currentPosition.Height;
		}
	}
	else if (newPosition.Height == currentPosition.Height)
	{
		if (currentPosition.Width > newPosition.Width)
		{
			directionWidth = -1;
			directionHeight = 1;
			isWidthStraight = 1;
			isHeightStraight = 0;
			movesCount = currentPosition.Width - newPosition.Width;
		}
		else if (currentPosition.Width < newPosition.Width)
		{
			directionWidth = 1;
			directionHeight = 1;
			isWidthStraight = 1;
			isHeightStraight = 0;
			movesCount = newPosition.Width - currentPosition.Width;
		}
	}
	else if (abs(currentPosition.Width - newPosition.Width) == abs(newPosition.Height - currentPosition.Height))
	{
		movesCount = abs(newPosition.Width - currentPosition.Width);

		if (newPosition.Width > currentPosition.Width && currentPosition.Height > newPosition.Height)
		{
			directionWidth = 1;
			directionHeight = -1;
			isWidthStraight = 1;
			isHeightStraight = 1;
		}
		else if (newPosition.Width > currentPosition.Width && currentPosition.Height < newPosition.Height)
		{
			directionWidth = 1;
			directionHeight = 1;
			isWidthStraight = 1;
			isHeightStraight = 1;
		}
		else if (newPosition.Width < currentPosition.Width && currentPosition.Height > newPosition.Height)
		{
			directionWidth = -1;
			directionHeight = -1;
			isWidthStraight = 1;
			isHeightStraight = 1;
		}
		else if (newPosition.Width < currentPosition.Width && currentPosition.Height < newPosition.Height)
		{
			directionWidth = -1;
			directionHeight = 1;
			isWidthStraight = 1;
			isHeightStraight = 1;
		}
	}
	else
		return false;

	for (int i = 1; i < movesCount; ++i)
	{
		figure = GameManager::GetFigureAtPosition(currentPosition.Height + isHeightStraight * directionHeight * i, currentPosition.Width + isWidthStraight * directionWidth * i);

		if (figure != nullptr)
		{
			return false;
			break;
		}
	}

	figure = GameManager::GetFigureAtPosition(newPosition.Height, newPosition.Width);
	if (figure != nullptr && figure->GetFigureColor() == GetFigureColor())
		return false;

	return true;
}

void Queen::MoveToPosition(Position newPosition)
{
	GameManager::RomeveFigureFromPosition(currentPosition.Height, currentPosition.Width);

	currentPosition = newPosition;

	MoveToCoordinate(currentPosition.Width * FIGURE_WIDTH, currentPosition.Height * FIGURE_HEIGHT);

	GameManager::SetFigureToPositionn(currentPosition.Height, currentPosition.Width, this);
}