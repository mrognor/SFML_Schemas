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

	/// Переменная-указатель(RectangleShape) для отображения кнопки для добавления нод
	sf::RectangleShape* ContextMenuWidgetAddButton;

	/// Переменная-указатель(Text) для отображения кнопки для добавления нод
	sf::Text* ContextMenuWidgetAddButtonText;

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

	TextInputWidget* ContextMenuWidgetRenameButtonTextInputWidget;

	/// Переменная-указатель(RectangleShape) для отображения кнопки "да" при вызове меню подтверждения
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetAcceptShape;

	/// Переменная-указатель(RectangleShape) для отображения кнопки "нет" при вызове меню подтверждения
	sf::RectangleShape* ContextMenuWidgetConfirmWidgetDeclineShape;

	/// Переменная-указатель(Text)  для отображения кнопки подтвердить
	sf::Text* ContextMenuWidgetConfirmWidgetAcceptText;

	/// Переменная-указатель(Text)  для отображения кнопки отменить
	sf::Text* ContextMenuWidgetConfirmWidgetDeclineText;

	bool IsRendering = false;
	
	bool IsMouseOnShape = false;

	bool IsConfirmWidgetRendering = false;

	// Перечисление для типа кнопки
	enum Buttons
	{
		None,
		Add,
		Rename,
		Delete
	};
	// Текущая кнопка
	Buttons CurrentButton = None;

public:
	/// Одного конструктора не достаточно
	ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow);
	
	void SetContextMenuWidgetDropDownList(DropDownListWidget* contextMenuWidgetDropDownList)
	{ ContextMenuWidgetDropDownList = contextMenuWidgetDropDownList; }

	void Tick();

	/// Обработчик ввода 
	void InputHandler(sf::Event event);

	void OpenContextMenu(DropDownListElementWidget* contextMenuWidgetDropDownListElement);

	void CloseContextMenu();

	bool getIsMouseOnShape() { return IsMouseOnShape; }

	void OpenConfirmWidget();

	~ContextMenuWidget();
};

