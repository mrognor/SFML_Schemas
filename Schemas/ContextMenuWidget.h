#pragma once

#include "SchemasClasses.h"
#include "DropDownListWidget.h"
#include "DropDownListElementWidget.h"


class ContextMenuWidget
{
private:
	/// Переменная для окна в котором выполняется операции контекстного меню
	sf::RenderWindow* ContextMenuWidgetWindow;

	/// Переменная-указатель(RectangleShape) для отображения объекта при вызове контекстного меню
	sf::RectangleShape* ContextMenuWidgetShape;

	bool IsRendering = false;
	
	bool IsMouseOnShape = false;

public:
	ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow);

	void Tick();

	/// Обработчик ввода 
	void InputHandler(sf::Event event);

	void OpenContextMenu();

	void CloseContextMenu();

	bool getIsMouseOnShape() { return IsMouseOnShape; }

	~ContextMenuWidget();
};

