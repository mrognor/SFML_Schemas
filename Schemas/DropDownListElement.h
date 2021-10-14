#pragma once

#include "SchemasClasses.h"
#include "DropDownList.h"
#include "DragAndDropWidget.h"

/// Класс для элемента DropDownList 
class DropDownListElement
{
private:
	/// Указатель на родительский виджет(DropDownList)
	DropDownList* DropDownListParent;

	/// Переменная для отслеживания объекта(DragAndDropWidget)
	DragAndDropWidget* DropDownListElementWindowDragAndDropWidget;

	/// Указатель на окно приложения в котором находится виджет(DropDownList)
	sf::RenderWindow* ListElementWindow;

	/// Указатель на RectangleShape, являющийся главным прямоугольником виджета(DropDownListElement)
	sf::RectangleShape* MainDropDownListElementShape;

	/// Шрифт 
	sf::Font font;

	/// Указатель на Text, являющийся главным текстом виджета(DropDownListElement)
	sf::Text* MainDropDownListElementText;

	/// Полный путь данного элемента(DropDownListElement)
	std::string FullPath;

	/// Полное имя данного элемента(DropDownListElement)
	std::string Name;

	/// Переменная для отслеживания мыши. True - если мышь на MainDropDownListElementShape, false в противном случае
	bool IsMouseOnShape;

	/// Позиция данного элемента в списке(DropDownList). Множитель y координаты для данного виджета 
	int NumberInDropDownList;
	
	/// Данная переменная служит для определения состояния папки.
	/// False - данный объект не должен отрисовываться на окне 
	/// True - данный объект не должен отрисовываться на окне
	bool IsRendering = true;

	/// Данная переменная служит для определения состояния папки. 
	/// False - все дети не должны отрисовываться(IsRendering = false)
	/// True - все дети должны отрисовываться(IsRendering = true)
	bool IsDropDownListElementOpen = true;

public:
	/// Создает объект RectangleShape для тела данного виджета. Вызывает функцию UpdateDropDownListElementPosition.
	/// UpdateDropDownListElementPosition перемещает тело виджета и текст в правильную позицию. Позиция устанавливается 
	/// из DropDownList.
	DropDownListElement(DropDownList* dropDownListParent, sf::RenderWindow* window, DragAndDropWidget* dropDownListElementWindowDragAndDropWidget,
		std::string name, std::string path, int numberInDropDownList);

	/// Сеттер для полного пути 
	void setFullPath(std::string path) { FullPath = path; }
	/// Геттер для полного пути 
	std::string getFullPath() { return FullPath; }

	/// Сеттер для имени
	void setName(std::string name) { Name = name; }
	// Геттер для имени
	std::string getName() { return Name; }

	/// Устанавливает позицию данного объекта в списке DropDownList
	void setNumberInDropDownList(int numberInList) { NumberInDropDownList = numberInList; }
	/// Получает позицию данного объекта в списке DropDownList
	int getNumberInDropDownList() { return NumberInDropDownList; }

	/// Сеттер для переменной для отрисовки объекта(DropDownListElement)
	void setIsRendering(bool f) { IsRendering = f; }
	// Геттер для переменной для отрисовки объекта(DropDownListElement)
	bool getIsRendering() { return IsRendering; }

	/// Сеттер для переменной для закрытия папки 
	void setIsDropDownListElementOpen(bool f) { IsDropDownListElementOpen = f; }
	// Геттер для переменной для закрытия папки
	bool getIsDropDownListElementOpen() { return IsDropDownListElementOpen; }

	/// Данная функция перемещает тело виджета(DropDownListElement) и текст в нужную позицию
	/// Для определения позиция есть переменная NumberInDropDownList
	/// Эта переменная устанавливается из DropDownList.
	void UpdateDropDownListElementPosition();

	/// Функция, работающая каждый такт 
	void Tick();

	// Обработчик ввода 
	void InputHandler(sf::Event event);

	/// Оператор сравнения
	bool operator== (const DropDownListElement& Obj);
	/// Оператор сравнения 
	bool operator!= (const DropDownListElement& Obj);
	/// Дуструктор. Освобождает память из по MainDropDownListElementShape и MainDropDownListElementText
	~DropDownListElement();
};