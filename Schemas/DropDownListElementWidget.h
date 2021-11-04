#pragma once

#include "SchemasClasses.h"
#include "DropDownListWidget.h"
#include "DragAndDropWidget.h"
#include "ContextMenuWidget.h"

/// Класс для элемента DropDownListWidget 
class DropDownListElementWidget
{
private:
	/// Указатель на родительский виджет(DropDownListWidget)
	DropDownListWidget* DropDownListParent;

	/// Переменная для отслеживания объекта(DragAndDropWidget)
	DragAndDropWidget* DropDownListElementDragAndDropWidget;

	/// Указатель на окно приложения в котором находится виджет(DropDownListWidget)
	sf::RenderWindow* DropDownListWindow;

	/// Указатель на текстуру для списка(DropDownList)
	sf::RenderTexture* DropDownListElementWidgetDropDownListWidgetTexture;

	/// Переменная для отслеживания объекта(ContextMenuWidget)
	ContextMenuWidget* DropDownListElementContextMenuWidget;

	/// Указатель на RectangleShape, являющийся главным прямоугольником виджета(DropDownListElementWidget)
	sf::RectangleShape* MainDropDownListElementShape;

	/// Указатель на CircleShape, являющийся графическим представление состояния 
	// открытости папки
	sf::CircleShape* DropDownListElementOpenClosedConditionTriangle;

	/// Шрифт 
	sf::Font font;

	/// Указатель на Text, являющийся главным текстом виджета(DropDownListElementWidget)
	sf::Text* MainDropDownListElementText;

	/// Полный путь данного элемента(DropDownListElementWidget)
	std::string FullPath;

	/// Полное имя данного элемента(DropDownListElementWidget)
	std::string Name;

	/// Переменная для отслеживания мыши. True - если мышь на MainDropDownListElementShape, false в противном случае
	bool IsMouseOnShape;

	/// Позиция данного элемента в списке(DropDownListWidget). Множитель y координаты для данного виджета 
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
	/// из DropDownListWidget.
	DropDownListElementWidget(DropDownListWidget* dropDownListParent, sf::RenderWindow* window, 
		sf::RenderTexture* dropDownListElementWidgetDropDownListWidgetTexture, DragAndDropWidget * dropDownListElementDragAndDropWidget,
 ContextMenuWidget* dropDownListElementContextMenu,
		std::string name, std::string path, int numberInDropDownList);

	/// Сеттер для полного пути 
	void setFullPath(std::string path) { FullPath = path; }
	/// Геттер для полного пути 
	std::string getFullPath() { return FullPath; }

	/// Сеттер для имени
	void setName(std::string name) { Name = name; }
	/// Геттер для имени
	std::string getName() { return Name; }

	/// Устанавливает позицию данного объекта в списке DropDownListWidget
	void setNumberInDropDownList(int numberInList) { NumberInDropDownList = numberInList; }
	/// Получает позицию данного объекта в списке DropDownListWidget
	int getNumberInDropDownList() { return NumberInDropDownList; }

	/// Сеттер для переменной для отрисовки объекта(DropDownListElementWidget)
	void setIsRendering(bool f);
	/// Геттер для переменной для отрисовки объекта(DropDownListElementWidget)
	bool getIsRendering() { return IsRendering; }

	/// Сеттер для переменной для закрытия папки 
	void setIsDropDownListElementOpen(bool f);
	// Геттер для переменной для закрытия папки
	bool getIsDropDownListElementOpen() { return IsDropDownListElementOpen; }

	/// Данная функция перемещает тело виджета(DropDownListElementWidget) и текст в нужную позицию
	/// Для определения позиция есть переменная NumberInDropDownList
	/// Эта переменная устанавливается из DropDownListWidget.
	void UpdateDropDownListElementPosition();

	/// Функция, работающая каждый такт 
	void Tick();

	/// Обработчик ввода 
	void InputHandler(sf::Event event);

	/// Оператор сравнения
	bool operator== (const DropDownListElementWidget& Obj);
	/// Оператор сравнения 
	bool operator!= (const DropDownListElementWidget& Obj);
	/// Дуструктор. Освобождает память из по MainDropDownListElementShape и MainDropDownListElementText
	~DropDownListElementWidget();
};