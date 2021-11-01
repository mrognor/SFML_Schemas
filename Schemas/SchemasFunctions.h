#pragma once

#pragma once

#include <SFML/Graphics.hpp>
#include<string>
#include <vector>


/// Самописная шаблонная функция для проверки наличия элемента в std::vector.
/// Первый параметр - вектор. Второй параметр - значение
/// Для работы у типа данных должен быть определен оператор сравнения 
/// Возвращает true если есть такой объект и false если нет 
template <class T>
inline bool IsInVector(const std::vector<T>& vect, T val)
{
	for (int i = 0; i < vect.size(); i++)
	{
		if (*vect[i] == *val)
			return true;
	}
	return false;
}

/// Самописная функция для подсчета количества вхождений одного символа в строку
/// Первый параметр - строка. Второй параметр - строка, но она должна состоять из одного символа 
/// Возвращает количество вхождений, или -1 если в строке не было такого символа 
inline int CountInStr(std::string string, std::string val)
{
	int count = 0;
	for (int i = 0; i < string.size(); i++)
	{
		if (sf::String(string[i]) == sf::String(val))
			count++;
	}
	return count;
}

/// Самописная функция для превращения строки(исходная строка не меняется) в вектор строк
/// деление на элементы происходит с помощью строки делителя
/// Первый параметр - строка для деления. Второй параметр - строка делитель 
/// Возвращает вектор строк. Строка делитель не будет входить в строки 
inline std::vector<std::string> Split(std::string stringToSplit, std::string stringSplitter)
{
	std::vector<int> SplitterPositionVector;
	std::vector<std::string> FinalVector;

	for (int i = 0; i != stringToSplit.size(); i++)
	{
		if (sf::String(stringToSplit[i]) == sf::String(stringSplitter))
			SplitterPositionVector.push_back(i);
	}

	if (SplitterPositionVector.size() == 0)
	{
		FinalVector.push_back(stringToSplit);
		return FinalVector;
	}

	FinalVector.push_back(stringToSplit.substr(0, SplitterPositionVector[0]));

	for (int i = 0; i != SplitterPositionVector.size() - 1; i++)
	{
		FinalVector.push_back(stringToSplit.substr(SplitterPositionVector[i] + 1,
			SplitterPositionVector[i + 1] - SplitterPositionVector[i] - 1));
	}

	if (stringToSplit[stringToSplit.size() - 1] != *stringSplitter.c_str())
		FinalVector.push_back(stringToSplit.substr(SplitterPositionVector[SplitterPositionVector.size() - 1] + 1,
			stringToSplit.size() - SplitterPositionVector[SplitterPositionVector.size() - 1]));

	return FinalVector;
}

inline sf::Vector2f FindMouseCoords(sf::RenderWindow* windowToFindCursorPosition)
{
	return sf::Vector2f(windowToFindCursorPosition->mapPixelToCoords
		(sf::Vector2i
		(sf::Mouse::getPosition(*windowToFindCursorPosition).x,
			sf::Mouse::getPosition(*windowToFindCursorPosition).y)
		).x,
		windowToFindCursorPosition->mapPixelToCoords
		(sf::Vector2i
		(sf::Mouse::getPosition(*windowToFindCursorPosition).x,
			sf::Mouse::getPosition(*windowToFindCursorPosition).y)
		).y);
}

inline bool operator>(std::string stra, std::string strb)
{
	if (stra.size() >= strb.size())
	{
		for (int i = 0; i < strb.size(); i++)
		{
			if (tolower(stra[i]) > tolower(strb[i]))
				return true;
			if (tolower(stra[i]) < tolower(strb[i]))
				return false;
		}
		return true;
	}

	if (strb.size() > stra.size())
	{
		for (int i = 0; i < stra.size(); i++)
		{
			if (tolower(stra[i]) > tolower(strb[i]))
				return true;
			if (tolower(stra[i]) < tolower(strb[i]))
				return false;
		}
		return false;
	}
}

inline bool operator<(std::string stra, std::string strb)
{
	if (stra.size() > strb.size())
	{
		for (int i = 0; i < strb.size(); i++)
		{
			if (tolower(stra[i]) > tolower(strb[i]))
				return false;
			if (tolower(stra[i]) < tolower(strb[i]))
				return true;
		}
		return true;
	}

	if (strb.size() > stra.size())
	{
		for (int i = 0; i < stra.size(); i++)
		{
			if (tolower(stra[i]) > tolower(strb[i]))
				return false;
			if (tolower(stra[i]) < tolower(strb[i]))
				return true;
		}
		return true;
	}
}

inline std::ostream& operator<<(std::ostream& stream, sf::FloatRect rect)
{
	stream <<"Left coord: " << rect.left 
		<< " Width: " << rect.width
		<< " Top coord: " << rect.top 
		<< " Height: " << rect.height;
	return stream;
}


template <class T>
inline bool IsShapeInSpriteContain(const sf::Sprite& sprite, const T& objectInSprite, sf::Vector2f vectorToCheck)
{
	if (vectorToCheck.x > (sprite.getPosition().x + objectInSprite.getGlobalBounds().left) &&
		vectorToCheck.x < (sprite.getPosition().x + objectInSprite.getGlobalBounds().left + objectInSprite.getGlobalBounds().width) &&
		vectorToCheck.y >(sprite.getPosition().y + objectInSprite.getGlobalBounds().top) &&
		vectorToCheck.y < (sprite.getPosition().y + objectInSprite.getGlobalBounds().top + objectInSprite.getGlobalBounds().height)
		)
		return true;
	else return false;
}
/// Данная функция нужна для поиска индекса символа в тексте, соответствующей данной позиции курсора
/// Первый параметр должен показывать позцию курсора относительно начала текста
inline int FindTextIndexToPosition(float localMousePositionX, sf::Text textToFind, sf::Font font)
{
	/// Текст для определения места нажития мышки и установки туда курсора
	sf::Text TextInputWidgetClickText;
	TextInputWidgetClickText.setFont(font);

	if (localMousePositionX <= 0)
	{
		return 0;
	}

	for (int i = 0; i <= textToFind.getString().getSize(); i++)
	{
		// Определение дистанции до левого символа
		float LeftDistance = localMousePositionX - (TextInputWidgetClickText.getGlobalBounds().left + TextInputWidgetClickText.getGlobalBounds().width);

		TextInputWidgetClickText.setString(TextInputWidgetClickText.getString() + textToFind.getString()[i]);

		// Определение дистанции до правого символа
		float RightDistance = localMousePositionX - (TextInputWidgetClickText.getGlobalBounds().left + TextInputWidgetClickText.getGlobalBounds().width);

		// Если левый символ левее, а правый правее, то мы дошли до нужной позиции
		if (LeftDistance >= 0 && RightDistance < 0)
		{
			if (abs(RightDistance) >= abs(LeftDistance))
				return i;
			else
				return i + 1;
		}
	}
	return textToFind.getString().getSize();
}
