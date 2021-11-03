#pragma once

#include "SchemasClasses.h"
#include "DropDownListElementWidget.h"
#include "DragAndDropWidget.h"
#include "ContextMenuWidget.h"

class DropDownListWidget
{
private:
	/// Указатель на главное окно приложения 
	sf::RenderWindow* DropDownListElementWindow;

	/// RectangleShape. Прямоугольник, служащий главным телом виджета списка
	sf::RectangleShape WidgetBody;

	/// Вектор из всех элементов виджета(DropDownListElementWidget)
	std::vector<DropDownListElementWidget*> DropDownListElementsVector;

	/// Переменная для отслеживания объекта(DragAndDropWidget)
	DragAndDropWidget* DropDownListDragAndDropWidget;

	/// Переменная для отслеживания объекта(ContextMenuWidget)
	ContextMenuWidget* DropDownListContextMenuWidget;

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

