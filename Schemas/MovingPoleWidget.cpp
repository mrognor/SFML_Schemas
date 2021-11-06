#include "MovingPoleWidget.h"

MovingPoleWidget::MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow) : MovingPoleWidgetWindow(movingPoleWidgetWindow)
{
	ShapeToTest.setSize({ 100, 100 });
	ShapeToTest.setPosition({ 600, 600 });

	Texture = new sf::RenderTexture;
	Texture->create(1920, 1080);
	Texture->draw(ShapeToTest);
	Texture->display();

	Sprite = new sf::Sprite;
	Sprite->setTexture(Texture->getTexture());
}

void MovingPoleWidget::Tick()
{
	MovingPoleWidgetWindow->draw(*Sprite);
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
		Sprite->move(MouseCoords - LastMouseCoords);
		LastMouseCoords = MouseCoords;
	}

	if (event.type == event.MouseWheelMoved)
	{
		float multiplayer = 1;
		if (event.mouseWheel.delta == 1)
			multiplayer = 0.95;

		if (event.mouseWheel.delta == -1)
			multiplayer = 1.05;
		

		Texture->clear(sf::Color(0,0,0,0));
		sf::View view = Texture->getView();
		view.zoom(multiplayer);
		Texture->setView(view);

		Texture->draw(ShapeToTest);
		Texture->display();
	}
}

MovingPoleWidget::~MovingPoleWidget()
{
	delete Texture;
	delete Sprite;
}
