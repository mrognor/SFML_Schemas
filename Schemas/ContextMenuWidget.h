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

	/// ����������-���������(RectangleShape) ��� ����������� ������ ��� ���������� ����������� ��������
	sf::RectangleShape* ContextMenuWidgetAddLogicalElementButton;

	/// ����������-���������(Text) ��� ����������� ������ ��� ���������� ����������� ��������
	sf::Text* ContextMenuWidgetAddLogicalElementButtonText;

	/// ����������-���������(RectangleShape) ��� ����������� ������ ��� �������� ���
	sf::RectangleShape* ContextMenuWidgetAddFolderButton;

	/// ����������-���������(Text)  ��� ����������� ������ ��� �������� ���
	sf::Text* ContextMenuWidgetAddFolderButtonText;

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

	/// ����������-��������� ��� ����������� ������ ���������� �����
	TextInputWidget* ContextMenuWidgetConfirmMenuWidgetTextInputWidget;

	/// ����������-���������(RectangleShape) ��� ����������� ������ "��" ��� ������ ���� �������������
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetAcceptShape;

	/// ����������-���������(RectangleShape) ��� ����������� ������ "���" ��� ������ ���� �������������
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetDeclineShape;

	/// ����������-���������(Text)  ��� ����������� ������ �����������
	sf::Text* ContextMenuWidgetConfirmWidgetAcceptText;

	/// ����������-���������(Text)  ��� ����������� ������ ��������
	sf::Text* ContextMenuWidgetConfirmWidgetDeclineText;

	/// ����������, ���������� �� ��������� ������������ ����
	bool IsRendering = false;
	
	/// ���������� ��� ������������ ����, ��� ����� ��������� �� ����������� ����
	bool IsMouseOnShape = false;

	/// ���������, ���������� �� ��������� ���� �������������
	bool IsConfirmWidgetRendering = false;

	/// ���������� ��� ������������ ���� �������� ������ � �������� ������� ����
	bool IsMenuCreatedToFolder = true;

	// ������������ ��� ���� ������
	enum Buttons
	{
		None,
		AddLogicalElement,
		AddFolder,
		Rename,
		Delete
	};
	// ������� ������
	Buttons CurrentButton = None;

public:
	/// ������ ������������ �� ����������
	ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow);

	/// ������ ������� ����� ��� ������ ������ 
	/// ��� ������������� ������ ���� ��� ����� ������
	void SetContextMenuWidgetDropDownList(DropDownListWidget* contextMenuWidgetDropDownList)
	{ ContextMenuWidgetDropDownList = contextMenuWidgetDropDownList; }

	void Tick();

	/// ���������� ����� 
	void InputHandler(sf::Event event);

	/// ������� ��� �������� ������������ ����
	void OpenContextMenu(DropDownListElementWidget* contextMenuWidgetDropDownListElement);

	/// ������� ��� �������� ������������ ����
	void CloseContextMenu();

	/// ������ ��� ���������� 
	bool getIsMouseOnShape() { return IsMouseOnShape; }

	/// ������� ��� �������� ���� ������������� 
	void OpenConfirmWidget();

	~ContextMenuWidget();
};

