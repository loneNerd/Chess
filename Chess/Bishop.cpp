#include "Bishop.h"

Bishop::Bishop(FigureColor color, Position position)
{
	if (color == FigureColor::Black)
		this->texture.loadFromFile("Images/BishopBlack.png");
	else
		this->texture.loadFromFile("Images/BishopWhite.png");

	this->color = color;
	this->type = FigureType::Bishop;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(-FIGURE_WIDTH - 10, -FIGURE_HEIGHT - 10);
	this->currentPosition.Width = position.Width;
	this->currentPosition.Height = position.Height;
}

bool Bishop::IsMovePosible(Position newPosition)
{
	if (newPosition.Width < 0 || newPosition.Width >= BOARD_WIDTH || newPosition.Height < 0 || newPosition.Height >= BOARD_HEIGHT)
		return false;

	Figure* figure;

	int directionWidth = 1;
	int directionHeight = 1;

	if (abs(newPosition.Height - currentPosition.Height) == abs(newPosition.Width - currentPosition.Width))
	{
		if (newPosition.Width > currentPosition.Width && currentPosition.Height > newPosition.Height)
		{
			directionWidth = 1;
			directionHeight = -1;
		}
		else if (newPosition.Width > currentPosition.Width && currentPosition.Height < newPosition.Height)
		{
			directionWidth = 1;
			directionHeight = 1;
		}
		else if (newPosition.Width < currentPosition.Width && currentPosition.Height > newPosition.Height)
		{
			directionWidth = -1;
			directionHeight = -1;
		}
		else if (newPosition.Width < currentPosition.Width && currentPosition.Height < newPosition.Height)
		{
			directionWidth = -1;
			directionHeight = 1;
		}
	}
	else
		return false;

	for (int i = 1; i < abs(currentPosition.Height - newPosition.Height); ++i)
	{
		figure = GameManager::GetFigureAtPosition(currentPosition.Height + directionHeight * i, currentPosition.Width + directionWidth * i);
		if (figure != nullptr)
		{
			return false;
		}
	}

	figure = GameManager::GetFigureAtPosition(newPosition.Height, newPosition.Width);
	if (figure != nullptr && figure->GetFigureColor() == GetFigureColor())
		return false;

	return true;
}

void Bishop::MoveToPosition(Position newPosition)
{
	GameManager::RomeveFigureFromPosition(currentPosition.Height, currentPosition.Width);

	currentPosition = newPosition;

	MoveToCoordinate(currentPosition.Width * FIGURE_WIDTH, currentPosition.Height * FIGURE_HEIGHT);

	GameManager::SetFigureToPositionn(currentPosition.Height, currentPosition.Width, this);
}