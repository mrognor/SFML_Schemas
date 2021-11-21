#pragma once

#include "SchemasClasses.h"
#include "DropDownListWidget.h"
#include "DropDownListElementWidget.h"
#include "TextInputWidget.h"

/// Одного только конструктора не достаточно. Требуется 
/// выполнить функцию SetContextMenuWidgetDropDownList
class ContextMenuWidget
{
private:
	/// Переменная для окна в котором выполняется операции контекстного меню
	sf::RenderWindow* ContextMenuWidgetWindow;

	/// Переменная-указатель(DropDownListElement) для работы с элементами списка DropDownList
	DropDownListElementWidget* ContextMenuWidgetDropDownListElement;

	/// Переменная-указатель(DropDownList) для работы с элементами списка DropDownList
	DropDownListWidget* ContextMenuWidgetDropDownList;

	/// Переменная-указатель(RectangleShape) для отображения объекта при вызове контекстного меню
	sf::RectangleShape* ContextMenuWidgetShape;

	/// Переменная-указатель(RectangleShape) для отображения кнопки для добавления логического элемента
	sf::RectangleShape* ContextMenuWidgetAddLogicalElementButton;

	/// Переменная-указатель(Text) для отображения кнопки для добавления логического элемента
	sf::Text* ContextMenuWidgetAddLogicalElementButtonText;

	/// Переменная-указатель(RectangleShape) для отображения кнопки для удаления нод
	sf::RectangleShape* ContextMenuWidgetAddFolderButton;

	/// Переменная-указатель(Text)  для отображения кнопки для удаления нод
	sf::Text* ContextMenuWidgetAddFolderButtonText;

	/// Переменная-указатель(RectangleShape) для отображения кнопки для переименования нод
	sf::RectangleShape* ContextMenuWidgetRenameButton;

	/// Переменная-указатель(Text) для отображения кнопки для переименования нод
	sf::Text* ContextMenuWidgetRenameButtonText;

	/// Переменная-указатель(RectangleShape) для отображения кнопки для удаления нод
	sf::RectangleShape* ContextMenuWidgetDeleteButton;

	/// Переменная-указатель(Text)  для отображения кнопки для удаления нод
	sf::Text* ContextMenuWidgetDeleteButtonText;

	/// Шрифт 
	sf::Font font;

	/// Переменная-указатель(RectangleShape) отображения объекта при вызове меню подтверждения 
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetShape;

	/// Переменная-указатель для самописного класса текстового ввода
	TextInputWidget* ContextMenuWidgetConfirmMenuWidgetTextInputWidget;

	/// Переменная-указатель(RectangleShape) для отображения кнопки "да" при вызове меню подтверждения
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetAcceptShape;

	/// Переменная-указатель(RectangleShape) для отображения кнопки "нет" при вызове меню подтверждения
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetDeclineShape;

	/// Переменная-указатель(Text)  для отображения кнопки подтвердить
	sf::Text* ContextMenuWidgetConfirmWidgetAcceptText;

	/// Переменная-указатель(Text)  для отображения кнопки отменить
	sf::Text* ContextMenuWidgetConfirmWidgetDeclineText;

	/// Переменная, отвечающая за рендеринг контекстного меню
	bool IsRendering = false;
	
	/// Переменная для отслеживания того, что мышка находится на контекстном меню
	bool IsMouseOnShape = false;

	/// Перемення, отвечающая за рендеринг меню подтверждения
	bool IsConfirmWidgetRendering = false;

	/// Переменная для отслеживания типа элемента списка к которому открыто меню
	bool IsMenuCreatedToFolder = true;

	// Перечисление для типа кнопки
	enum Buttons
	{
		None,
		AddLogicalElement,
		AddFolder,
		Rename,
		Delete
	};
	// Текущая кнопка
	Buttons CurrentButton = None;

public:
	/// Одного конструктора не достаточно
	ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow);

	/// Данная функция нужна для работы класса 
	/// Она устанавливает объект меню для этого класса
	void SetContextMenuWidgetDropDownList(DropDownListWidget* contextMenuWidgetDropDownList)
	{ ContextMenuWidgetDropDownList = contextMenuWidgetDropDownList; }

	void Tick();

	/// Обработчик ввода 
	void InputHandler(sf::Event event);

	/// Функция для открытия контекстного меню
	void OpenContextMenu(DropDownListElementWidget* contextMenuWidgetDropDownListElement);

	/// Функция для закрытия контекстного меню
	void CloseContextMenu();

	/// Геттер для переменной 
	bool getIsMouseOnShape() { return IsMouseOnShape; }

	/// Функция для открытия меню подтверждения 
	void OpenConfirmWidget();

	~ContextMenuWidget();
};

