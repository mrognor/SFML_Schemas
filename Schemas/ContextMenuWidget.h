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

	/// ����������-���������(RectangleShape) ��� ����������� ������ ��� ���������� ���
	sf::RectangleShape* ContextMenuWidgetAddButton;

	/// ����������-���������(Text) ��� ����������� ������ ��� ���������� ���
	sf::Text* ContextMenuWidgetAddButtonText;

	/// ����������-���������(RectangleShape) ��� ����������� ������ ��� �������������� ���
	sf::RectangleShape* ContextMenuWidgetRenameButton;

	/// ����������-���������(Text) ��� ����������� ������ ��� �������������� ���
	sf::Text* ContextMenuWidgetRenameButtonText;

	/// ����������-���������(RectangleShape) ��� ����������� ������ ��� �������� ���
	sf::RectangleShape* ContextMenuWidgetDeleteButton;

	/// ����������-���������(Text)  ��� ����������� ������ ��� �������� ���
	sf::Text* ContextMenuWidgetDeleteButtonText;

	/// ����� 
	sf::Font font;

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

