#include "DropDownListElement.h"

DropDownListElement::DropDownListElement(DropDownList* dropDownListParent, sf::RenderWindow* window, std::string name, std::string path, int numberInDropDownList)
	: DropDownListParent(dropDownListParent), Name(name), FullPath(path), Window(window), NumberInDropDownList(numberInDropDownList)
{
	font.loadFromFile("Font.ttf");

	MainDropDownListElementShape = new sf::RectangleShape();
	MainDropDownListElementShape->setSize(sf::Vector2f(380 - 20 * CountInStr(FullPath, "/"), 40));
	
	MainDropDownListElementText = new sf::Text;
	MainDropDownListElementText->setFont(font);
	MainDropDownListElementText->setString(sf::String(Name));
	MainDropDownListElementText->setFillColor(sf::Color::Black);
	
	SetDropDownListElementPosition();
}

void DropDownListElement::SetDropDownListElementPosition()
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
	Window->draw(*MainDropDownListElementShape);
	Window->draw(*MainDropDownListElementText);
}

void DropDownListElement::InputHandler(sf::Event event)
{
	// OnHovered
	if (MainDropDownListElementShape->getGlobalBounds().contains
	(Window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*Window).x, sf::Mouse::getPosition(*Window).y)).x,
		Window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*Window).x, sf::Mouse::getPosition(*Window).y)).y))
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
	//if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && IsMouseOnShape)
	//{
	//	if (IsElementOpen)
	//	{
	//		IsElementOpen = false;
	//		DropDownListParent->CloseFolder(Name, FullPath);
	//	}
	//	else
	//	{
	//		IsElementOpen = true;
	//		DropDownListParent->OpenFolder(Name, FullPath);
	//	}
	//}
}

DropDownListElement::~DropDownListElement()
{
	delete MainDropDownListElementShape;
	delete MainDropDownListElementText;
}