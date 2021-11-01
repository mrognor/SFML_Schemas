#include "TextInputWidget.h"

TextInputWidget::TextInputWidget(sf::RenderWindow* textInputWidgetWindow) : TextInputWidgetWindow(textInputWidgetWindow)
{
	TextInputWidgetMainShape.setSize(sf::Vector2f(200, 40));

	TextInputWidgetCursorShape.setSize(sf::Vector2f(3, 25));
	TextInputWidgetCursorShape.setFillColor(sf::Color::Green);

	font.loadFromFile("Font.ttf");

	TextInputWidgetMainText.setFont(font);
	TextInputWidgetMainText.setFillColor(sf::Color::Magenta);

	TextInputWidgetHintText.setFont(font);
	TextInputWidgetHintText.setFillColor(sf::Color::Black);

	TextInputWidgetCursorText.setFont(font);

	TextInputWidgetSliderShape.setSize(sf::Vector2f(200, 10));
	TextInputWidgetSliderShape.setPosition(sf::Vector2f(0, 35));
	TextInputWidgetSliderShape.setFillColor(sf::Color::Green);

	TextInputWidgetHighlightShape.setFillColor(sf::Color::Blue);

	// Create texture to text input pole
	TextInputWidgetTexture.create(200, 40);
	TextInputWidgetTexture.draw(TextInputWidgetMainShape);
	// Update texture
	TextInputWidgetTexture.display();

	TextInputWidgetSprite.setTexture(TextInputWidgetTexture.getTexture());
	TextInputWidgetSprite.setPosition(500, 300);
}

void TextInputWidget::Tick()
{
	TextInputWidgetWindow->draw(TextInputWidgetSprite);
}

void TextInputWidget::InputHandler(sf::Event event)
{
	/// Определяем координаты курсора 
	sf::Vector2f MouseCoords = FindMouseCoords(TextInputWidgetWindow);

	/// Переменная для движения текста в случае движения курсора
	bool IsCursorMoved = false;

	// Включение ввода текста
	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
		TextInputWidgetSprite.getGlobalBounds().contains(MouseCoords))
	{
		if (IsShapeInSpriteContain(TextInputWidgetSprite, TextInputWidgetSliderShape, MouseCoords) == false)
		{
			CursorPosition = FindTextIndexToPosition(MouseCoords.x - TextInputWidgetSprite.getPosition().x - TextInputWidgetMainText.getPosition().x, TextInputWidgetMainText, font);
			HighliteStartPosition = CursorPosition;
		}
		IsTextInputStarted = true;
	}


	// Отключение ввода текста
	if ((event.type == event.MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Left
		|| event.mouseButton.button == sf::Mouse::Right)) &&
		TextInputWidgetSprite.getGlobalBounds().contains(MouseCoords) == false)
	{
		IsTextInputStarted = false;
	}

	// Включение движения слайдера
	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
		IsShapeInSpriteContain(TextInputWidgetSprite, TextInputWidgetSliderShape, MouseCoords))
	{
		IsSliderDragStarted = true;
		CursorClickPosition = MouseCoords.x - (TextInputWidgetSprite.getPosition().x + TextInputWidgetSliderShape.getGlobalBounds().left);
	}

	// Выключение движения слайдера
	if (event.type == event.MouseButtonReleased)
		IsSliderDragStarted = false;

	if (event.type == event.MouseButtonPressed && IsSliderDragStarted == false)
	{
		TextInputWidgetHighlightShape.setSize(sf::Vector2f(0, 30));
	}


	// Левая стрелка
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
	{
		IsCursorMoved = true;
		if (IsTextInputStarted)
		{
			if (CursorPosition > 0)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					CursorPosition--;
					if (CursorPosition != HighliteStartPosition)
					{
						/// Текст для определения места нажития мышки и установки туда курсора
						sf::Text TextInputWidgetHighliteStartText(
							TextInputWidgetMainText.getString().substring(0, HighliteStartPosition), font);

						sf::Text TextInputWidgetCursorText(
							TextInputWidgetMainText.getString().substring(0, CursorPosition), font);

						TextInputWidgetHighlightShape.setPosition(sf::Vector2f(
							TextInputWidgetHighliteStartText.getGlobalBounds().width + TextInputWidgetMainText.getPosition().x, 5));
						TextInputWidgetHighlightShape.setSize(sf::Vector2f(
							TextInputWidgetCursorText.getGlobalBounds().width
							- TextInputWidgetHighliteStartText.getGlobalBounds().width, 30));
					}
					else TextInputWidgetHighlightShape.setSize(sf::Vector2f(0, 30));
				}
				else
				{
					CursorPosition--;
					HighliteStartPosition = CursorPosition;
				}
			}
		}
	}
	// Правая стрелка
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
	{
		IsCursorMoved = true;
		if (IsTextInputStarted)
		{
			if (CursorPosition < TextInputWidgetMainText.getString().getSize())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					CursorPosition++;
					if (CursorPosition != HighliteStartPosition)
					{
						/// Текст для определения места нажития мышки и установки туда курсора
						sf::Text TextInputWidgetHighliteStartText(
							TextInputWidgetMainText.getString().substring(0, HighliteStartPosition), font);

						sf::Text TextInputWidgetCursorText(
							TextInputWidgetMainText.getString().substring(0, CursorPosition), font);

						TextInputWidgetHighlightShape.setPosition(sf::Vector2f(
							TextInputWidgetHighliteStartText.getGlobalBounds().width + TextInputWidgetMainText.getPosition().x, 5));
						TextInputWidgetHighlightShape.setSize(sf::Vector2f(
							TextInputWidgetCursorText.getGlobalBounds().width
							- TextInputWidgetHighliteStartText.getGlobalBounds().width, 30));
					}
					else TextInputWidgetHighlightShape.setSize(sf::Vector2f(0, 30));
				}
				else
				{
					CursorPosition++;
					HighliteStartPosition = CursorPosition;
				}
			}
		}
	}

	// Проверка ввода текста
	if (IsTextInputStarted && event.type == sf::Event::TextEntered && event.text.unicode < 128)
	{
		std::cout << "Char:" << char(event.text.unicode) << " Code:" << event.text.unicode << std::endl;
		IsCursorMoved = true;
		TextInputWidgetHighlightShape.setSize(sf::Vector2f(0, 30));
		switch (event.text.unicode)
		{
			// Кнопка удаления
		case 8:
			if (TextInputWidgetMainText.getString().getSize() != 0 && CursorPosition > 0 && CursorPosition == HighliteStartPosition)
			{
				TextInputWidgetMainText.setString(TextInputWidgetMainText.getString().substring(0, CursorPosition - 1) + TextInputWidgetMainText.getString().substring(CursorPosition));
				CursorPosition--;
				HighliteStartPosition = CursorPosition;
				if (TextInputWidgetCursorShape.getGlobalBounds().left < TextInputWidgetMainShape.getGlobalBounds().left &&
					TextInputWidgetCursorShape.getGlobalBounds().left > TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)
				{
					sf::Text deletionText(TextInputWidgetMainText.getString()[CursorPosition], font);
					TextInputWidgetMainText.move(sf::Vector2f(deletionText.getGlobalBounds().left + deletionText.getGlobalBounds().width, 0));
					TextInputWidgetCursorText.move(sf::Vector2f(deletionText.getGlobalBounds().left + deletionText.getGlobalBounds().width, 0));
					TextInputWidgetHighlightShape.move(sf::Vector2f(deletionText.getGlobalBounds().left + deletionText.getGlobalBounds().width, 0));
				}

				if (TextInputWidgetCursorShape.getGlobalBounds().left >= TextInputWidgetMainShape.getGlobalBounds().left &&
					TextInputWidgetCursorShape.getGlobalBounds().left <= TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)
				{
					TextInputWidgetMainText.setPosition(sf::Vector2f(0, 0));
					TextInputWidgetCursorText.setPosition(sf::Vector2f(0, 0));
					TextInputWidgetHighlightShape.setPosition(sf::Vector2f(0, 0));
				}
			}
			if (CursorPosition != HighliteStartPosition && CursorPosition <= TextInputWidgetMainText.getString().getSize()
				&& HighliteStartPosition <= TextInputWidgetMainText.getString().getSize())
			{
				if (CursorPosition > HighliteStartPosition)
				{
					if (TextInputWidgetCursorShape.getGlobalBounds().left < TextInputWidgetMainShape.getGlobalBounds().left &&
						TextInputWidgetCursorShape.getGlobalBounds().left > TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)
					{
						std::cout << std::string(TextInputWidgetMainText.getString()) << std::endl;
						std::cout << "CursorPosition: " << CursorPosition << " HighliteStartPosition: " << HighliteStartPosition << " Len: " << CursorPosition - HighliteStartPosition
							<< " Str: " << std::string(TextInputWidgetMainText.getString().substring(HighliteStartPosition, CursorPosition - HighliteStartPosition)) << std::endl;

						sf::Text deletionText(TextInputWidgetMainText.getString().substring(HighliteStartPosition, CursorPosition - HighliteStartPosition), font);
						TextInputWidgetMainText.move(sf::Vector2f(deletionText.getGlobalBounds().left + deletionText.getGlobalBounds().width, 0));
						TextInputWidgetCursorText.move(sf::Vector2f(deletionText.getGlobalBounds().left + deletionText.getGlobalBounds().width, 0));
						TextInputWidgetHighlightShape.move(sf::Vector2f(deletionText.getGlobalBounds().left + deletionText.getGlobalBounds().width, 0));
					}

					TextInputWidgetMainText.setString(TextInputWidgetMainText.getString().substring(0, HighliteStartPosition) + TextInputWidgetMainText.getString().substring(CursorPosition));

					CursorPosition = HighliteStartPosition;
				}
				else
				{
					if (TextInputWidgetCursorShape.getGlobalBounds().left < TextInputWidgetMainShape.getGlobalBounds().left &&
						TextInputWidgetCursorShape.getGlobalBounds().left > TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)
					{
						sf::Text deletionText(TextInputWidgetMainText.getString().substring(CursorPosition, HighliteStartPosition - CursorPosition), font);
						TextInputWidgetMainText.move(sf::Vector2f(deletionText.getGlobalBounds().width, 0));
						TextInputWidgetCursorText.move(sf::Vector2f(deletionText.getGlobalBounds().width, 0));
						TextInputWidgetHighlightShape.move(sf::Vector2f(deletionText.getGlobalBounds().width, 0));
					}
					TextInputWidgetMainText.setString(TextInputWidgetMainText.getString().substring(0, CursorPosition) + TextInputWidgetMainText.getString().substring(HighliteStartPosition));
				}

				HighliteStartPosition = CursorPosition;

				if (TextInputWidgetCursorShape.getGlobalBounds().left >= TextInputWidgetMainShape.getGlobalBounds().left &&
					TextInputWidgetCursorShape.getGlobalBounds().left <= TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)
				{
					TextInputWidgetMainText.setPosition(sf::Vector2f(0, 0));
					TextInputWidgetCursorText.setPosition(sf::Vector2f(0, 0));
					TextInputWidgetHighlightShape.setPosition(sf::Vector2f(0, 0));
				}
			}
			break;

		default:
			TextInputWidgetMainText.setString(TextInputWidgetMainText.getString().substring(0, CursorPosition) + sf::String(event.text.unicode)
				+ TextInputWidgetMainText.getString().substring(CursorPosition));
			CursorPosition++;
			HighliteStartPosition = CursorPosition;
		}
	}

	// Клавиша delete
	if (IsTextInputStarted && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete)
	{
		if (TextInputWidgetMainText.getString().getSize() != 0 && CursorPosition < TextInputWidgetMainText.getString().getSize())
			TextInputWidgetMainText.setString(TextInputWidgetMainText.getString().substring(0, CursorPosition) + TextInputWidgetMainText.getString().substring(CursorPosition + 1));
	}

	// Подготовка текстуры и отрисовка всего статичного
	TextInputWidgetTexture.clear();
	TextInputWidgetTexture.draw(TextInputWidgetMainShape);

	// Отрисовка выделителя текста
	if (IsTextInputStarted && event.type == event.MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		IsSliderDragStarted == false)
	{
		CursorPosition = FindTextIndexToPosition(MouseCoords.x - TextInputWidgetSprite.getPosition().x - TextInputWidgetMainText.getPosition().x, TextInputWidgetMainText, font);
		if (CursorPosition != HighliteStartPosition)
		{
			/// Текст для определения места нажития мышки и установки туда курсора
			sf::Text TextInputWidgetHighliteStartText(
				TextInputWidgetMainText.getString().substring(0, HighliteStartPosition), font);

			sf::Text TextInputWidgetCursorText(
				TextInputWidgetMainText.getString().substring(0, CursorPosition), font);

			TextInputWidgetHighlightShape.setPosition(sf::Vector2f(
				TextInputWidgetHighliteStartText.getGlobalBounds().width + TextInputWidgetMainText.getPosition().x, 5));
			TextInputWidgetHighlightShape.setSize(sf::Vector2f(
				TextInputWidgetCursorText.getGlobalBounds().width
				- TextInputWidgetHighliteStartText.getGlobalBounds().width, 30));
		}
		else TextInputWidgetHighlightShape.setSize(sf::Vector2f(0, 30));
	}

	TextInputWidgetTexture.draw(TextInputWidgetHighlightShape);
	TextInputWidgetTexture.draw(TextInputWidgetMainText);

	if (TextInputWidgetMainText.getString().getSize() == 0)
	{
		TextInputWidgetTexture.draw(TextInputWidgetHintText);
	}

	// Отриcовка курсора
	if (IsTextInputStarted)
	{
		TextInputWidgetCursorText.setString((TextInputWidgetMainText.getString().substring(0, CursorPosition)));
		TextInputWidgetCursorShape.setPosition(sf::Vector2f(TextInputWidgetCursorText.getGlobalBounds().left + TextInputWidgetCursorText.getGlobalBounds().width, 10));
		TextInputWidgetTexture.draw(TextInputWidgetCursorShape);
	}

	// Логика слайдера
	if (TextInputWidgetMainText.getGlobalBounds().width > TextInputWidgetMainShape.getGlobalBounds().width)
	{
		TextInputWidgetSliderShape.setScale(sf::Vector2f(TextInputWidgetMainShape.getGlobalBounds().width / TextInputWidgetMainText.getGlobalBounds().width, 1));

		if (IsSliderDragStarted)
		{
			TextInputWidgetSliderShape.setPosition(sf::Vector2f(MouseCoords.x - TextInputWidgetSprite.getPosition().x - CursorClickPosition, 35));

			// Граничные позиции слайдера
			if (TextInputWidgetSliderShape.getGlobalBounds().left < TextInputWidgetMainShape.getGlobalBounds().left)
				TextInputWidgetSliderShape.setPosition(sf::Vector2f(TextInputWidgetMainShape.getGlobalBounds().left, 35));

			if (TextInputWidgetSliderShape.getGlobalBounds().left + TextInputWidgetSliderShape.getGlobalBounds().width > TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)
				TextInputWidgetSliderShape.setPosition(sf::Vector2f(TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width - TextInputWidgetSliderShape.getGlobalBounds().width, 35));


			TextInputWidgetMainText.setPosition(sf::Vector2f(-1 * TextInputWidgetSliderShape.getGlobalBounds().left * TextInputWidgetMainShape.getGlobalBounds().width / TextInputWidgetSliderShape.getGlobalBounds().width, 0));
			TextInputWidgetCursorText.setPosition(sf::Vector2f(-1 * TextInputWidgetSliderShape.getGlobalBounds().left * TextInputWidgetMainShape.getGlobalBounds().width / TextInputWidgetSliderShape.getGlobalBounds().width, 0));

			/// Текст для определения места нажития мышки и установки туда курсора
			sf::Text TextInputWidgetHighliteStartText(
				TextInputWidgetMainText.getString().substring(0, HighliteStartPosition), font);

			TextInputWidgetHighlightShape.setPosition(sf::Vector2f(
				TextInputWidgetHighliteStartText.getGlobalBounds().width + TextInputWidgetMainText.getPosition().x, 5));
		}
		// Отрисовка слайдера на текстуре
		TextInputWidgetTexture.draw(TextInputWidgetSliderShape);
	}

	if (IsCursorMoved)
	{
		// Сдвиг текста если курсор правее правого края поля
		if (TextInputWidgetCursorShape.getGlobalBounds().left > TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)
		{
			TextInputWidgetMainText.move(sf::Vector2f(-1 * (TextInputWidgetCursorShape.getGlobalBounds().left - (TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)), 0));
			TextInputWidgetCursorText.move(sf::Vector2f(-1 * (TextInputWidgetCursorShape.getGlobalBounds().left - (TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)), 0));
			TextInputWidgetHighlightShape.move(sf::Vector2f(-1 * (TextInputWidgetCursorShape.getGlobalBounds().left - (TextInputWidgetMainShape.getGlobalBounds().left + TextInputWidgetMainShape.getGlobalBounds().width)), 0));
		}

		// Сдвиг текста если курсор левее левого края поля
		if (TextInputWidgetCursorShape.getGlobalBounds().left < TextInputWidgetMainShape.getGlobalBounds().left)
		{
			TextInputWidgetMainText.move(sf::Vector2f(TextInputWidgetMainShape.getGlobalBounds().left - TextInputWidgetCursorShape.getGlobalBounds().left, 0));
			TextInputWidgetCursorText.move(sf::Vector2f(TextInputWidgetMainShape.getGlobalBounds().left - TextInputWidgetCursorShape.getGlobalBounds().left, 0));
			TextInputWidgetHighlightShape.move(sf::Vector2f(TextInputWidgetMainShape.getGlobalBounds().left - TextInputWidgetCursorShape.getGlobalBounds().left, 0));
		}

		TextInputWidgetSliderShape.setPosition(sf::Vector2f(
			-1 * TextInputWidgetMainText.getGlobalBounds().left /
			(TextInputWidgetMainShape.getGlobalBounds().width / TextInputWidgetSliderShape.getGlobalBounds().width), 35));
	}
	TextInputWidgetTexture.display();
}

void TextInputWidget::SetPosition(sf::Vector2f Vec)
{
	TextInputWidgetSprite.setPosition(Vec);
}

sf::String TextInputWidget::GetString()
{
	return TextInputWidgetMainText.getString();
}

void TextInputWidget::SetHintString(sf::String hintString)
{
	TextInputWidgetHintText.setString(hintString);
}

TextInputWidget::~TextInputWidget()
{
}