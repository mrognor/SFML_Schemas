#pragma once

#include "SchemasClasses.h"
#include "MovingPoleWidget.h"

#define PI 3.14159265  

/// Класс для объектов соединения нод на поле
class MovingPoleConnectionWidget
{
private:
	/// Переменная-указатель для родительского поля
	MovingPoleWidget* ParentMovingPoleWidget;

	/// Тело объекта соединения
	sf::RectangleShape ConnectionBody;

	/// Окно в котором рисуется объект
	sf::RenderWindow* Window;

	/// Переменная для начальной точки тела
	sf::Vector2f Start;

	/// Толщина соединения
	float ConnectionThickness = 10;

	/// Переменная для фиксации установки соединения
	bool IsConnectionNodePlaced = false;

	ConnectionTypes ConnectionType;

	InputNode* EntryNode_Input;
	OutputNode* EntryNode_Output;
	InputNode* ExitNode_Input = nullptr;
	OutputNode* ExitNode_Output = nullptr;

	bool Value = false;

public:
	/// Конструктор в котором начало соединения находится в выходе ноды
	MovingPoleConnectionWidget(sf::RenderWindow* window, MovingPoleWidget* parentMovingPoleWidget, OutputNode* entryNode);

	/// Конструктор в котором начало соединения находится во входе ноды
	MovingPoleConnectionWidget(sf::RenderWindow* window, MovingPoleWidget* parentMovingPoleWidget, InputNode* entryNode);

	void DrawElementToTexture();

	void InputHandler(sf::Event event);
	
	void Move(sf::Vector2f vec);

	void setExitNode(InputNode* exitNode) { ExitNode_Input = exitNode; }

	void setExitNode(OutputNode* exitNode) { ExitNode_Output = exitNode; }

	void UpdateConnectionElement();

	ConnectionTypes getConnectionType() { return ConnectionType; }

	~MovingPoleConnectionWidget();
};
