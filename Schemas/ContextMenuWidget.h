#pragma once

#include "SchemasClasses.h"
#include "DropDownListWidget.h"
#include "DropDownListElementWidget.h"
#include "TextInputWidget.h"

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

	/// ����������-���������(RectangleShape) ����������� ������� ��� ������ ���� ������������� 
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetShape;

	TextInputWidget* ContextMenuWidgetRenameButtonTextInputWidget;

	/// ����������-���������(RectangleShape) ��� ����������� ������ "��" ��� ������ ���� �������������
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetAcceptShape;

	/// ����������-���������(RectangleShape) ��� ����������� ������ "���" ��� ������ ���� �������������
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetDeclineShape;


	bool IsRendering = false;
	
	bool IsMouseOnShape = false;

	bool IsConfirmWidgetRendering = false;

public:
	ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow);

	void Tick();

	/// ���������� ����� 
	void InputHandler(sf::Event event);

	void OpenContextMenu();

	void CloseContextMenu();

	bool getIsMouseOnShape() { return IsMouseOnShape; }

	void OpenConfirmWidget();

	~ContextMenuWidget();
};

