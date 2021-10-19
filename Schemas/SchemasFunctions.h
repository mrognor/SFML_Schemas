#pragma once

#pragma once

#include <SFML/Graphics.hpp>
#include<string>
#include <vector>


/// ���������� ��������� ������� ��� �������� ������� �������� � std::vector.
/// ������ �������� - ������. ������ �������� - ��������
/// ��� ������ � ���� ������ ������ ���� ��������� �������� ��������� 
/// ���������� true ���� ���� ����� ������ � false ���� ��� 
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

/// ���������� ������� ��� �������� ���������� ��������� ������ ������� � ������
/// ������ �������� - ������. ������ �������� - ������, �� ��� ������ �������� �� ������ ������� 
/// ���������� ���������� ���������, ��� -1 ���� � ������ �� ���� ������ ������� 
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

/// ���������� ������� ��� ����������� ������(�������� ������ �� ��������) � ������ �����
/// ������� �� �������� ���������� � ������� ������ ��������
/// ������ �������� - ������ ��� �������. ������ �������� - ������ �������� 
/// ���������� ������ �����. ������ �������� �� ����� ������� � ������ 
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
			if (tolower(stra[0]) > tolower(strb[0]))
				return true;
			if (tolower(stra[0]) < tolower(strb[0]))
				return false;
		}
		return true;
	}

	if (strb.size() > stra.size())
	{
		for (int i = 0; i < stra.size(); i++)
		{
			if (tolower(stra[0]) > tolower(strb[0]))
				return true;
			if (tolower(stra[0]) < tolower(strb[0]))
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
			if (tolower(stra[0]) > tolower(strb[0]))
				return false;
			if (tolower(stra[0]) < tolower(strb[0]))
				return true;
		}
		return true;
	}

	if (strb.size() > stra.size())
	{
		for (int i = 0; i < stra.size(); i++)
		{
			if (tolower(stra[0]) > tolower(strb[0]))
				return false;
			if (tolower(stra[0]) < tolower(strb[0]))
				return true;
		}
		return true;
	}
}
