#pragma once

#include "SchemasClasses.h"
#include "DropDownListWidget.h"
#include "DropDownListElementWidget.h"


class ContextMenuWidget
{
private:
	/// ���������� ��� ���� � ������� ����������� �������� ������������ ����
	sf::RenderWindow* ContextMenuWidgetWindow;

	/// ����������-���������(RectangleShape) ��� ����������� ������� ��� ������ ������������ ����
	sf::RectangleShape* ContextMenuWidgetShape;

	bool IsRendering = false;
	
	bool IsMouseOnShape = false;

public:
	ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow);

	void Tick();

	/// ���������� ����� 
	void InputHandler(sf::Event event);

	void OpenContextMenu();

	void CloseContextMenu();

	bool getIsMouseOnShape() { return IsMouseOnShape; }

	~ContextMenuWidget();
};

