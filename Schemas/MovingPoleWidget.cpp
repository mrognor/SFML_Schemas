#include "MovingPoleWidget.h"

MovingPoleWidget::MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow, DropDownListWidget* movingPoleDropDownListWidget, DragAndDropWidget* movingPoleDragAndDropWidget) :
	MovingPoleWidgetWindow(movingPoleWidgetWindow), MovingPoleDropDownListWidget(movingPoleDropDownListWidget), MovingPoleDragAndDropWidget(movingPoleDragAndDropWidget)
{
	MovingPoleWidgetTexture = new sf::RenderTexture;
	MovingPoleWidgetTexture->create(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	MovingPoleWidgetTexture->display();

	MovingPoleWidgetSprite = new sf::Sprite;
	MovingPoleWidgetSprite->setTexture(MovingPoleWidgetTexture->getTexture());

	TestPoleWidget1 = new MovingPoleNodeWidget(MovingPoleWidgetWindow, this, 600, 200);
	TestPoleWidget1->CreateGraphicalRepresentationOfElement();
	TestPoleWidget1->DrawElementToTexture();
}

void MovingPoleWidget::Tick()
{
	TestPoleWidget1->DrawElementToTexture();

	MovingPoleWidgetWindow->draw(*MovingPoleWidgetSprite);
}

void MovingPoleWidget::InputHandler(sf::Event event)
{
	sf::Vector2f MouseCoords = FindMouseCoords(MovingPoleWidgetWindow);

	TestPoleWidget1->InputHandler(event);

	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		IsDragStarted = true;
		LastMouseCoords = MouseCoords;
	}
	if (event.type == event.MouseButtonReleased)
		IsDragStarted = false;

	if (IsDragStarted)
	{
		TestPoleWidget1->Move(MouseCoords - LastMouseCoords);

		MovingPoleWidgetTexture->clear(sf::Color(0, 0, 0, 0));
		TestPoleWidget1->DrawElementToTexture();

		MovingPoleWidgetTexture->display();

		LastMouseCoords = MouseCoords;
	}

	if (event.type == event.MouseButtonReleased && MovingPoleDropDownListWidget->GetSprite()->getGlobalBounds().contains(MouseCoords) == false)
	{
		if (MovingPoleDragAndDropWidget != nullptr && MovingPoleDragAndDropWidget->getIsDragAndDropInProcess() &&
			MovingPoleDragAndDropWidget->getCurrentDropDownListElement()->getIsFolder() == false)
		{
			std::cout << "GF" << std::endl;
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

		TestPoleWidget1->DrawElementToTexture();
		MovingPoleWidgetTexture->display();
	}
}

MovingPoleWidget::~MovingPoleWidget()
{
	delete MovingPoleWidgetTexture;
	delete MovingPoleWidgetSprite;

	delete TestPoleWidget1;
}
