#pragma once

#include "SchemasClasses.h"
#include "DropDownListWidget.h"
#include "DropDownListElementWidget.h"
#include "TextInputWidget.h"

/// ������ ������ ������������ �� ����������. ��������� 
/// ��������� ������� SetContextMenuWidgetDropDownList
class ContextMenuWidget
{
private:
	/// ���������� ��� ���� � ������� ����������� �������� ������������ ����
	sf::RenderWindow* ContextMenuWidgetWindow;

	/// ����������-���������(DropDownListElement) ��� ������ � ���������� ������ DropDownList
	DropDownListElementWidget* ContextMenuWidgetDropDownListElement;

	/// ����������-���������(DropDownList) ��� ������ � ���������� ������ DropDownList
	DropDownListWidget* ContextMenuWidgetDropDownList;

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

	/// ����������-���������(Text)  ��� ����������� ������ �����������
	sf::Text* ContextMenuWidgetConfirmWidgetAcceptText;

	/// ����������-���������(Text)  ��� ����������� ������ ��������
	sf::Text* ContextMenuWidgetConfirmWidgetDeclineText;

	bool IsRendering = false;
	
	bool IsMouseOnShape = false;

	bool IsConfirmWidgetRendering = false;

	// ������������ ��� ���� ������
	enum Buttons
	{
		None,
		Add,
		Rename,
		Delete
	};
	// ������� ������
	Buttons CurrentButton = None;

public:
	/// ������ ������������ �� ����������
	ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow);
	
	void SetContextMenuWidgetDropDownList(DropDownListWidget* contextMenuWidgetDropDownList)
	{ ContextMenuWidgetDropDownList = contextMenuWidgetDropDownList; }

	void Tick();

	/// ���������� ����� 
	void InputHandler(sf::Event event);

	void OpenContextMenu(DropDownListElementWidget* contextMenuWidgetDropDownListElement);

	void CloseContextMenu();

	bool getIsMouseOnShape() { return IsMouseOnShape; }

	void OpenConfirmWidget();

	~ContextMenuWidget();
};

