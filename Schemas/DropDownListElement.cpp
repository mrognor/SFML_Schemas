#include "DropDownListElement.h"

DropDownListElement::DropDownListElement(DropDownList* dropDownListParent, sf::RenderWindow* window, std::string name, std::string path, int numberInDropDownList)
	: DropDownListParent(dropDownListParent), Name(name), FullPath(path), ListElementWindow(window), NumberInDropDownList(numberInDropDownList)
{
	font.loadFromFile("Font.ttf");

	MainDropDownListElementShape = new sf::RectangleShape();
	MainDropDownListElementShape->setSize(sf::Vector2f(380 - 20 * CountInStr(FullPath, "/"), 40));
	
	MainDropDownListElementText = new sf::Text;
	MainDropDownListElementText->setFont(font);
	MainDropDownListElementText->setString(sf::String(Name));
	MainDropDownListElementText->setFillColor(sf::Color::Black);


	DragNDropListElementText = new sf::Text;
	DragNDropListElementText->setFont(font);
	DragNDropListElementText->setString(sf::String(Name) + "DRAG");
	DragNDropListElementText->setFillColor(sf::Color::Black);

	DragNDropListElementShape = new sf::RectangleShape();
	DragNDropListElementShape->setSize(sf::Vector2f(DragNDropListElementText->getGlobalBounds().width, DragNDropListElementText->getGlobalBounds().height*2));

	UpdateDropDownListElementPosition();
}

void DropDownListElement::UpdateDropDownListElementPosition()
{
	MainDropDownListElementShape->setPosition(10 + 20 * CountInStr(FullPath, "/"), 10 + NumberInDropDownList * 50);

	MainDropDownListElementText->setPosition(15 + 20 * CountInStr(FullPath, "/"), 15 + NumberInDropDownList * 50);
}

bool DropDownListElement::operator==(const DropDownListElement& Obj)
{
	if (FullPath == Obj.FullPath && Name == Obj.Name)
		return true;
	return false;
}

bool DropDownListElement::operator!=(const DropDownListElement& Obj)
{
	if (FullPath == Obj.FullPath && Name == Obj.Name)
		return false;
	return true;
}

void DropDownListElement::Tick()
{
	if (IsRendering)
	{
		/// Локальная переменная для отслеживания позиции курсора в окне
		sf::Vector2f CurrentMouseCoords = FindMouseCoords(ListElementWindow);

		ListElementWindow->draw(*MainDropDownListElementShape);
		ListElementWindow->draw(*MainDropDownListElementText);

		if (IsDragListElementInProcess && DragStartListElementCoords != CurrentMouseCoords)
		{
			DragNDropListElementShape->setPosition(CurrentMouseCoords.x, CurrentMouseCoords.y);
			DragNDropListElementText->setPosition(CurrentMouseCoords.x, CurrentMouseCoords.y);
			ListElementWindow->draw(*DragNDropListElementShape);
			ListElementWindow->draw(*DragNDropListElementText);
		}
	}
}

void DropDownListElement::InputHandler(sf::Event event)
{
	if (IsRendering)
	{
		/// Локальная переменная для отслеживания позиции курсора в окне
		sf::Vector2f CurrentMouseCoords= FindMouseCoords(ListElementWindow);

		// OnHovered
		if (MainDropDownListElementShape->getGlobalBounds().contains(CurrentMouseCoords.x, CurrentMouseCoords.y))
		{
			IsMouseOnShape = true;
			MainDropDownListElementShape->setFillColor(sf::Color::Blue);
		}
		else
		{
			IsMouseOnShape = false;
			MainDropDownListElementShape->setFillColor(sf::Color::White);
		}

		// OnClicked
		if (event.type == event.MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (IsMouseOnShape && IsDragListElementInProcess == true)
				{
					if (IsDropDownListElementOpen)
					{
						IsDropDownListElementOpen = false;
						DropDownListParent->CloseDropDownListElement(this);
					}
					else
					{
						IsDropDownListElementOpen = true;
						DropDownListParent->OpenDropDownListElement(this);
					}
				}

				IsDragListElementInProcess = false;
			}
		}

		if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && IsMouseOnShape)
		{
			DragStartListElementCoords = CurrentMouseCoords;
			IsDragListElementInProcess = true;
		}

	}
}

DropDownListElement::~DropDownListElement()
{
	delete MainDropDownListElementShape;
	delete MainDropDownListElementText;
}