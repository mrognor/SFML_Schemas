#pragma once

#include "SchemasClasses.h"
#include "DropDownList.h"

/// Класс для элемента DropDownList 
class DropDownListElement
{
private:
	/// Указатель на родительский виджет(DropDownList)
	DropDownList* DropDownListParent;

	/// Указатель на окно приложения в котором находится виджет(DropDownList)
	sf::RenderWindow* Window;

	/// Указатель на RectangleShape, являющийся главным прямоугольником виджета(DropDownListElement)
	sf::RectangleShape* MainDropDownListElementShape;

	/// Указатель на Text, являющийся главным текстом виджета(DropDownListElement)
	sf::Text* MainDropDownListElementText;
	 
	/// Шрифт 
	sf::Font font;

	/// Полный путь данного элемента(DropDownListElement)
	std::string FullPath;

	/// Полное имя данного элемента(DropDownListElement)
	std::string Name;

	/// Переменная для отслеживания мыши. True - если мышь на MainDropDownListElementShape, false в противном случае
	bool IsMouseOnShape;

	/// Позиция данного элемента в списке(DropDownList). Множитель y координаты для данного виджета 
	int NumberInDropDownList;

public:
	/// Создает объект RectangleShape для тела данного виджета. Вызывает функцию SetDropDownListElementPosition.
	/// SetDropDownListElementPosition перемещает тело виджета и текст в правильную позицию. Позиция устанавливается 
	/// из DropDownList.
	DropDownListElement(DropDownList* dropDownListParent, sf::RenderWindow* window, std::string name, std::string path, int numberInDropDownList);

	/// Сеттер для полного пути 
	void setFullPath(std::string path) { FullPath = path; }
	/// Геттер для полного пути 
	std::string getFullPath() { return FullPath; }

	/// Сеттер для имени
	void setName(std::string name) { Name = name; }
	// Геттер для имени
	std::string getName() { return Name; }

	/// Данная функция перемещает тело виджета(DropDownListElement) и текст в нужную позицию
	/// Для определения позиция есть переменная NumberInDropDownList
	/// Эта переменная устанавливается из DropDownList.
	void SetDropDownListElementPosition();

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