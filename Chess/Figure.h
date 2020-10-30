#pragma once
#ifndef FIGURE_H_
#define FIGURE_H_

#include <SFML/Graphics.hpp>

enum class FigureType {
	King,
	Queen,
	Bishop,
	Knight,
	Rook,
	Pawn
};

enum class FigureColor {
	White,
	Black
};

struct Position {
	Position()
	{
		this->Width = 0;
		this->Height = 0;
	}

	Position(int width, int height)
	{
		this->Width = width;
		this->Height = height;
	}

	Position(const Position& position)
	{
		this->Width = position.Width;
		this->Height = position.Height;
	}

	Position& operator= (const Position& position)
	{
		this->Width = position.Width;
		this->Height = position.Height;
		return *this;
	}

	int Width;
	int Height;
};

const int FIGURE_HEIGHT = 100;
const int FIGURE_WIDTH = 100;

class Figure {
public:
	virtual void MoveToPosition(Position newPosition) = 0;
	virtual bool IsMovePosible(Position newPosition) = 0;
	virtual void MoveToCoordinate(int x, int y) = 0;
	virtual FigureType GetFigureType() const = 0;
	virtual FigureColor GetFigureColor() const = 0;
	virtual const sf::Sprite& GetSprite() const = 0;
	virtual inline int GetX() const = 0;
	virtual inline int GetY() const = 0;
	virtual inline int GetWidth() const = 0;
	virtual inline int GetHeight() const = 0;
};

#endif //FIGURE_H_