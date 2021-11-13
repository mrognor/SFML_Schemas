#pragma once

#include "SchemasClasses.h"
#include "MovingPoleNodeWidget.h"
#include "DropDownListWidget.h"
#include "MovingPoleNodeWidget.h"
#include "DragAndDropWidget.h"
#include "MovingPoleConnectionWidget.h"

class MovingPoleWidget
{
private:
	/// Окно поля
	sf::RenderWindow* MovingPoleWidgetWindow;

	/// Указатель на DropDown список
	DropDownListWidget* MovingPoleDropDownListWidget;

	/// Указатель на драг и дроп виджет
	DragAndDropWidget* MovingPoleDragAndDropWidget;

	/// Вектор нод поля
	std::vector<MovingPoleNodeWidget*> MovingPoleNodeVector;

	/// Вектор соединений поля
	std::vector<MovingPoleConnectionWidget*> MovingPoleConnectionVector;

	/// Переменная для последних координат мыши
	sf::Vector2f LastMouseCoords;

	/// Текстура для отрисовки всех элементов поля
	sf::RenderTexture* MovingPoleWidgetTexture;

	/// Спрайт для отрисовки всеъ элементов поля
	sf::Sprite* MovingPoleWidgetSprite;

	/// Переменная для фиксации начала перетаскивания
	bool IsDragStarted = false;

	MovingPoleConnectionWidget* CurrentConnectionWidget = nullptr;

public:
	MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow, DropDownListWidget* movingPoleDropDownListWidget, DragAndDropWidget* movingPoleDragAndDropWidget);

	void Tick();

	void InputHandler(sf::Event event);

	/// Функция для создания объекта соединения нод на поле
	void CreateConnection(OutputNode* outputNode);

	void DeleteConnection(MovingPoleConnectionWidget* widgetToRemove);

	/// Функция возвращает текущий объект соединения 
	MovingPoleConnectionWidget* getCurrentConnectionWidget() { return CurrentConnectionWidget; }

	/// Функция сбрасывает текущий объект соединения. Должна ввызываться в случае удачного соединения
	void ResetCurrentConnectionWidget() { CurrentConnectionWidget = nullptr; }

	sf::RenderTexture* GetMovingPoleWidgetTexture() { return MovingPoleWidgetTexture; }

	sf::Sprite* GetMovingPoleWidgetSprite() { return MovingPoleWidgetSprite; }

	~MovingPoleWidget();
};

