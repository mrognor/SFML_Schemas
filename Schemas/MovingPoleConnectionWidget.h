#pragma once

#include "SchemasClasses.h"
#include "MovingPoleWidget.h"

#define PI 3.14159265  


class MovingPoleConnectionWidget
{
private:
	MovingPoleWidget* ParentMovingPoleWidget;

	sf::RectangleShape ConnectionBody;

	sf::RenderWindow* Window;

	sf::Vector2f Start;

	float ConnectionThickness = 10;

	bool IsConnectionNodePlaced = false;

	OutputNode* EntryNode;
	InputNode* ExitNode = nullptr;

public:
	MovingPoleConnectionWidget(sf::RenderWindow* window, MovingPoleWidget* parentMovingPoleWidget, OutputNode* entryNode);

	void DrawElementToTexture();

	void InputHandler(sf::Event event);
	
	void Move(sf::Vector2f vec);

	void setExitNode(InputNode* exitNode) { ExitNode = exitNode; }

	~MovingPoleConnectionWidget();
};
