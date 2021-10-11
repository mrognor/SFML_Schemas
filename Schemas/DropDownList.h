#pragma once

#include "SchemasClasses.h"
#include "DropDownListElement.h"

class DropDownList
{
private:
	/// Указатель на главное окно приложения 
	sf::RenderWindow* Window;

	/// RectangleShape. Прямоугольник, служащий главным телом виджета списка
	sf::RectangleShape WidgetBody;

	/// Вектор из всех элементов виджета(DropDownListElement)
	std::vector<DropDownListElement*> DropDownListElementsVector;

public:
	///
	DropDownList(sf::RenderWindow* mainWindow, int sizeX, int sizeY);

	/// Функция обработки ввода пользователя. Передает ивент всем элементам виджета(DropDownListElement)
	void InputHandler(sf::Event event);

	/// 
	void Tick();

	/// Функция для открытия DropDownListElement
	void OpenDropDownListElement(DropDownListElement* elementToOpen);
	/// Функция для закрытия DropDownListElement
	void CloseDropDownListElement(DropDownListElement* elementToClose);
	
	/// Функция для нахождения индекса элементов(DropDownElement)
	/// Находит номер и устанавливает элементу нужное значение
	void FindAndSetDropDownListElementIndexes();

	~DropDownList();
};

