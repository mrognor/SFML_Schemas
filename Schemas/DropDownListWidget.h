#pragma once

#include "SchemasClasses.h"
#include "DropDownListElementWidget.h"
#include "DragAndDropWidget.h"
#include "ContextMenuWidget.h"

class DropDownListWidget
{
private:
	/// ��������� �� ������� ���� ���������� 
	sf::RenderWindow* DropDownListElementWindow;

	/// RectangleShape. �������������, �������� ������� ����� ������� ������
	sf::RectangleShape WidgetBody;

	/// ������ �� ���� ��������� �������(DropDownListElementWidget)
	std::vector<DropDownListElementWidget*> DropDownListElementsVector;

	/// ���������� ��� ������������ �������(DragAndDropWidget)
	DragAndDropWidget* DropDownListDragAndDropWidget;

	/// ���������� ��� ������������ �������(ContextMenuWidget)
	ContextMenuWidget* DropDownListContextMenuWidget;

public:
	///
	DropDownListWidget(sf::RenderWindow* mainWindow, DragAndDropWidget* dropDownListWindowDragAndDropWidget,
		ContextMenuWidget* dropDownListContextMenuWidget, int sizeX, int sizeY);

	/// ������ ������� ����� ��� �������� ����� �� �����
	void LoadElementsFromFile();

	/// ������� ��������� ����� ������������. �������� ����� ���� ��������� �������(DropDownListElementWidget)
	void InputHandler(sf::Event event);

	/// 
	void Tick();

	/// ������� ��� �������� DropDownListElementWidget
	void OpenDropDownListElement(DropDownListElementWidget* elementToOpen);
	/// ������� ��� �������� DropDownListElementWidget
	void CloseDropDownListElement(DropDownListElementWidget* elementToClose);
	
	/// ������� ��� ���������� ������� ���������(DropDownElement)
	/// ������� ����� � ������������� �������� ������ ��������
	void FindAndSetDropDownListElementIndexes();

	void ReplaceDropDownListElement(DropDownListElementWidget* elementToMove, DropDownListElementWidget* destinationElement);

	void RenameDropDownListElement(DropDownListElementWidget* elementToRename, std::string newname);

	~DropDownListWidget();
};

