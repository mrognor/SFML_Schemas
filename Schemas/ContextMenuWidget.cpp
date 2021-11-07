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

	ContextMenuWidgetConfirmMenuWidgetTextInputWidget = new TextInputWidget(ContextMenuWidgetWindow);

	ContextMenuWidgetConfirmWidgetAcceptShape = new sf::RectangleShape(sf::Vector2f(145, 40));
	ContextMenuWidgetConfirmWidgetAcceptText = new sf::Text("Accept", font);
	ContextMenuWidgetConfirmWidgetAcceptText->setFillColor(sf::Color::Black);

	ContextMenuWidgetConfirmWidgetDeclineShape = new sf::RectangleShape(sf::Vector2f(145, 40));
	ContextMenuWidgetConfirmWidgetDeclineText = new sf::Text("Decline", font);
	ContextMenuWidgetConfirmWidgetDeclineText->setFillColor(sf::Color::Black);
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
			ContextMenuWidgetConfirmMenuWidgetTextInputWidget->Tick();
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetAcceptShape);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetDeclineShape);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetAcceptText);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetDeclineText);
		}
	}
}

void ContextMenuWidget::InputHandler(sf::Event event)
{
	if (IsRendering)
	{
		/// Локальная переменная для отслеживания позиции курсора в окне
		sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);

		if (ContextMenuWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) && IsRendering)
		{
			IsMouseOnShape = true;
		}
		else
			IsMouseOnShape = false;

		if (IsConfirmWidgetRendering && ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords))
		{
			IsMouseOnShape = true;
		}

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
			CurrentButton = None;
		}

		// Обработка кнопки добавить
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
				if (IsConfirmWidgetRendering == false)
				{
					ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetIsReceiveInput(true);
					ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetString("");
					ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetHintString("Insert name");
					OpenConfirmWidget();
					CurrentButton = Add;
				}
				else
				{
					if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) != true)
					{
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetIsReceiveInput(true);
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetString("");
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetHintString("Insert name");
						OpenConfirmWidget();
						CurrentButton = Add;
					}
				}
			}
		}
		else
		{
			ContextMenuWidgetAddButton->setFillColor(sf::Color::Black);
		}

		// Обработка кнопки удалить
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
				if (IsConfirmWidgetRendering == false)
				{
					OpenConfirmWidget();
					CurrentButton = Delete;
					ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetIsReceiveInput(false);
					ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetString("          Delete ?");
					
				}
				else
				{
					if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) != true)
					{
						OpenConfirmWidget();
						CurrentButton = Delete;
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetIsReceiveInput(false);
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetString("          Delete ?");
						
					}
				}
			}
		}
		else
		{
			ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Black);
		}

		// Обработка кнопки переименовать
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
				if (IsConfirmWidgetRendering == false)
				{
					ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetIsReceiveInput(true);
					ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetString(sf::String(ContextMenuWidgetDropDownListElement->getName()));
					OpenConfirmWidget();
					CurrentButton = Rename;
				}
				else
				{
					if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) != true)
					{
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetIsReceiveInput(true);
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetString(sf::String(ContextMenuWidgetDropDownListElement->getName()));
						OpenConfirmWidget();
						CurrentButton = Rename;
					}
				}
			}
		}
		else
		{
			ContextMenuWidgetRenameButton->setFillColor(sf::Color::Black);
		}

		ContextMenuWidgetConfirmMenuWidgetTextInputWidget->InputHandler(event);

		if (IsConfirmWidgetRendering && event.type == event.MouseButtonReleased &&
			event.mouseButton.button == sf::Mouse::Left && ContextMenuWidgetConfirmWidgetDeclineShape->getGlobalBounds().contains(CurrentMouseCoords))
		{
			IsConfirmWidgetRendering = false;
		}

		if (IsConfirmWidgetRendering && event.type == event.MouseButtonReleased &&
			event.mouseButton.button == sf::Mouse::Left && ContextMenuWidgetConfirmWidgetAcceptShape->getGlobalBounds().contains(CurrentMouseCoords))
		{
			switch (CurrentButton)
			{
			case None:
				break;

			case Add:
				if (ContextMenuWidgetConfirmMenuWidgetTextInputWidget->GetString() != "")
				{ 
					ContextMenuWidgetDropDownList->AddNewDropDownListElement(ContextMenuWidgetDropDownListElement,
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->GetString());
				}
				CloseContextMenu();
				break;

			case Rename:
				if (ContextMenuWidgetConfirmMenuWidgetTextInputWidget->GetString() != "")
				{
					ContextMenuWidgetDropDownList->RenameDropDownListElement(ContextMenuWidgetDropDownListElement,
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->GetString());
				}
				CloseContextMenu();
				break;

			case Delete:
				ContextMenuWidgetDropDownList->DeleteDropDownListElement(ContextMenuWidgetDropDownListElement);
				CloseContextMenu();
				break;
			}
		}
	}
}

void ContextMenuWidget::OpenContextMenu(DropDownListElementWidget* contextMenuWidgetDropDownListElement)
{
	IsRendering = true;

	ContextMenuWidgetDropDownListElement = contextMenuWidgetDropDownListElement;

	/// Локальная переменная для отслеживания позиции курсора в окне
	sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);
	float VerticalShift = 0;
	if (CurrentMouseCoords.y > ContextMenuWidgetWindow->getSize().y / 2)
		VerticalShift = ContextMenuWidgetShape->getSize().y;

	ContextMenuWidgetShape->setPosition(sf::Vector2f(CurrentMouseCoords.x, CurrentMouseCoords.y - VerticalShift));
	
	ContextMenuWidgetAddButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5 - VerticalShift));
	ContextMenuWidgetAddButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5 - VerticalShift));

	ContextMenuWidgetRenameButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50 - VerticalShift));
	ContextMenuWidgetRenameButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50 - VerticalShift));

	ContextMenuWidgetDeleteButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 95 - VerticalShift));
	ContextMenuWidgetDeleteButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 95 - VerticalShift));
}

void ContextMenuWidget::CloseContextMenu()
{
	CurrentButton = None;
	IsConfirmWidgetRendering = false;
	IsMouseOnShape = false;
	IsRendering = false;
}

void ContextMenuWidget::OpenConfirmWidget()
{	
	/// Локальная переменная для отслеживания позиции курсора в окне
	sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);
	if ((IsConfirmWidgetRendering && ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false) ||
		IsConfirmWidgetRendering == false)
	{
		float VerticalShift = 0;
		if (CurrentMouseCoords.y > ContextMenuWidgetWindow->getSize().y / 2)
			VerticalShift = ContextMenuWidgetConfirmWidgetShape->getSize().y;

		IsConfirmWidgetRendering = true;

		ContextMenuWidgetConfirmWidgetShape->setPosition(sf::Vector2f(CurrentMouseCoords.x, CurrentMouseCoords.y - VerticalShift));
		ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5 - VerticalShift));
		ContextMenuWidgetConfirmWidgetAcceptShape->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50 - VerticalShift));
		ContextMenuWidgetConfirmWidgetDeclineShape->setPosition(sf::Vector2f(CurrentMouseCoords.x + 155, CurrentMouseCoords.y + 50 - VerticalShift));
	
		ContextMenuWidgetConfirmWidgetAcceptText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 25, CurrentMouseCoords.y + 50 - VerticalShift));
		ContextMenuWidgetConfirmWidgetDeclineText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 175, CurrentMouseCoords.y + 50 - VerticalShift));
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
	delete ContextMenuWidgetConfirmWidgetAcceptShape;
	delete ContextMenuWidgetConfirmWidgetDeclineShape;

	delete ContextMenuWidgetConfirmWidgetAcceptText;
	delete ContextMenuWidgetConfirmWidgetDeclineText;

	delete ContextMenuWidgetConfirmMenuWidgetTextInputWidget;
}
