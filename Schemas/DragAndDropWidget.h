#pragma once

#include "SchemasClasses.h"
#include "DropDownListElement.h"

class DragAndDropWidget
{
private:
	/// ���������� ��� ���� � ������� ����������� �������� DragAndDrop
	sf::RenderWindow* DragAndDropWidgetWindow;

	/// ����������-���������(RectangleShape) ��� ����������� ������� ��� �������������� �����
	sf::RectangleShape* DragAndDropWidgetShape;

	/// ����� 
	sf::Font font;

	/// ����������-���������(Text) ��� ����������� ������� ��� �������������� �����
	sf::Text* DragAndDropWidgetText;

	/// ���������� ������ �������������� 
	sf::Vector2f DragStartCoords;

	/// ���������� ���������� ��� ����������� ��������� �������(DropDownListElement).
	/// ���������� ���������� ���� �� �������� �������������� 
	bool IsDragAndDropInProcess = false;

	
	/// ���������� ��� ������������ �������(DropDownListElement)
	/// ��������� �� ������ ��� �������� � ������ ������ ����������� �������� DragAndDrop
	DropDownListElement* CurrentDropDownListElement;

	/// ���������� ��� ������������ �������(DropDownList)
	/// ��������� �� ������ ������� �������� ������� ������� ���� � ������ ������ �������
	DropDownList* WindowDropDownList;

public:
	/// ������ ������ ������������ �� ���������� ��� ������ ���������. ��������� ������������
	/// setWindowDropDownList ��� ���������� ������ ���������
	DragAndDropWidget(sf::RenderWindow* dragAndDropWidgetWindow);

	void Tick();

	/// ���������� ����� 
	void InputHandler(sf::Event event);

	/// ������� ��� ��������� WindowDropDownList
	void setWindowDropDownList(DropDownList* windowDropDownList) { WindowDropDownList = windowDropDownList; }

	/// ������� ��� ������ DragAndDrop ��������. ��������� DropDownListElement ��� �������� ���������� ��������
	void StartDragAndDropOperation(DropDownListElement* currentDropDownListElement);
	
	/// ������� ��� ��������� ��������� ��������������
	bool getIsDragAndDropInProcess() { return IsDragAndDropInProcess; }

	/// ������� ��� ��������� ��������� ������ ��������������
	sf::Vector2f getDragStartCoords() { return DragStartCoords; }

	/// ������� ��� �������� DropDownListElement ��� �������� ����������� �������� �������������� 
	DropDownListElement* getCurrentDropDownListElement() { return CurrentDropDownListElement;}

	~DragAndDropWidget(); 
};

