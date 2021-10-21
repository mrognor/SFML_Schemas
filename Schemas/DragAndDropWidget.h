#pragma once

#include "SchemasClasses.h"
#include "DropDownListElementWidget.h"

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

	/// Логическая переменная для определения состояния объекта(DropDownListElementWidget).
	/// Переменная показывает идет ли операция перетаскивания 
	bool IsDragAndDropInProcess = false;

	
	/// Переменная для отслеживания объекта(DropDownListElementWidget)
	/// Указывает на объект для которого в данный момент выполняется операция DragAndDrop
	DropDownListElementWidget* CurrentDropDownListElement;

	/// Переменная для отслеживания объекта(DropDownListWidget)
	/// Указывает на объект который является списком данного окна в данный момент времени
	DropDownListWidget* WindowDropDownList;

public:
	/// Одного только конструктора не достаточно для работы программы. Требуется использовать
	/// setWindowDropDownList для корректной работы программы
	DragAndDropWidget(sf::RenderWindow* dragAndDropWidgetWindow);

	void Tick();

	/// Обработчик ввода 
	void InputHandler(sf::Event event);

	/// Функция для установки WindowDropDownList
	void setWindowDropDownList(DropDownListWidget* windowDropDownList) { WindowDropDownList = windowDropDownList; }

	/// Функция для старта DragAndDrop операции. Принимает DropDownListElementWidget для которого происходит операция
	void StartDragAndDropOperation(DropDownListElementWidget* currentDropDownListElement);
	
	/// Функция для получения состояния перетаскивания
	bool getIsDragAndDropInProcess() { return IsDragAndDropInProcess; }

	/// Функция для получения координат начала перетаскивания
	sf::Vector2f getDragStartCoords() { return DragStartCoords; }

	/// Функция для возврата DropDownListElementWidget для которого выполняется операция перетаскивания 
	DropDownListElementWidget* getCurrentDropDownListElement() { return CurrentDropDownListElement;}

	~DragAndDropWidget(); 
};

