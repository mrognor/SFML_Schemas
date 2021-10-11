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
		ListElementWindow->draw(*MainDropDownListElementShape);
		ListElementWindow->draw(*MainDropDownListElementText);
	}
}

void DropDownListElement::InputHandler(sf::Event event)
{
	if (IsRendering)
	{
		/// ��������� ���������� ��� ������������ ������� ������� � ����
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
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && IsMouseOnShape)
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
	}
}

DropDownListElement::~DropDownListElement()
{
	delete MainDropDownListElementShape;
	delete MainDropDownListElementText;
}