#pragma once

#include "SchemasClasses.h"
#include "DropDownListElement.h"
#include "DragAndDropWidget.h"

class DropDownList
{
private:
	/// ��������� �� ������� ���� ���������� 
	sf::RenderWindow* ListElementWindow;

	/// RectangleShape. �������������, �������� ������� ����� ������� ������
	sf::RectangleShape WidgetBody;

	/// ������ �� ���� ��������� �������(DropDownListElement)
	std::vector<DropDownListElement*> DropDownListElementsVector;

	/// ���������� ��� ������������ �������(DragAndDropWidget)
	DragAndDropWidget* DropDownListWindowDragAndDropWidget;

public:
	///
	DropDownList(sf::RenderWindow* mainWindow, DragAndDropWidget* dropDownListWindowDragAndDropWidget,
		int sizeX, int sizeY);

	/// ������ ������� ����� ��� �������� ����� �� �����
	void LoadElementsFromFile();

	/// ������� ��������� ����� ������������. �������� ����� ���� ��������� �������(DropDownListElement)
	void InputHandler(sf::Event event);

	/// 
	void Tick();

	/// ������� ��� �������� DropDownListElement
	void OpenDropDownListElement(DropDownListElement* elementToOpen);
	/// ������� ��� �������� DropDownListElement
	void CloseDropDownListElement(DropDownListElement* elementToClose);
	
	/// ������� ��� ���������� ������� ���������(DropDownElement)
	/// ������� ����� � ������������� �������� ������ ��������
	void FindAndSetDropDownListElementIndexes();

	void ReplaceDropDownListElement(DropDownListElement* elementToMove, DropDownListElement* destinationElement);

	~DropDownList();
};

