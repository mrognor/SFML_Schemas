#include "DropDownList.h"

DropDownList::DropDownList(sf::RenderWindow* mainWindow, int sizeX, int sizeY) : ListElementWindow(mainWindow)
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
				DropDownListElement* F = new DropDownListElement(this, ListElementWindow, vec[i], FilePath, DropDownListElementsVector.size());
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
	ListElementWindow->draw(WidgetBody);

	for (DropDownListElement* element : DropDownListElementsVector)
	{
		element->Tick();
	}
}

void DropDownList::FindAndSetDropDownListElementIndexes()
{
	int count = 0;
	for (DropDownListElement* element : DropDownListElementsVector)
	{
		if (element->getIsRendering())
		{
			element->setNumberInDropDownList(count);
			count++;
		}
		else element->setIsRendering(false);
	}
}

void DropDownList::OpenDropDownListElement(DropDownListElement* elementToOpen)
{
	std::vector<DropDownListElement*> ElementsToClose;
	for (DropDownListElement* element : DropDownListElementsVector)
	{
		if (element->getFullPath().find(elementToOpen->getFullPath() + "/") != -1)
		{
			element->setIsRendering(true);
			if (element->getIsDropDownListElementOpen() == false)
			{
				ElementsToClose.push_back(element);
			}
		}
	}

	for (DropDownListElement* element : ElementsToClose)
	{
		CloseDropDownListElement(element);
	}

	FindAndSetDropDownListElementIndexes();

	for (DropDownListElement* element : DropDownListElementsVector)
	{
		element->UpdateDropDownListElementPosition();
	}
}

void DropDownList::CloseDropDownListElement(DropDownListElement* elementToClose)
{
	for (DropDownListElement* element : DropDownListElementsVector)
	{
		if (element->getFullPath().find(elementToClose->getFullPath() + "/") != -1)
		{
			element->setIsRendering(false);
		}
	}

	FindAndSetDropDownListElementIndexes();

	for (DropDownListElement* element : DropDownListElementsVector)
	{
		element->UpdateDropDownListElementPosition();
	}
}

DropDownList::~DropDownList()
{
	for (DropDownListElement* folder : DropDownListElementsVector)
	{
		delete folder;
	}
}