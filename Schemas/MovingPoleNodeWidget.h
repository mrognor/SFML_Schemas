#pragma once

#include "SchemasClasses.h"

struct InputNode
{
	sf::CircleShape* Circle;
	bool Value;
};
struct OutputNode
{
	sf::CircleShape* Circle;
	std::string Formula;
};

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

/// ��� ��������� ������ ����� ������������ ����� Draw
class MovingPoleNodeWidget
{
private:
	sf::RenderWindow* MovingPoleNodeWidgetWindow;
	sf::RenderTexture* MovingPoleNodeWidgetTexture;
	sf::Sprite* MovingPoleNodeWidgetSprite;


	sf::Text MovingPoleNodeWidgetText;
	sf::Font font;

	std::string NodeName = "";
	std::string InputLine = "A/B/C";
	std::string OutputLine = "A/B/C/D";
	/// ����������� �� ����� � ������!!! ��� ����� ���� ������ ���������������
	std::string FormulaLine = "A:or(A,B)/B:and(A,B)/C:or(and(A,not(B)),and(not(A),B))/D:not(C)";

	std::map<std::string, InputNode> InputNodesMap;
	std::map<std::string, OutputNode> OutputNodesMap;

	sf::RectangleShape MovingPoleNodeWidgetBody;
	std::vector<sf::CircleShape*> InputShapes;
	std::vector<sf::CircleShape*> OutputShapes;

	float ButtonShift = 45;

	float ButtonRadius = 20;

	float BodyWidth = 200;

	/// ������� ��� ���������� ���������� �������
	void UpdateLogicalOutputs();

public:
	MovingPoleNodeWidget(sf::RenderWindow* window, sf::Sprite* movingPoleNodeWidgetSprite, 
		sf::RenderTexture* movingPoleNodeWidgetTexture, float posX = 0, float posY = 0);

	void InputHandler(sf::Event event);

	void Move(sf::Vector2f vec);
	
	/// ������ ����� ������������ ������� �� ��������
	void DrawElementToTexture();

	/// ������� ��� �������� ����������� ������������� ������ ����
	void CreateGraphicalRepresentationOfElement();

	~MovingPoleNodeWidget();
};

