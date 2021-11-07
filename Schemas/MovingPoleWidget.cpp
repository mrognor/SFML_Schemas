#include "MovingPoleWidget.h"

MovingPoleWidget::MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow, DropDownListWidget* movingPoleDropDownListWidget) :
	MovingPoleWidgetWindow(movingPoleWidgetWindow), MovingPoleDropDownListWidget(movingPoleDropDownListWidget)
{
	ShapeToTest.setSize({ 100, 100 });
	ShapeToTest.setPosition({ 600, 600 });

	MovingPoleWidgetTexture = new sf::RenderTexture;
	MovingPoleWidgetTexture->create(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	MovingPoleWidgetTexture->draw(ShapeToTest);
	MovingPoleWidgetTexture->display();

	MovingPoleWidgetSprite = new sf::Sprite;
	MovingPoleWidgetSprite->setTexture(MovingPoleWidgetTexture->getTexture());
}

void MovingPoleWidget::Tick()
{
	MovingPoleWidgetWindow->draw(*MovingPoleWidgetSprite);
}

void MovingPoleWidget::InputHandler(sf::Event event)
{
	sf::Vector2f MouseCoords = FindMouseCoords(MovingPoleWidgetWindow);

	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		IsDragStarted = true;
		LastMouseCoords = MouseCoords;
	}
	if (event.type == event.MouseButtonReleased)
		IsDragStarted = false;

	if (IsDragStarted)
	{
		ShapeToTest.move(MouseCoords - LastMouseCoords);

		MovingPoleWidgetTexture->clear(sf::Color(0, 0, 0, 0));
		MovingPoleWidgetTexture->draw(ShapeToTest);
		MovingPoleWidgetTexture->display();

		LastMouseCoords = MouseCoords;
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

		MovingPoleWidgetTexture->draw(ShapeToTest);
		MovingPoleWidgetTexture->display();
	}
}

MovingPoleWidget::~MovingPoleWidget()
{
	delete MovingPoleWidgetTexture;
	delete MovingPoleWidgetSprite;
}
