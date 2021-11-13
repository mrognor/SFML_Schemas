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

	ConnectionTypes ConnectionType;

	InputNode* EntryNode_Input;
	OutputNode* EntryNode_Output;
	InputNode* ExitNode_Input = nullptr;
	OutputNode* ExitNode_Output = nullptr;

public:
	///  онструктор в котором начало соединени€ находитс€ в выходе ноды
	MovingPoleConnectionWidget(sf::RenderWindow* window, MovingPoleWidget* parentMovingPoleWidget, OutputNode* entryNode);

	///  онструктор в котором начало соединени€ находитс€ во входе ноды
	MovingPoleConnectionWidget(sf::RenderWindow* window, MovingPoleWidget* parentMovingPoleWidget, InputNode* entryNode);

	void DrawElementToTexture();

	void InputHandler(sf::Event event);
	
	void Move(sf::Vector2f vec);

	void setExitNode(InputNode* exitNode) { ExitNode_Input = exitNode; }

	void setExitNode(OutputNode* exitNode) { ExitNode_Output = exitNode; }

	ConnectionTypes getConnectionType() { return ConnectionType; }

	~MovingPoleConnectionWidget();
};
