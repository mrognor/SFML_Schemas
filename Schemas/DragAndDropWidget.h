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

	
public:
	DragAndDropWidget(sf::RenderWindow* dragAndDropWidgetWindow);

	void Tick();

	// ���������� ����� 
	void InputHandler(sf::Event event);

	void StartDragAndDropOperation(DropDownListElement* currentDropDownListElement, sf::Vector2f dragStartCoords);
	
	bool getIsDragAndDropInProcess() { return IsDragAndDropInProcess; }

	~DragAndDropWidget(); 
	/*
	void setCurrentDropDownListElement(DropDownListElement* currentDropDownListElement) 
	{ CurrentDropDownListElement = currentDropDownListElement; }

	void setIsDragListElementInProcess(bool f) { IsDragNDropInProcess = f; }

	bool getIsDragListElementInProcess() { return IsDragNDropInProcess; }

	void setDragStartListElementCoords(sf::Vector2f coords) { DragStartCoords = coords; }
	*/
};

