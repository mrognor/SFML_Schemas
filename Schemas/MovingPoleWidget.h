#pragma once

#include "SchemasClasses.h"

class MovingPoleWidget
{
private:
	sf::RenderWindow* MovingPoleWidgetWindow;

	sf::RectangleShape ShapeToTest;

	sf::Vector2f LastMouseCoords;

	sf::RenderTexture* Texture;
	sf::Sprite* Sprite;

	bool IsDragStarted = false;

public:
	MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow);

	void Tick();

	void InputHandler(sf::Event event);

	~MovingPoleWidget();
};

