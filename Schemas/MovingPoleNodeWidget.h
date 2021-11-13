#pragma once

#include "SchemasClasses.h"
#include "MovingPoleWidget.h"

inline bool InterpretLine(std::string Line)
{
	while (Line.size() != 1)
	{
		if (Line.find("not(0)") != -1)
			Line.replace(Line.find("not(0)"), 6, "1");
		if (Line.find("not(1)") != -1)
			Line.replace(Line.find("not(1)"), 6, "0");

		if (Line.find("and(0,0)") != -1)
			Line.replace(Line.find("and(0,0)"), 8, "0");
		if (Line.find("and(0,1)") != -1)
			Line.replace(Line.find("and(0,1)"), 8, "0");
		if (Line.find("and(1,0)") != -1)
			Line.replace(Line.find("and(1,0)"), 8, "0");
		if (Line.find("and(1,1)") != -1)
			Line.replace(Line.find("and(1,1)"), 8, "1");

		if (Line.find("or(0,0)") != -1)
			Line.replace(Line.find("or(0,0)"), 7, "0");
		if (Line.find("or(0,1)") != -1)
			Line.replace(Line.find("or(0,1)"), 7, "1");
		if (Line.find("or(1,0)") != -1)
			Line.replace(Line.find("or(1,0)"), 7, "1");
		if (Line.find("or(1,1)") != -1)
			Line.replace(Line.find("or(1,1)"), 7, "1");
	}

	if (Line == "1")
		return true;
	if (Line == "0")
		return false;
}

inline std::string SwapLetter(std::string str, std::map<std::string, InputNode> inputNodesMap)
{
	for (auto it = inputNodesMap.begin(); it != inputNodesMap.end(); it++)
	{
		while (str.find("(" + it->first + ")") != -1)
			str.replace(str.find(it->first), it->first.size(), std::to_string(int(it->second.Value)));

		while (str.find("(" + it->first + ",") != -1)
			str.replace(str.find(it->first), it->first.size(), std::to_string(int(it->second.Value)));

		while (str.find("," + it->first + ")") != -1)
			str.replace(str.find(it->first), it->first.size(), std::to_string(int(it->second.Value)));
	}
	return str;
}

/// Для отрисовки класса нужно использовать метод Draw
class MovingPoleNodeWidget
{
private:
	sf::RenderWindow* MovingPoleNodeWidgetWindow;
	MovingPoleWidget* ParentMovingPoleWidget;

	sf::Text MovingPoleNodeWidgetText;
	sf::Font font;

	std::string NodeName;
	std::string InputLine;
	std::string OutputLine;
	/// Ограничение на входы и выходы!!! Они могут быть только односимвольными
	std::string FormulaLine;

	std::map<std::string, InputNode> InputNodesMap;
	std::map<std::string, OutputNode> OutputNodesMap;

	sf::RectangleShape MovingPoleNodeWidgetBody;
	std::vector<sf::CircleShape*> InputShapes;
	std::vector<sf::CircleShape*> OutputShapes;

	float ButtonShift = 45;

	float ButtonRadius = 20;

	float BodyWidth = 200;

	/// Функция для обновления логических выходов
	void UpdateLogicalOutputs();

public:
	MovingPoleNodeWidget(sf::RenderWindow* window, MovingPoleWidget* movingPoleWidget, std::string nodeName, float posX = 0, float posY = 0);

	void InputHandler(sf::Event event);

	void Move(sf::Vector2f vec);
	
	/// Данный метод отрисовывает элемент на текстуре
	void DrawElementToTexture();

	/// Функция для создания графической интерпретации данной ноды
	void CreateGraphicalRepresentationOfElement();

	~MovingPoleNodeWidget();
};

