#include "ContextMenuWidget.h"

ContextMenuWidget::ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow) : ContextMenuWidgetWindow(contextMenuWidgetWindow)
{
	ContextMenuWidgetShape = new sf::RectangleShape(sf::Vector2f(200, 500));
	ContextMenuWidgetShape->setFillColor(sf::Color::Magenta);
}

void ContextMenuWidget::Tick()
{
	if (IsRendering)
	{
		ContextMenuWidgetWindow->draw(*ContextMenuWidgetShape);
	}
}

void ContextMenuWidget::InputHandler(sf::Event event)
{
	/// Локальная переменная для отслеживания позиции курсора в окне
	sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);
	if (ContextMenuWidgetShape->getGlobalBounds().contains(CurrentMouseCoords.x, CurrentMouseCoords.y) && IsRendering)
	{
		IsMouseOnShape = true;
	}
	else 
		IsMouseOnShape = false;

	if (event.type == event.MouseButtonReleased && IsRendering == true)
	{
		CloseContextMenu();
	}
}

void ContextMenuWidget::OpenContextMenu()
{
	IsRendering = true;
	/// Локальная переменная для отслеживания позиции курсора в окне
	sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);
	ContextMenuWidgetShape->setPosition(CurrentMouseCoords);
}

void ContextMenuWidget::CloseContextMenu()
{
	IsRendering = false;
}

ContextMenuWidget::~ContextMenuWidget()
{
	delete ContextMenuWidgetShape;
}
