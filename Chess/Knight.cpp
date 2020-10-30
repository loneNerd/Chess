#include "Knight.h"

Knight::Knight(FigureColor color, Position position)
{
	if (color == FigureColor::Black)
		this->texture.loadFromFile("Images/KnightBlack.png");
	else
		this->texture.loadFromFile("Images/KnightWhite.png");

	this->color = color;
	this->type = FigureType::Knight;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(-FIGURE_WIDTH - 10, -FIGURE_HEIGHT - 10);
	this->currentPosition.Width = position.Width;
	this->currentPosition.Height = position.Height;
}

bool Knight::IsMovePosible(Position newPosition)
{
	if (newPosition.Width < 0 || newPosition.Width >= BOARD_WIDTH || newPosition.Height < 0 || newPosition.Height >= BOARD_HEIGHT)
		return false;

	Figure* figure = GameManager::GetFigureAtPosition(newPosition.Height, newPosition.Width);

	return ((abs(newPosition.Height - currentPosition.Height) == 2 && abs(newPosition.Width - currentPosition.Width) == 1) ||
		(abs(newPosition.Height - currentPosition.Height) == 1 && abs(newPosition.Width - currentPosition.Width) == 2)) &&
		(figure == nullptr || figure->GetFigureColor() != GetFigureColor());
}

void Knight::MoveToPosition(Position newPosition)
{
	GameManager::RomeveFigureFromPosition(currentPosition.Height, currentPosition.Width);

	currentPosition = newPosition;

	MoveToCoordinate(currentPosition.Width * FIGURE_WIDTH, currentPosition.Height * FIGURE_HEIGHT);

	GameManager::SetFigureToPositionn(currentPosition.Height, currentPosition.Width, this);
}