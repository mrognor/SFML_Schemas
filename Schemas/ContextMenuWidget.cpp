#include "ContextMenuWidget.h"

ContextMenuWidget::ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow) : ContextMenuWidgetWindow(contextMenuWidgetWindow)
{
	ContextMenuWidgetShape = new sf::RectangleShape(sf::Vector2f(305, 140));
	ContextMenuWidgetShape->setFillColor(sf::Color::Magenta);

	font.loadFromFile("Font.ttf");

	/// Кнопка добавления нод
	ContextMenuWidgetAddButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetAddButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetAddButtonText = new sf::Text;
	ContextMenuWidgetAddButtonText->setFont(font);
	ContextMenuWidgetAddButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetAddButtonText->setString("Add logical element");
	ContextMenuWidgetAddButtonText->setCharacterSize(25);

	/// Кнопка переименования нод
	ContextMenuWidgetRenameButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetRenameButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetRenameButtonText = new sf::Text;
	ContextMenuWidgetRenameButtonText->setFont(font);
	ContextMenuWidgetRenameButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetRenameButtonText->setString("Rename logical element");
	ContextMenuWidgetRenameButtonText->setCharacterSize(25);

	/// Кнопка удаления нод
	ContextMenuWidgetDeleteButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetDeleteButtonText = new sf::Text;
	ContextMenuWidgetDeleteButtonText->setFont(font);
	ContextMenuWidgetDeleteButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetDeleteButtonText->setString("Delete logical element");
	ContextMenuWidgetDeleteButtonText->setCharacterSize(25);

	/// Меню подтверждения 
	ContextMenuWidgetConfirmWidgetShape = new sf::RectangleShape(sf::Vector2f(305, 95));
	ContextMenuWidgetConfirmWidgetShape->setFillColor(sf::Color::Black);

	ContextMenuWidgetConfirmWidgetTextInputShape = new sf::RectangleShape(sf::Vector2f(295, 40));

	ContextMenuWidgetConfirmWidgetTextInputText = new sf::Text;
	ContextMenuWidgetConfirmWidgetTextInputText->setFont(font);
	ContextMenuWidgetConfirmWidgetTextInputText->setFillColor(sf::Color::Green);
	ContextMenuWidgetConfirmWidgetTextInputText->setString("ABCDEFGHIJKLMNOPQRSTUVXYZW");
	ContextMenuWidgetConfirmWidgetTextInputText->setCharacterSize(25);

	ContextMenuWidgetConfirmWidgetTextInputShapeTexture = new sf::RenderTexture();
	ContextMenuWidgetConfirmWidgetTextInputShapeTexture->create(295, 40);
	ContextMenuWidgetConfirmWidgetTextInputShapeTexture->draw(*ContextMenuWidgetConfirmWidgetTextInputShape);
	ContextMenuWidgetConfirmWidgetTextInputShapeTexture->draw(*ContextMenuWidgetConfirmWidgetTextInputText);
	ContextMenuWidgetConfirmWidgetTextInputShapeTexture->display();

	ContextMenuWidgetConfirmWidgetTextInputShapeSprite = new sf::Sprite(ContextMenuWidgetConfirmWidgetTextInputShapeTexture->getTexture());

	ContextMenuWidgetConfirmWidgetAcceptShape = new sf::RectangleShape(sf::Vector2f(145, 40));

	ContextMenuWidgetConfirmWidgetDeclineShape = new sf::RectangleShape(sf::Vector2f(145, 40));
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

		if (IsConfirmWidgetRendering == true)
		{
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetShape);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetTextInputShapeSprite);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetAcceptShape);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetDeclineShape);
		}
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
		if (IsConfirmWidgetRendering == false)
			CloseContextMenu();
		else
		{
			if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false)
				CloseContextMenu();
		}
	}

	if (event.type == event.MouseButtonReleased && ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false)
	{
		IsConfirmWidgetRendering = false;
	}

	if (ContextMenuWidgetAddButton->getGlobalBounds().contains(CurrentMouseCoords))
	{
		if (IsConfirmWidgetRendering == false)
			ContextMenuWidgetAddButton->setFillColor(sf::Color::Blue);
		else
		{
			if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false)
				ContextMenuWidgetAddButton->setFillColor(sf::Color::Blue);
			else
			{
				ContextMenuWidgetAddButton->setFillColor(sf::Color::Black);
			}
		}
		
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && IsRendering == true)
		{
			OpenConfirmWidget();
		}
	}
	else
	{
		ContextMenuWidgetAddButton->setFillColor(sf::Color::Black);
	}

	if (ContextMenuWidgetDeleteButton->getGlobalBounds().contains(CurrentMouseCoords))
	{
		if (IsConfirmWidgetRendering == false)
			ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Blue);
		else
		{
			if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false)
				ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Blue);
			else
			{
				ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Black);
			}
		}
		
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && IsRendering == true)
		{
			OpenConfirmWidget();
		}
	}
	else
	{
		ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Black);
	}

	if (ContextMenuWidgetRenameButton->getGlobalBounds().contains(CurrentMouseCoords))
	{
		if (IsConfirmWidgetRendering == false)
			ContextMenuWidgetRenameButton->setFillColor(sf::Color::Blue);
		else
		{
			if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false)
				ContextMenuWidgetRenameButton->setFillColor(sf::Color::Blue);
			else
			{
				ContextMenuWidgetRenameButton->setFillColor(sf::Color::Black);
			}
		}
		
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && IsRendering == true)
		{
			OpenConfirmWidget();
		}
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

void ContextMenuWidget::OpenConfirmWidget()
{	
	/// Локальная переменная для отслеживания позиции курсора в окне
	sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);
	if ((IsConfirmWidgetRendering && ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false) ||
		IsConfirmWidgetRendering == false)
	{
		IsConfirmWidgetRendering = true;
		ContextMenuWidgetConfirmWidgetShape->setPosition(CurrentMouseCoords);
		ContextMenuWidgetConfirmWidgetTextInputShapeSprite->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5));
		ContextMenuWidgetConfirmWidgetAcceptShape->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50));
		ContextMenuWidgetConfirmWidgetDeclineShape->setPosition(sf::Vector2f(CurrentMouseCoords.x + 155, CurrentMouseCoords.y + 50));
	}
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

	delete ContextMenuWidgetConfirmWidgetShape;
	delete ContextMenuWidgetConfirmWidgetTextInputShape;
	delete ContextMenuWidgetConfirmWidgetAcceptShape;
	delete ContextMenuWidgetConfirmWidgetDeclineShape;

	delete ContextMenuWidgetConfirmWidgetTextInputShapeTexture;
	delete ContextMenuWidgetConfirmWidgetTextInputShapeSprite;
}
