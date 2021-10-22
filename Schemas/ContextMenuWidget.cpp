#include "ContextMenuWidget.h"

ContextMenuWidget::ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow) : ContextMenuWidgetWindow(contextMenuWidgetWindow)
{
	ContextMenuWidgetShape = new sf::RectangleShape(sf::Vector2f(305, 140));
	ContextMenuWidgetShape->setFillColor(sf::Color::Magenta);

	font.loadFromFile("Font.ttf");

	ContextMenuWidgetAddButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetAddButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetAddButtonText = new sf::Text;
	ContextMenuWidgetAddButtonText->setFont(font);
	ContextMenuWidgetAddButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetAddButtonText->setString("Add logical element");
	ContextMenuWidgetAddButtonText->setCharacterSize(25);

	ContextMenuWidgetDeleteButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetRenameButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetRenameButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetRenameButtonText = new sf::Text;
	ContextMenuWidgetRenameButtonText->setFont(font);
	ContextMenuWidgetRenameButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetRenameButtonText->setString("Rename logical element");
	ContextMenuWidgetRenameButtonText->setCharacterSize(25);

	ContextMenuWidgetDeleteButtonText = new sf::Text;
	ContextMenuWidgetDeleteButtonText->setFont(font);
	ContextMenuWidgetDeleteButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetDeleteButtonText->setString("Delete logical element");
	ContextMenuWidgetDeleteButtonText->setCharacterSize(25);
}

void ContextMenuWidget::Tick()
{
	if (IsRendering)
	{
		ContextMenuWidgetWindow->draw(*ContextMenuWidgetShape);

		ContextMenuWidgetWindow->draw(*ContextMenuWidgetAddButton);
		ContextMenuWidgetWindow->draw(*ContextMenuWidgetRenameButton);
		ContextMenuWidgetWindow->draw(*ContextMenuWidgetDeleteButton);

		ContextMenuWidgetWindow->draw(*ContextMenuWidgetAddButtonText);
		ContextMenuWidgetWindow->draw(*ContextMenuWidgetRenameButtonText);
		ContextMenuWidgetWindow->draw(*ContextMenuWidgetDeleteButtonText);
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

	if (event.type == event.MouseButtonReleased && IsRendering == true &&
		ContextMenuWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false)
	{
		CloseContextMenu();
	}

	if (ContextMenuWidgetAddButton->getGlobalBounds().contains(CurrentMouseCoords))
	{
		ContextMenuWidgetAddButton->setFillColor(sf::Color::Blue);
	}
	else
	{
		ContextMenuWidgetAddButton->setFillColor(sf::Color::Black);
	}

	if (ContextMenuWidgetDeleteButton->getGlobalBounds().contains(CurrentMouseCoords))
	{
		ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Blue);
	}
	else
	{
		ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Black);
	}

	if (ContextMenuWidgetRenameButton->getGlobalBounds().contains(CurrentMouseCoords))
	{
		ContextMenuWidgetRenameButton->setFillColor(sf::Color::Blue);
	}
	else
	{
		ContextMenuWidgetRenameButton->setFillColor(sf::Color::Black);
	}
}

void ContextMenuWidget::OpenContextMenu()
{
	IsRendering = true;
	/// Локальная переменная для отслеживания позиции курсора в окне
	sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);
	ContextMenuWidgetShape->setPosition(CurrentMouseCoords);
	
	ContextMenuWidgetAddButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5));
	ContextMenuWidgetAddButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5));

	ContextMenuWidgetRenameButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50));
	ContextMenuWidgetRenameButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50));

	ContextMenuWidgetDeleteButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 95));
	ContextMenuWidgetDeleteButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 95));
}

void ContextMenuWidget::CloseContextMenu()
{
	IsRendering = false;
}

ContextMenuWidget::~ContextMenuWidget()
{
	delete ContextMenuWidgetShape;

	delete ContextMenuWidgetAddButton;
	delete ContextMenuWidgetDeleteButton;
	delete ContextMenuWidgetRenameButton;

	delete ContextMenuWidgetAddButtonText;
	delete ContextMenuWidgetDeleteButtonText;
	delete ContextMenuWidgetRenameButtonText;
}
