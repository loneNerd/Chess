#include "King.h"

King::King(FigureColor color, Position position)
{
	if (color == FigureColor::Black)
		this->texture.loadFromFile("Images/KingBlack.png");
	else
		this->texture.loadFromFile("Images/KingWhite.png");

	this->color = color;
	this->type = FigureType::King;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(-FIGURE_WIDTH - 10, -FIGURE_HEIGHT - 10);
	this->currentPosition.Width = position.Width;
	this->currentPosition.Height = position.Height;
}

bool King::IsMovePosible(Position newPosition)
{
	if (newPosition.Width < 0 || newPosition.Width >= BOARD_WIDTH || newPosition.Height < 0 || newPosition.Height >= BOARD_HEIGHT)
		return false;

	Figure* figure = GameManager::GetFigureAtPosition(newPosition.Height, newPosition.Width);

	return (abs(currentPosition.Width - newPosition.Width) <= 1 &&
		abs(currentPosition.Height - newPosition.Height) <= 1 &&
		(figure == nullptr || figure->GetFigureColor() != GetFigureColor()));
}

void King::MoveToPosition(Position newPosition)
{
	GameManager::RomeveFigureFromPosition(currentPosition.Height, currentPosition.Width);

	currentPosition = newPosition;

	MoveToCoordinate(currentPosition.Width * FIGURE_WIDTH, currentPosition.Height * FIGURE_HEIGHT);

	GameManager::SetFigureToPositionn(currentPosition.Height, currentPosition.Width, this);
}