#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <windows.h>

#include "GameManager.h"

using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

Figure* currentFigure;

Vector2f oldCoordinate(0, 0);

int main() {
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess game");

	Texture BoardTexture;
	BoardTexture.loadFromFile("Images/Board.png");

	Sprite BoardSprite(BoardTexture);

	Event event;

	GameManager::Initialize();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) 
				window.close();
			
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape) 
					window.close();
			}
		}

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == Mouse::Left)
			{
				currentFigure = GameManager::GetFigureAtPosition(static_cast<int>(Mouse::getPosition(window).y / FIGURE_HEIGHT), static_cast<int>(Mouse::getPosition(window).x / FIGURE_WIDTH));

				if (currentFigure != nullptr &&
					((GameManager::GetGameState() == GameState::WhiteMove && currentFigure->GetFigureColor() == FigureColor::White) ||
						(GameManager::GetGameState() == GameState::BlackMove && currentFigure->GetFigureColor() == FigureColor::Black)))
				{
					oldCoordinate.x = currentFigure->GetWidth() * FIGURE_WIDTH;
					oldCoordinate.y = currentFigure->GetHeight() * FIGURE_HEIGHT;
				}
				else
					currentFigure = nullptr;
			}
		}

		if (event.type == Event::MouseButtonReleased)
		{
			if (event.key.code == Mouse::Left)
			{
				if (currentFigure != nullptr)
				{
					Position newPosition = Position(static_cast<int>((currentFigure->GetX() + FIGURE_WIDTH / 2) / FIGURE_WIDTH), static_cast<int>((currentFigure->GetY() + FIGURE_HEIGHT / 2) / FIGURE_HEIGHT));

					if (currentFigure->GetX() < 0 || currentFigure->GetX() > WINDOW_WIDTH || currentFigure->GetY() < 0 || currentFigure->GetY() > WINDOW_HEIGHT || 
						!currentFigure->IsMovePosible(newPosition) || GameManager::IsCheck(currentFigure, newPosition))
					{
						currentFigure->MoveToCoordinate(oldCoordinate.x, oldCoordinate.y);
					}
					else
					{
						currentFigure->MoveToPosition(newPosition);

						window.clear();
						window.draw(BoardSprite);

						for (int i = 0; i < BOARD_HEIGHT; ++i)
						{
							for (int j = 0; j < BOARD_WIDTH; ++j)
							{
								Figure* figure = GameManager::GetFigureAtPosition(i, j);

								if (figure != nullptr)
									window.draw(figure->GetSprite());
							}
						}

						if (currentFigure != nullptr)
							window.draw(currentFigure->GetSprite());

						window.display();

						if (GameManager::IsCheckMate(currentFigure))
						{
							int result = IDNO;
							if (GameManager::GetGameState() == GameState::BlackMove)
								result = MessageBoxA(NULL, "Check Mate! Black Win. Start New Game?", "End Game", MB_YESNO);
							else if (GameManager::GetGameState() == GameState::WhiteMove)
								result = MessageBoxA(NULL, "Check Mate! White Win. Start New Game?", "End Game", MB_YESNO);

							if (result == IDYES)
							{
								GameManager::RestartGame();
								currentFigure = nullptr;
								continue;
							}
							else if (result == IDNO)
							{
								window.close();
								break;
							}
						}

						if (GameManager::GetGameState() == GameState::BlackMove)
							GameManager::SetGameState(GameState::WhiteMove);
						else if (GameManager::GetGameState() == GameState::WhiteMove)
							GameManager::SetGameState(GameState::BlackMove);
					}

					currentFigure = nullptr;
				}
			}
		}

		if (currentFigure != nullptr)
			currentFigure->MoveToCoordinate(Mouse::getPosition(window).x - FIGURE_WIDTH / 2, Mouse::getPosition(window).y - FIGURE_HEIGHT / 2);

		window.clear();
		window.draw(BoardSprite);

		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				Figure* figure = GameManager::GetFigureAtPosition(i, j);

				if (figure != nullptr)
					window.draw(figure->GetSprite());
			}
		}

		if (currentFigure != nullptr)
			window.draw(currentFigure->GetSprite());

		window.display();
	}

	GameManager::Destroy();

	return 0;
}