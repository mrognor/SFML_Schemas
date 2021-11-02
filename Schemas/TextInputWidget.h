#pragma once

#include "SchemasClasses.h"

class TextInputWidget
{
private:
	/// Указатель на окно в котором находится наш виджет
	sf::RenderWindow* TextInputWidgetWindow;

	/// Текстура нашего виджета. 
	/// Текстура требуется для сокрытия текста за пределами поля ввода
	sf::RenderTexture TextInputWidgetTexture;

	/// Тело поля ввода 
	sf::RectangleShape TextInputWidgetMainShape;

	// Фигура для правого отступа поля ввода
	sf::RectangleShape TextInputWidgetRightPaddingShape;

	/// Тело курсора 
	sf::RectangleShape TextInputWidgetCursorShape;

	/// Шрифт
	sf::Font font;

	/// Основной текст поля ввода 
	sf::Text TextInputWidgetMainText;

	/// Дополнительный текст поля ввода.
	/// Не отрисовывается на экране, служит для нахождения
	/// позиции куросра в пикселях. Содержит часть основного текста
	/// Позиция в исходном тексте определяется переменной CursorPosition
	sf::Text TextInputWidgetCursorText;

	/// Текст подсказки в поле ввода 
	sf::Text TextInputWidgetHintText;

	/// Тело слайдера
	sf::RectangleShape TextInputWidgetSliderShape;

	/// Тело шейпа подсветки
	sf::RectangleShape TextInputWidgetHighlightShape;

	/// Спрайт для нашей текстуры. Размер как у текстуры
	sf::Sprite TextInputWidgetSprite;

	/// Переменная для обозначения начала ввода текста 
	bool IsTextInputStarted = false;

	/// Позиция курсора внутри текста
	int CursorPosition = 0;

	/// Позиция начала фигуры подсветки
	int HighliteStartPosition = 0;

	/// Переменная для обозначения начала перетаскивания слайдера
	bool IsSliderDragStarted = false;

	/// Позиция нажатия на курсор
	float CursorClickPosition;

public:
	TextInputWidget(sf::RenderWindow* textInputWidgetWindow);

	void Tick();

	void InputHandler(sf::Event event);

	void SetPosition(sf::Vector2f Vec);

	void SetString(sf::String newstring);

	void SetHintString(sf::String hintString);

	sf::String GetString();

	~TextInputWidget();
};


