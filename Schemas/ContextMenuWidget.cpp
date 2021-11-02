#include "ContextMenuWidget.h"

ContextMenuWidget::ContextMenuWidget(sf::RenderWindow* contextMenuWidgetWindow) : ContextMenuWidgetWindow(contextMenuWidgetWindow)
{
	ContextMenuWidgetShape = new sf::RectangleShape(sf::Vector2f(305, 140));
	ContextMenuWidgetShape->setFillColor(sf::Color::Magenta);

	font.loadFromFile("Font.ttf");

	/// ������ ���������� ���
	ContextMenuWidgetAddButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetAddButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetAddButtonText = new sf::Text;
	ContextMenuWidgetAddButtonText->setFont(font);
	ContextMenuWidgetAddButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetAddButtonText->setString("Add logical element");
	ContextMenuWidgetAddButtonText->setCharacterSize(25);

	/// ������ �������������� ���
	ContextMenuWidgetRenameButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetRenameButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetRenameButtonText = new sf::Text;
	ContextMenuWidgetRenameButtonText->setFont(font);
	ContextMenuWidgetRenameButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetRenameButtonText->setString("Rename logical element");
	ContextMenuWidgetRenameButtonText->setCharacterSize(25);

	/// ������ �������� ���
	ContextMenuWidgetDeleteButton = new sf::RectangleShape(sf::Vector2f(295, 40));
	ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Black);

	ContextMenuWidgetDeleteButtonText = new sf::Text;
	ContextMenuWidgetDeleteButtonText->setFont(font);
	ContextMenuWidgetDeleteButtonText->setFillColor(sf::Color::Green);
	ContextMenuWidgetDeleteButtonText->setString("Delete logical element");
	ContextMenuWidgetDeleteButtonText->setCharacterSize(25);

	/// ���� ������������� 
	ContextMenuWidgetConfirmWidgetShape = new sf::RectangleShape(sf::Vector2f(305, 95));
	ContextMenuWidgetConfirmWidgetShape->setFillColor(sf::Color::Black);

	ContextMenuWidgetRenameButtonTextInputWidget = new TextInputWidget(ContextMenuWidgetWindow);

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
			ContextMenuWidgetRenameButtonTextInputWidget->Tick();
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetAcceptShape);
			ContextMenuWidgetWindow->draw(*ContextMenuWidgetConfirmWidgetDeclineShape);
		}
	}
}

void ContextMenuWidget::InputHandler(sf::Event event)
{
	if (IsRendering)
	{
		/// ��������� ���������� ��� ������������ ������� ������� � ����
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

		// ��������� ������ ��������
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
					ContextMenuWidgetRenameButtonTextInputWidget->SetString("");
					OpenConfirmWidget();
					CurrentButton = Add;
				}
				else
				{
					if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) != true)
					{
						ContextMenuWidgetRenameButtonTextInputWidget->SetString("");
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

		// ��������� ������ �������
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
				}
				else
				{
					if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) != true)
					{
						OpenConfirmWidget();
						CurrentButton = Delete;
					}
				}
			}
		}
		else
		{
			ContextMenuWidgetDeleteButton->setFillColor(sf::Color::Black);
		}

		// ��������� ������ �������������
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
					ContextMenuWidgetRenameButtonTextInputWidget->SetString(sf::String(ContextMenuWidgetDropDownListElement->getName()));
					OpenConfirmWidget();
					CurrentButton = Rename;
				}
				else
				{
					if (ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) != true)
					{
						ContextMenuWidgetRenameButtonTextInputWidget->SetString(sf::String(ContextMenuWidgetDropDownListElement->getName()));
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

		ContextMenuWidgetRenameButtonTextInputWidget->InputHandler(event);

		if (IsConfirmWidgetRendering && event.type == event.MouseButtonReleased &&
			event.mouseButton.button == sf::Mouse::Left && ContextMenuWidgetConfirmWidgetAcceptShape->getGlobalBounds().contains(CurrentMouseCoords))
		{
			switch (CurrentButton)
			{
			case None:
				break;

			case Add:
				if (ContextMenuWidgetRenameButtonTextInputWidget->GetString() != "")
				{ 
					ContextMenuWidgetDropDownList->AddNewDropDownListElement(ContextMenuWidgetDropDownListElement,
						ContextMenuWidgetRenameButtonTextInputWidget->GetString());
				}
				CloseContextMenu();
				break;

			case Rename:
				if (ContextMenuWidgetRenameButtonTextInputWidget->GetString() != "")
				{
					ContextMenuWidgetDropDownList->RenameDropDownListElement(ContextMenuWidgetDropDownListElement,
						ContextMenuWidgetRenameButtonTextInputWidget->GetString());
				}
				CloseContextMenu();
				break;

			case Delete:
				break;
			}
		}
	}
}

void ContextMenuWidget::OpenContextMenu(DropDownListElementWidget* contextMenuWidgetDropDownListElement)
{
	IsRendering = true;

	ContextMenuWidgetDropDownListElement = contextMenuWidgetDropDownListElement;

	/// ��������� ���������� ��� ������������ ������� ������� � ����
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
	CurrentButton = None;
	IsConfirmWidgetRendering = false;
	IsMouseOnShape = false;
	IsRendering = false;
}

void ContextMenuWidget::OpenConfirmWidget()
{	
	/// ��������� ���������� ��� ������������ ������� ������� � ����
	sf::Vector2f CurrentMouseCoords = FindMouseCoords(ContextMenuWidgetWindow);
	if ((IsConfirmWidgetRendering && ContextMenuWidgetConfirmWidgetShape->getGlobalBounds().contains(CurrentMouseCoords) == false) ||
		IsConfirmWidgetRendering == false)
	{
		IsConfirmWidgetRendering = true;
		ContextMenuWidgetConfirmWidgetShape->setPosition(CurrentMouseCoords);
		ContextMenuWidgetRenameButtonTextInputWidget->SetPosition(sf::Vector2f(CurrentMouseCoords.x + 5, CurrentMouseCoords.y + 5));
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
	delete ContextMenuWidgetConfirmWidgetAcceptShape;
	delete ContextMenuWidgetConfirmWidgetDeclineShape;

	delete ContextMenuWidgetRenameButtonTextInputWidget;
}
