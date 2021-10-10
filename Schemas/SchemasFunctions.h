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

	FinalVector.push_back(stringToSplit.substr(SplitterPositionVector[SplitterPositionVector.size() - 1] + 1,
		stringToSplit.size() - SplitterPositionVector[SplitterPositionVector.size() - 1]));

	return FinalVector;
}