#pragma once
#ifndef ROOK_H_
#define ROOK_H_

#include <SFML/Graphics.hpp>
#include <cmath>

#include "GameManager.h"
#include "Figure.h"

class Rook : public Figure {
public:
	Rook(FigureColor color, Position position);
	void MoveToPosition(Position newPosition) override;
	bool IsMovePosible(Position newPosition) override;
	FigureType GetFigureType() const override { return this->type; }
	FigureColor GetFigureColor() const override { return this->color; }
	void MoveToCoordinate(int x, int y) override { this->sprite.setPosition(x, y); }
	const sf::Sprite& GetSprite() const override { return this->sprite; }
	inline int GetX() const override { return this->sprite.getPosition().x; }
	inline int GetY() const override { return this->sprite.getPosition().y; }
	inline int GetWidth() const override { return this->currentPosition.Width; }
	inline int GetHeight() const override { return this->currentPosition.Height; }

private:
	sf::Texture texture;
	sf::Sprite sprite;
	FigureType type;
	FigureColor color;
	Position currentPosition;
};

#endif //ROOK_H_
