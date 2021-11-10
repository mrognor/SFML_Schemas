#include "MovingPoleNodeWidget.h"


MovingPoleNodeWidget::MovingPoleNodeWidget(sf::RenderWindow* window, sf::Sprite* movingPoleNodeWidgetSprite,
	sf::RenderTexture* movingPoleNodeWidgetTexture, float posX, float posY) :
	MovingPoleNodeWidgetWindow(window), MovingPoleNodeWidgetSprite(movingPoleNodeWidgetSprite),
	MovingPoleNodeWidgetTexture(movingPoleNodeWidgetTexture)
{
	MovingPoleNodeWidgetBody.setPosition({ posX, posY });
	MovingPoleNodeWidgetBody.setFillColor(sf::Color::White);

	CreateGraphicalRepresentationOfElement();

	UpdateLogicalOutputs();
}


void MovingPoleNodeWidget::DrawElementToTexture()
{
	MovingPoleNodeWidgetTexture->draw(MovingPoleNodeWidgetBody);
	//MovingPoleNodeWidgetTexture->draw(MovingPoleNodeWidgetText);

	for (sf::CircleShape* circle : InputShapes)
	{
		MovingPoleNodeWidgetTexture->draw(*circle);
	}

	for (sf::CircleShape* circle : OutputShapes)
	{
		MovingPoleNodeWidgetTexture->draw(*circle);
	}
}

void MovingPoleNodeWidget::InputHandler(sf::Event event)
{
	sf::Vector2f MouseCoords = FindMouseCoords(MovingPoleNodeWidgetTexture, MovingPoleNodeWidgetWindow);

	if (event.type == event.MouseButtonPressed)
	{
		for (auto it = InputNodesMap.begin(); it != InputNodesMap.end(); it++)
		{
			if (IsShapeInSpriteContain(*MovingPoleNodeWidgetSprite, *it->second.Circle, MouseCoords))
			{
				if (it->second.Value == 0)
				{
					it->second.Circle->setFillColor(sf::Color::Blue);
					it->second.Value = 1;
					UpdateLogicalOutputs();
				}
				else
				{
					it->second.Circle->setFillColor(sf::Color::Magenta);
					it->second.Value = 0;
					UpdateLogicalOutputs();
				}
			}
		}
	}
}

void MovingPoleNodeWidget::Move(sf::Vector2f vec)
{
	MovingPoleNodeWidgetBody.move(vec);

	for (sf::CircleShape* circle : InputShapes)
	{
		circle->move(vec);
	}

	for (sf::CircleShape* circle : OutputShapes)
	{
		circle->move(vec);
	}
}

void MovingPoleNodeWidget::CreateGraphicalRepresentationOfElement()
{
	InputShapes.clear();
	OutputShapes.clear();
	
	float posX = MovingPoleNodeWidgetBody.getPosition().x;
	float posY = MovingPoleNodeWidgetBody.getPosition().y;

	std::vector<std::string> InputNames = Split(InputLine, "/");
	std::vector<std::string> OutputNames = Split(OutputLine, "/");
	std::vector<std::string> FormulaNames = Split(FormulaLine, "/");
	
	for (int i = 0; i < InputNames.size(); i++)
	{
		sf::CircleShape* circle = new sf::CircleShape(ButtonRadius);
		circle->setOrigin(ButtonRadius, ButtonRadius);
		circle->setFillColor(sf::Color::Magenta);
		circle->setPosition(posX + ButtonRadius, posY + ButtonRadius + i * ButtonShift);

		InputShapes.push_back(circle);

		InputNode A;
		A.Circle = circle;
		A.Value = false;
		InputNodesMap[InputNames[i]] = A;
	}

	for (int i = 0; i < OutputNames.size(); i++)
	{
		sf::CircleShape* circle = new sf::CircleShape(ButtonRadius);
		circle->setOrigin(ButtonRadius, ButtonRadius);
		circle->setFillColor(sf::Color::Magenta);
		circle->setPosition(posX + BodyWidth - ButtonRadius, posY + ButtonRadius + i * ButtonShift);

		OutputShapes.push_back(circle);

		OutputNode A;
		A.Circle = circle;

		for (int j = 0; j < FormulaNames.size(); j++)
		{
			if (FormulaNames[j].find(OutputNames[i]) == 0)
				A.Formula = FormulaNames[j].substr(FormulaNames[j].find(":") + 1);
		}
		OutputNodesMap[OutputNames[i]] = A;
	}

	if (InputNames.size() > OutputNames.size())
		MovingPoleNodeWidgetBody.setSize({ BodyWidth, float((InputNames.size() - 1) * ButtonShift + 2 * ButtonRadius) });
	else
		MovingPoleNodeWidgetBody.setSize({ BodyWidth, float((OutputNames.size() - 1) * ButtonShift + 2 * ButtonRadius) });

	UpdateLogicalOutputs();
}

void MovingPoleNodeWidget::UpdateLogicalOutputs()
{
	for (auto it = OutputNodesMap.begin(); it != OutputNodesMap.end(); it++)
	{
		std::string newstr = SwapLetter(it->second.Formula, InputNodesMap);
		if (InterpretLine(newstr))
			it->second.Circle->setFillColor(sf::Color::Blue);
		else it->second.Circle->setFillColor(sf::Color::Magenta);
	}
}

MovingPoleNodeWidget::~MovingPoleNodeWidget()
{
	for (sf::CircleShape* circle : InputShapes)
	{
		delete circle;
	}

	for (sf::CircleShape* circle : OutputShapes)
	{
		delete circle;
	}
}
