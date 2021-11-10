#pragma once

#include "SchemasClasses.h"
#include "MovingPoleNodeWidget.h"
#include "DropDownListWidget.h"
#include "MovingPoleNodeWidget.h"
#include "DragAndDropWidget.h"

class MovingPoleWidget
{
private:
	/// Окно поля
	sf::RenderWindow* MovingPoleWidgetWindow;

	/// Указатель на DropDown список
	DropDownListWidget* MovingPoleDropDownListWidget;

	DragAndDropWidget* MovingPoleDragAndDropWidget;

	std::vector<MovingPoleNodeWidget*> MovingPoleNodeVector;

	/// Переменная для последних координат мыши
	sf::Vector2f LastMouseCoords;

	/// Текстура для отрисовки всех элементов поля
	sf::RenderTexture* MovingPoleWidgetTexture;

	/// Спрайт для отрисовки всеъ элементов поля
	sf::Sprite* MovingPoleWidgetSprite;

	/// Переменная для фиксации начала перетаскивания
	bool IsDragStarted = false;

public:
	MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow, DropDownListWidget* movingPoleDropDownListWidget, DragAndDropWidget* movingPoleDragAndDropWidget);

	void Tick();

	void InputHandler(sf::Event event);

	sf::RenderTexture* GetMovingPoleWidgetTexture() { return MovingPoleWidgetTexture; }

	sf::Sprite* GetMovingPoleWidgetSprite() { return MovingPoleWidgetSprite; }

	~MovingPoleWidget();
};

