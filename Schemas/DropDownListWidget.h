#pragma once

#include "SchemasClasses.h"
#include "DropDownListElementWidget.h"
#include "DragAndDropWidget.h"

class DropDownListWidget
{
private:
	/// ��������� �� ������� ���� ���������� 
	sf::RenderWindow* ListElementWindow;

	/// RectangleShape. �������������, �������� ������� ����� ������� ������
	sf::RectangleShape WidgetBody;

	/// ������ �� ���� ��������� �������(DropDownListElementWidget)
	std::vector<DropDownListElementWidget*> DropDownListElementsVector;

	/// ���������� ��� ������������ �������(DragAndDropWidget)
	DragAndDropWidget* DropDownListWindowDragAndDropWidget;

public:
	///
	DropDownListWidget(sf::RenderWindow* mainWindow, DragAndDropWidget* dropDownListWindowDragAndDropWidget,
		int sizeX, int sizeY);

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

	~DropDownListWidget();
};

