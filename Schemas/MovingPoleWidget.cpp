#include "MovingPoleWidget.h"

MovingPoleWidget::MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow, DropDownListWidget* movingPoleDropDownListWidget, DragAndDropWidget* movingPoleDragAndDropWidget) :
	MovingPoleWidgetWindow(movingPoleWidgetWindow), MovingPoleDropDownListWidget(movingPoleDropDownListWidget), MovingPoleDragAndDropWidget(movingPoleDragAndDropWidget)
{
	MovingPoleWidgetTexture = new sf::RenderTexture;
	MovingPoleWidgetTexture->create(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	MovingPoleWidgetTexture->display();

	MovingPoleWidgetSprite = new sf::Sprite;
	MovingPoleWidgetSprite->setTexture(MovingPoleWidgetTexture->getTexture());
}

void MovingPoleWidget::Tick()
{
	for (MovingPoleNodeWidget* widget : MovingPoleNodeVector)
	{
		widget->DrawElementToTexture();
	}

	MovingPoleWidgetWindow->draw(*MovingPoleWidgetSprite);
}

void MovingPoleWidget::InputHandler(sf::Event event)
{
	sf::Vector2f MouseCoords = FindMouseCoords(MovingPoleWidgetWindow);

	for (MovingPoleNodeWidget* widget : MovingPoleNodeVector)
	{
		widget->InputHandler(event);
	}

	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		IsDragStarted = true;
		LastMouseCoords = MouseCoords;
	}
	if (event.type == event.MouseButtonReleased)
		IsDragStarted = false;

	if (IsDragStarted)
	{
		for (MovingPoleNodeWidget* widget : MovingPoleNodeVector)
		{
			widget->Move(MouseCoords - LastMouseCoords);
		}

		MovingPoleWidgetTexture->clear(sf::Color(0, 0, 0, 0));

		for (MovingPoleNodeWidget* widget : MovingPoleNodeVector)
		{
			widget->DrawElementToTexture();
		}

		MovingPoleWidgetTexture->display();

		LastMouseCoords = MouseCoords;
	}

	if (event.type == event.MouseButtonReleased && MovingPoleDropDownListWidget->GetSprite()->getGlobalBounds().contains(MouseCoords) == false)
	{
		if (MovingPoleDragAndDropWidget != nullptr && MovingPoleDragAndDropWidget->getIsDragAndDropInProcess() &&
			MovingPoleDragAndDropWidget->getCurrentDropDownListElement()->getIsFolder() == false)
		{
			sf::Vector2f MouseCoords = FindMouseCoords(MovingPoleWidgetTexture, MovingPoleWidgetWindow);

			MovingPoleNodeWidget* NewNode = new MovingPoleNodeWidget(MovingPoleWidgetWindow, this,
				MovingPoleDragAndDropWidget->getCurrentDropDownListElement()->getName(), MouseCoords.x, MouseCoords.y);
			NewNode->CreateGraphicalRepresentationOfElement();
			NewNode->DrawElementToTexture();
			MovingPoleNodeVector.push_back(NewNode);
		}
	}

	if (event.type == event.MouseWheelMoved && MovingPoleDropDownListWidget->GetSprite()->getGlobalBounds().contains(MouseCoords) == false)
	{
		float multiplayer = 1;
		if (event.mouseWheel.delta == 1)
			multiplayer = 0.95;

		if (event.mouseWheel.delta == -1)
			multiplayer = 1.05;
		

		MovingPoleWidgetTexture->clear(sf::Color(0,0,0,0));

		sf::View view = MovingPoleWidgetTexture->getView();
		view.zoom(multiplayer);
		MovingPoleWidgetTexture->setView(view);

		for (MovingPoleNodeWidget* widget : MovingPoleNodeVector)
		{
			widget->DrawElementToTexture();
		}

		MovingPoleWidgetTexture->display();
	}
}

MovingPoleWidget::~MovingPoleWidget()
{
	delete MovingPoleWidgetTexture;
	delete MovingPoleWidgetSprite;

	for (MovingPoleNodeWidget* widget : MovingPoleNodeVector)
	{
		delete widget;
	}
}
