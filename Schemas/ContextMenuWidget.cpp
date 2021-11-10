#include "ContextMenuWidget.h"

ContextMenuWidget::ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow) : ContextMenuWidgetWindow(contextMenuWidgetWindow)
{
	ContextMenuWidgetShape = new sf::RectangleShape(sf::Vector2f(305, 185));
	ContextMenuWidgetShape->setFillColor(sf::Color::Magenta);

	font.loadFromFile("Font.ttf");

	/// Кнопка добавления логического элемента
	ContextMenuWidgetAddLogicalElementButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetAddLogicalElementButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetAddLogicalElementButtonText = new sf::Text;
	ContextMenuWidgetAddLogicalElementButtonText->setFont(font);
	ContextMenuWidgetAddLogicalElementButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetAddLogicalElementButtonText->setString("Add logical element");
	ContextMenuWidgetAddLogicalElementButtonText->setCharacterSize(25);

	/// Кнопка для добавления папки
	ContextMenuWidgetAddFolderButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetAddFolderButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetAddFolderButtonText = new sf::Text;
	ContextMenuWidgetAddFolderButtonText->setFont(font);
	ContextMenuWidgetAddFolderButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetAddFolderButtonText->setString("Add folder");
	ContextMenuWidgetAddFolderButtonText->setCharacterSize(25);

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

		if (IsMenuCreatedToFolder)
		{
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetAddLogicalElementButton);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetAddFolderButton);
		}
		ContextMenuWidgetWindow->draw(*ContextMenuWidgetRenameButton);
		ContextMenuWidgetWindow->draw(*ContextMenuWidgetDeleteButton);

		if (IsMenuCreatedToFolder)
		{
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetAddLogicalElementButtonText);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetAddFolderButtonText);
		}
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

		// Обработка кнопки добавить логический элемент
		if (IsMenuCreatedToFolder && ContextMenuWidgetAddLogicalElementButton->getGlobalBounds().contains(CurrentMouseCoords))
		{
			if (IsConfirmWidgetRendering == false)
				ContextMenuWidgetAddLogicalElementButton->setFillColor(sf::Color::Blue);
			else
			{
				if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false)
					ContextMenuWidgetAddLogicalElementButton->setFillColor(sf::Color::Blue);
				else
				{
					ContextMenuWidgetAddLogicalElementButton->setFillColor(sf::Color::Black);
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
					CurrentButton = AddLogicalElement;
				}
				else
				{
					if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) != true)
					{
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetIsReceiveInput(true);
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetString("");
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetHintString("Insert name");
						OpenConfirmWidget();
						CurrentButton = AddLogicalElement;
					}
				}
			}
		}
		else
		{
			ContextMenuWidgetAddLogicalElementButton->setFillColor(sf::Color::Black);
		}

		// Обработка кнопки добавить папку
		if (IsMenuCreatedToFolder && ContextMenuWidgetAddFolderButton->getGlobalBounds().contains(CurrentMouseCoords))
		{
			if (IsConfirmWidgetRendering == false)
				ContextMenuWidgetAddFolderButton->setFillColor(sf::Color::Blue);
			else
			{
				if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false)
					ContextMenuWidgetAddFolderButton->setFillColor(sf::Color::Blue);
				else
				{
					ContextMenuWidgetAddFolderButton->setFillColor(sf::Color::Black);
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
					CurrentButton = AddFolder;
				}
				else
				{
					if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) != true)
					{
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetIsReceiveInput(true);
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetString("");
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->SetHintString("Insert name");
						OpenConfirmWidget();
						CurrentButton = AddLogicalElement;
					}
				}
			}
		}
		else
		{
			ContextMenuWidgetAddFolderButton->setFillColor(sf::Color::Black);
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

			case AddLogicalElement:
				if (ContextMenuWidgetConfirmMenuWidgetTextInputWidget->GetString() != "")
				{ 
					ContextMenuWidgetDropDownList->AddNewDropDownListElement(ContextMenuWidgetDropDownListElement,
						ContextMenuWidgetConfirmMenuWidgetTextInputWidget->GetString(), false);
				}
				CloseContextMenu();
				break;

			case AddFolder:
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
	IsMenuCreatedToFolder = contextMenuWidgetDropDownListElement->getIsFolder();

	if (IsMenuCreatedToFolder == true)
		ContextMenuWidgetShape->setSize(sf::Vector2f(305, 185));
	else
		ContextMenuWidgetShape->setSize(sf::Vector2f(305, 95));

	ContextMenuWidgetDropDownListElement = contextMenuWidgetDropDownListElement;

	/// Локальная переменная для отслеживания позиции курсора в окне
	sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);
	/// Сдвиг меню подтверждения в нижней части экрана
	float VerticalShift = 0;
	if (CurrentMouseCoords.y > ContextMenuWidgetWindow->getSize().y / 2)
		VerticalShift = ContextMenuWidgetShape->getSize().y;

	ContextMenuWidgetShape->setPosition(sf::Vector2f(CurrentMouseCoords.x, CurrentMouseCoords.y - VerticalShift));
	
	if (IsMenuCreatedToFolder == true)
	{
		ContextMenuWidgetAddLogicalElementButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5 - VerticalShift));
		ContextMenuWidgetAddLogicalElementButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5 - VerticalShift));

		ContextMenuWidgetAddFolderButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50 - VerticalShift));
		ContextMenuWidgetAddFolderButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50 - VerticalShift));

		ContextMenuWidgetRenameButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 95 - VerticalShift));
		ContextMenuWidgetRenameButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 95 - VerticalShift));

		ContextMenuWidgetDeleteButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 140 - VerticalShift));
		ContextMenuWidgetDeleteButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 140 - VerticalShift));
	}
	else
	{
		ContextMenuWidgetRenameButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5 - VerticalShift));
		ContextMenuWidgetRenameButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5 - VerticalShift));

		ContextMenuWidgetDeleteButton->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50 - VerticalShift));
		ContextMenuWidgetDeleteButtonText->setPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 50 - VerticalShift));
	}
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

	delete ContextMenuWidgetAddLogicalElementButton;
	delete ContextMenuWidgetAddFolderButton;
	delete ContextMenuWidgetDeleteButton;
	delete ContextMenuWidgetRenameButton;

	delete ContextMenuWidgetAddLogicalElementButtonText;
	delete ContextMenuWidgetAddFolderButtonText;
	delete ContextMenuWidgetDeleteButtonText;
	delete ContextMenuWidgetRenameButtonText;

	delete ContextMenuWidgetConfirmWidgetShape;
	delete ContextMenuWidgetConfirmWidgetAcceptShape;
	delete ContextMenuWidgetConfirmWidgetDeclineShape;

	delete ContextMenuWidgetConfirmWidgetAcceptText;
	delete ContextMenuWidgetConfirmWidgetDeclineText;

	delete ContextMenuWidgetConfirmMenuWidgetTextInputWidget;
}
