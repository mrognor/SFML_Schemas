#include "MovingPoleNodeWidget.h"


MovingPoleNodeWidget::MovingPoleNodeWidget(sf::RenderWindow* window, MovingPoleWidget* movingPoleWidget, std::string nodeName, float posX, float posY) :
	MovingPoleNodeWidgetWindow(window), ParentMovingPoleWidget(movingPoleWidget), NodeName(nodeName)
{
	MovingPoleNodeWidgetBody.setPosition({ posX, posY });
	MovingPoleNodeWidgetBody.setFillColor(sf::Color::White);

	std::ifstream NodeTXT;
	NodeTXT.open(NodeName + ".txt");

	std::string Line;

	if (NodeTXT.is_open())
	{
		getline(NodeTXT, Line);
		InputLine = Split(Line, " ")[1];

		getline(NodeTXT, Line);
		OutputLine = Split(Line, " ")[1];

		getline(NodeTXT, Line);
		FormulaLine = Split(Line, " ")[1];
	}

	CreateGraphicalRepresentationOfElement();
}


void MovingPoleNodeWidget::DrawElementToTexture()
{
	ParentMovingPoleWidget->GetMovingPoleWidgetTexture()->draw(MovingPoleNodeWidgetBody);

	for (sf::CircleShape* circle : InputShapes)
	{
		ParentMovingPoleWidget->GetMovingPoleWidgetTexture()->draw(*circle);
	}

	for (sf::CircleShape* circle : OutputShapes)
	{
		ParentMovingPoleWidget->GetMovingPoleWidgetTexture()->draw(*circle);
	}
}

void MovingPoleNodeWidget::InputHandler(sf::Event event)
{
	sf::Vector2f MouseCoords = FindMouseCoords(ParentMovingPoleWidget->GetMovingPoleWidgetTexture(), MovingPoleNodeWidgetWindow);

	if (event.type == event.MouseButtonPressed)
	{
		for (auto it = InputNodesMap.begin(); it != InputNodesMap.end(); it++)
		{
			if (IsShapeInSpriteContain(*ParentMovingPoleWidget->GetMovingPoleWidgetSprite(), *it->second.Circle, MouseCoords) &&
				it->second.InputConnection == nullptr)
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

		for (auto it = InputNodesMap.begin(); it != InputNodesMap.end(); it++)
		{
			if (IsShapeInSpriteContain(*ParentMovingPoleWidget->GetMovingPoleWidgetSprite(), *it->second.Circle, MouseCoords))
			{
				ParentMovingPoleWidget->CreateConnection(&(it->second));
			}
		}

		for (auto it = OutputNodesMap.begin(); it != OutputNodesMap.end(); it++)
		{
			if (IsShapeInSpriteContain(*ParentMovingPoleWidget->GetMovingPoleWidgetSprite(), *it->second.Circle, MouseCoords))
			{
				ParentMovingPoleWidget->CreateConnection(&(it->second));
			}
		}
	}

	if (event.type == event.MouseButtonReleased)
	{
		for (auto it = InputNodesMap.begin(); it != InputNodesMap.end(); it++)
		{
			if (IsShapeInSpriteContain(*ParentMovingPoleWidget->GetMovingPoleWidgetSprite(), *it->second.Circle, MouseCoords) &&
				ParentMovingPoleWidget->getCurrentConnectionWidget() != nullptr && 
				ParentMovingPoleWidget->getCurrentConnectionWidget()->getConnectionType() == OutputInput)
			{
				ParentMovingPoleWidget->getCurrentConnectionWidget()->setExitNode(&it->second);
				it->second.InputConnection = ParentMovingPoleWidget->getCurrentConnectionWidget();
				ParentMovingPoleWidget->ResetCurrentConnectionWidget(); 
			}
		}
		for (auto it = OutputNodesMap.begin(); it != OutputNodesMap.end(); it++)
		{
			if (IsShapeInSpriteContain(*ParentMovingPoleWidget->GetMovingPoleWidgetSprite(), *it->second.Circle, MouseCoords) &&
				ParentMovingPoleWidget->getCurrentConnectionWidget() != nullptr && 
				ParentMovingPoleWidget->getCurrentConnectionWidget()->getConnectionType() == InputOutput)
			{
				ParentMovingPoleWidget->getCurrentConnectionWidget()->setExitNode(&it->second);
				it->second.OutputConnection = ParentMovingPoleWidget->getCurrentConnectionWidget();
				ParentMovingPoleWidget->ResetCurrentConnectionWidget();
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

