#include "MovingPoleConnectionWidget.h"

MovingPoleConnectionWidget::MovingPoleConnectionWidget(sf::RenderWindow* window, MovingPoleWidget* parentMovingPoleWidget, OutputNode* entryNode) :
	Window(window), ParentMovingPoleWidget(parentMovingPoleWidget), EntryNode(entryNode)
{
	ConnectionBody.setFillColor(sf::Color::Blue);
	ConnectionBody.setOrigin({ ConnectionThickness / 2, 0 });

	Start = EntryNode->Circle->getPosition();
	ConnectionBody.setPosition(Start);
}

void MovingPoleConnectionWidget::DrawElementToTexture()
{
	if (IsConnectionNodePlaced == false)
	{
		sf::Vector2f MouseCoords = FindMouseCoords(ParentMovingPoleWidget->GetMovingPoleWidgetTexture(), Window);
		ConnectionBody.setSize({ ConnectionThickness, float(sqrt(pow(MouseCoords.x - Start.x, 2) + pow(MouseCoords.y - Start.y, 2))) });

		float angle = atan((MouseCoords.y - Start.y) / (MouseCoords.x - Start.x)) * 180.0 / PI;
		if (MouseCoords.x > Start.x)
			angle += 270;
		else angle += 90;

		ConnectionBody.setRotation(angle);
	}

	//ConnectionBody.setFillColor(EntryNode->Circle->getFillColor());
	ParentMovingPoleWidget->GetMovingPoleWidgetTexture()->draw(ConnectionBody);
}

void MovingPoleConnectionWidget::InputHandler(sf::Event event)
{
	if (event.type == event.MouseButtonReleased && IsConnectionNodePlaced == false)
	{
		if (ExitNode == nullptr)
			ParentMovingPoleWidget->DeleteConnection(this);
		else
		{
			ConnectionBody.setSize({ ConnectionThickness, float(sqrt(pow(ExitNode->Circle->getPosition().x - Start.x, 2) +
				pow(ExitNode->Circle->getPosition().y - Start.y, 2))) });

			float angle = atan((ExitNode->Circle->getPosition().y - Start.y) / (ExitNode->Circle->getPosition().x - Start.x)) * 180.0 / PI;
			if (ExitNode->Circle->getPosition().x > Start.x)
				angle += 270;
			else angle += 90;

			ConnectionBody.setRotation(angle);

			IsConnectionNodePlaced = true;
		}
	}
}

void MovingPoleConnectionWidget::Move(sf::Vector2f vec)
{
	ConnectionBody.move(vec);
}


MovingPoleConnectionWidget::~MovingPoleConnectionWidget()
{
}