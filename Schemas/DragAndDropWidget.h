#pragma once

#include "SchemasClasses.h"
#include "DropDownListElement.h"

class DragAndDropWidget
{
private:
	/// Переменная для окна в котором выполняется операция DragAndDrop
	sf::RenderWindow* DragAndDropWidgetWindow;

	/// Переменная-указатель(RectangleShape) для отображения объекта при перетаскивании папок
	sf::RectangleShape* DragAndDropWidgetShape;

	/// Шрифт 
	sf::Font font;

	/// Переменная-указатель(Text) для отображения объекта при перетаскивании папок
	sf::Text* DragAndDropWidgetText;

	/// Координаты начала перетаскивания 
	sf::Vector2f DragStartCoords;

	/// Логическая переменная для определения состояния объекта(DropDownListElement).
	/// Переменная показывает идет ли операция перетаскивания 
	bool IsDragAndDropInProcess = false;

	
	/// Переменная для отслеживания объекта(DropDownListElement)
	/// Указывает на объект для которого в данный момент выполняется операция DragAndDrop
	DropDownListElement* CurrentDropDownListElement;

	
public:
	DragAndDropWidget(sf::RenderWindow* dragAndDropWidgetWindow);

	void Tick();

	// Обработчик ввода 
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

