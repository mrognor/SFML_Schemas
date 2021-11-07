#pragma once

#include "SchemasClasses.h"
#include "MovingPoleNodeWidget.h"
#include "DropDownListWidget.h"

class MovingPoleWidget
{
private:
	/// Окно поля
	sf::RenderWindow* MovingPoleWidgetWindow;

	DropDownListWidget* MovingPoleDropDownListWidget;

	sf::RectangleShape ShapeToTest;
	
	/// Переменная для последних координат мыши
	sf::Vector2f LastMouseCoords;

	/// Текстура для отрисовки всех элементов поля
	sf::RenderTexture* MovingPoleWidgetTexture;

	/// Спрайт для отрисовки всеъ элементов поля
	sf::Sprite* MovingPoleWidgetSprite;

	/// Переменная для фиксации начала перетаскивания
	bool IsDragStarted = false;

public:
	MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow, DropDownListWidget* movingPoleDropDownListWidget);

	void Tick();

	void InputHandler(sf::Event event);

	~MovingPoleWidget();
};

