#include "MovingPoleConnectionWidget.h"

MovingPoleConnectionWidget::MovingPoleConnectionWidget(sf::RenderWindow* window, MovingPoleWidget* parentMovingPoleWidget, OutputNode* entryNode) :
	Window(window), ParentMovingPoleWidget(parentMovingPoleWidget), EntryNode_Output(entryNode)
{
	ConnectionType = OutputInput;

	EntryNode_Output->OutputConnections.push_back(this);

	Value = EntryNode_Output->Value;
	if (Value == true)
		ConnectionBody.setFillColor(sf::Color::Blue);
	else
		ConnectionBody.setFillColor(sf::Color::Magenta);

	ConnectionBody.setOrigin({ ConnectionThickness / 2, 0 });

	Start = EntryNode_Output->Circle->getPosition();
	ConnectionBody.setPosition(Start);
}

MovingPoleConnectionWidget::MovingPoleConnectionWidget(sf::RenderWindow* window, MovingPoleWidget* parentMovingPoleWidget, InputNode* entryNode) :
	Window(window), ParentMovingPoleWidget(parentMovingPoleWidget), EntryNode_Input(entryNode)
{
	ConnectionType = InputOutput;

	EntryNode_Input->InputConnection = this;

	Value = EntryNode_Input->Value;
	if (Value == true)
		ConnectionBody.setFillColor(sf::Color::Blue);
	else
		ConnectionBody.setFillColor(sf::Color::Magenta);

	ConnectionBody.setOrigin({ ConnectionThickness / 2, 0 });

	Start = EntryNode_Input->Circle->getPosition();
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

	//ConnectionBody.setFillColor(EntryNode_Output->Circle->getFillColor());
	ParentMovingPoleWidget->GetMovingPoleWidgetTexture()->draw(ConnectionBody);
}

void MovingPoleConnectionWidget::InputHandler(sf::Event event)
{
	if (event.type == event.MouseButtonReleased && IsConnectionNodePlaced == false)
	{
		if ((ConnectionType == OutputInput && ExitNode_Input == nullptr) ||
			(ConnectionType == InputOutput && ExitNode_Output == nullptr))
		{
			if (EntryNode_Output != nullptr)
				EntryNode_Output->OutputConnections.clear();

			if(EntryNode_Input != nullptr)
				EntryNode_Input->InputConnection = nullptr;

			ParentMovingPoleWidget->DeleteConnection(this);
		}
		else
		{
			if (ConnectionType == OutputInput)
			{
				ConnectionBody.setSize({ ConnectionThickness, float(sqrt(pow(ExitNode_Input->Circle->getPosition().x - Start.x, 2) +
					pow(ExitNode_Input->Circle->getPosition().y - Start.y, 2))) });

				float angle = atan((ExitNode_Input->Circle->getPosition().y - Start.y) / (ExitNode_Input->Circle->getPosition().x - Start.x)) * 180.0 / PI;
				if (ExitNode_Input->Circle->getPosition().x > Start.x)
					angle += 270;
				else angle += 90;

				ConnectionBody.setRotation(angle);
			}

			if (ConnectionType == InputOutput)
			{
				ConnectionBody.setSize({ ConnectionThickness, float(sqrt(pow(ExitNode_Output->Circle->getPosition().x - Start.x, 2) +
					pow(ExitNode_Output->Circle->getPosition().y - Start.y, 2))) });

				float angle = atan((ExitNode_Output->Circle->getPosition().y - Start.y) / (ExitNode_Output->Circle->getPosition().x - Start.x)) * 180.0 / PI;
				if (ExitNode_Output->Circle->getPosition().x > Start.x)
					angle += 270;
				else angle += 90;

				ConnectionBody.setRotation(angle);
			}
			

			IsConnectionNodePlaced = true;
		}
	}
}

void MovingPoleConnectionWidget::Move(sf::Vector2f vec)
{
	ConnectionBody.move(vec);
}


void MovingPoleConnectionWidget::UpdateConnectionElement()
{
	if (ConnectionType == InputOutput)
	{
		Value = ExitNode_Output->Value;

		if (Value == true)
			ConnectionBody.setFillColor(sf::Color::Blue);
		else
			ConnectionBody.setFillColor(sf::Color::Magenta);

		EntryNode_Input->Value = ExitNode_Output->Value;
		EntryNode_Input->ParentNodeWidget->UpdateLogicalOutputs();
	}

	if (ConnectionType == OutputInput)
	{

		Value = EntryNode_Output->Value;
		if (Value == true)
			ConnectionBody.setFillColor(sf::Color::Blue);
		else
			ConnectionBody.setFillColor(sf::Color::Magenta);

		ExitNode_Input->Value = EntryNode_Output->Value;
		ExitNode_Input->ParentNodeWidget->UpdateLogicalOutputs();
	}
}

MovingPoleConnectionWidget::~MovingPoleConnectionWidget()
{
}