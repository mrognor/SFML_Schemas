#pragma once

#include "SchemasClasses.h"
#include "DropDownListElementWidget.h"
#include "DragAndDropWidget.h"
#include "ContextMenuWidget.h"

class DropDownListWidget
{
private:
	/// Указатель на главное окно приложения 
	sf::RenderWindow* DropDownListWindow;

	/// Переменная для визуального ограничения длины кнопок
	sf::RectangleShape PaddingShape;

	/// Переменная для визуального изменения размера списка
	sf::RectangleShape HorizontalSliderShape;

	/// Переменная для движения списка по вертикали
	sf::RectangleShape VerticalSliderShape; 

	/// Указатель на текстуру для списка(DropDownList)
	sf::RenderTexture* DropDownListElementWidgetTexture;

	/// Указатель на спрайт для списка(DropDownList)
	sf::Sprite* DropDownListElementWidgetSprite;

	/// Вектор из всех элементов виджета(DropDownListElementWidget)
	std::vector<DropDownListElementWidget*> DropDownListElementsVector;

	/// Переменная для отслеживания объекта(DragAndDropWidget)
	DragAndDropWidget* DropDownListDragAndDropWidget;

	/// Переменная для отслеживания объекта(ContextMenuWidget)
	ContextMenuWidget* DropDownListContextMenuWidget;

	bool IsHorizontalMoving = false;

	bool IsVerticalMoving = false;

	float VerticalSliderClickPosition;

	/// Функция для записи движимых нод в файл. Алфавитный порядок соблюдается
	void WriteMovingNodesInAlphabeticOrder(std::vector<std::string> staticNodes, std::vector<std::string> movingNodes,
		DropDownListElementWidget* destinationElement);

public:
	///
	DropDownListWidget(sf::RenderWindow* mainWindow, DragAndDropWidget* dropDownListWindowDragAndDropWidget,
		ContextMenuWidget* dropDownListContextMenuWidget, int sizeX, int sizeY);

	/// Данная функция нужна для загрузки папок из файла
	void LoadElementsFromFile();

	/// Функция обработки ввода пользователя. Передает ивент всем элементам виджета(DropDownListElementWidget)
	void InputHandler(sf::Event event);

	/// 
	void Tick();
	
	/// Функция возвращает sprite списка
	sf::Sprite* GetSprite() { return DropDownListElementWidgetSprite; }

	/// Функция для открытия DropDownListElementWidget
	void OpenDropDownListElement(DropDownListElementWidget* elementToOpen);
	/// Функция для закрытия DropDownListElementWidget
	void CloseDropDownListElement(DropDownListElementWidget* elementToClose);
	
	/// Функция для нахождения индекса элементов(DropDownElement)
	/// Находит номер и устанавливает элементу нужное значение
	void FindAndSetDropDownListElementIndexes();

	/// Функция для перемещения DropDownListElement в иерархии
	void ReplaceDropDownListElement(DropDownListElementWidget* elementToMove, DropDownListElementWidget* destinationElement);

	/// Функция для добавления нового DropDownListElement
	void AddNewDropDownListElement(DropDownListElementWidget* parentElementToNewElement, std::string newname);

	/// Функция для переименования DropDownListElement
	void RenameDropDownListElement(DropDownListElementWidget* elementToRename, std::string newname);

	/// Функция для удаления DropDownListElement
	void DeleteDropDownListElement(DropDownListElementWidget* elementToDelete);

	~DropDownListWidget();
};

