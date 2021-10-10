#include "DropDownList.h"

DropDownList::DropDownList(sf::RenderWindow* mainWindow, int sizeX, int sizeY) : Window(mainWindow)
{
	std::ifstream NodesTXT;
	sf::Font font;

	NodesTXT.open("Nodes.txt");

	WidgetBody.setSize(sf::Vector2f(sizeX, sizeY));
	WidgetBody.setFillColor(sf::Color::Black);

	std::string Line;

	if (NodesTXT.is_open())
	{
		while (getline(NodesTXT, Line))
		{
			auto vec = Split(Line, "/");
			std::string FilePath;

			for (int i = 0; i < vec.size(); i++)
			{
				FilePath += vec[i];
				DropDownListElement* F = new DropDownListElement(this, Window, vec[i], FilePath, DropDownListElementsVector.size());
				if (IsInVector(DropDownListElementsVector, F) == false)
				{
					DropDownListElementsVector.push_back(F);
				}
				else delete F;
				FilePath += "/";
			}
		}
	}
}

void DropDownList::InputHandler(sf::Event event)
{
	for (DropDownListElement* element : DropDownListElementsVector)
	{
		element->InputHandler(event);
	}
}

void DropDownList::Tick()
{
	Window->draw(WidgetBody);

	for (DropDownListElement* element : DropDownListElementsVector)
	{
		element->Tick();
	}
}

DropDownList::~DropDownList()
{
	for (DropDownListElement* folder : DropDownListElementsVector)
	{
		delete folder;
	}
}