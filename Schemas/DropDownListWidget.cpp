#include "DropDownListWidget.h"

DropDownListWidget::DropDownListWidget(sf::RenderWindow* mainWindow, DragAndDropWidget* dropDownListWindowDragAndDropWidget,
	ContextMenuWidget* dropDownListContextMenuWidget, int sizeX, int sizeY) : 
	DropDownListElementWindow(mainWindow), DropDownListDragAndDropWidget(dropDownListWindowDragAndDropWidget),
	DropDownListContextMenuWidget(dropDownListContextMenuWidget)
{

	WidgetBody.setSize(sf::Vector2f(sizeX, sizeY));
	WidgetBody.setFillColor(sf::Color::Black);

	LoadElementsFromFile();
}

void DropDownListWidget::LoadElementsFromFile()
{
	std::ifstream NodesTXT;

	NodesTXT.open("Nodes.txt");
	std::string Line;

	if (NodesTXT.is_open())
	{
		DropDownListElementsVector.clear();

		std::vector<DropDownListElementWidget*> ElementsToClose;

		while (getline(NodesTXT, Line))
		{
			std::vector<std::string> ParsedLine = Split(Line, " ");
			DropDownListElementWidget* F = new DropDownListElementWidget(this, DropDownListElementWindow, 
				DropDownListDragAndDropWidget, DropDownListContextMenuWidget, ParsedLine[1], ParsedLine[0],
				DropDownListElementsVector.size());

			
			if (ParsedLine[2] == std::string("true"))
				F->setIsDropDownListElementOpen(true);
			else
			{
				F->setIsDropDownListElementOpen(false);
				ElementsToClose.push_back(F);
			}
			
			DropDownListElementsVector.push_back(F);
		}

		for (DropDownListElementWidget* elem : ElementsToClose)
		{
			CloseDropDownListElement(elem);
		}
	}
	NodesTXT.close();
}

void DropDownListWidget::InputHandler(sf::Event event)
{
	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		element->InputHandler(event);
	}
	if (event.type == sf::Event::Closed)
	{
		std::ofstream NodesTXTOut;
		NodesTXTOut.open("Nodes.txt");

		if (NodesTXTOut.is_open())
		{
			for (DropDownListElementWidget* element : DropDownListElementsVector)
			{
				NodesTXTOut << element->getFullPath() << " " << element->getName() << " ";

				if (element->getIsDropDownListElementOpen())
					NodesTXTOut << std::string("true");
				else
					NodesTXTOut << std::string("false");

				NodesTXTOut << std::endl;
			}
		}
	}
}

void DropDownListWidget::Tick()
{
	DropDownListElementWindow->draw(WidgetBody);

	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		element->Tick();
	}
}

void DropDownListWidget::FindAndSetDropDownListElementIndexes()
{
	int count = 0;
	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		if (element->getIsRendering())
		{
			element->setNumberInDropDownList(count);
			count++;
		}
	}
}


void DropDownListWidget::OpenDropDownListElement(DropDownListElementWidget* elementToOpen)
{
	std::vector<DropDownListElementWidget*> ElementsToClose;
	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		if (element->getFullPath().find(elementToOpen->getFullPath()) != -1)
		{
			element->setIsRendering(true);
			if (element->getIsDropDownListElementOpen() == false)
			{
				ElementsToClose.push_back(element);
			}
		}
	}

	for (DropDownListElementWidget* element : ElementsToClose)
	{
		CloseDropDownListElement(element);
	}

	FindAndSetDropDownListElementIndexes();

	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		element->UpdateDropDownListElementPosition();
	}
}

void DropDownListWidget::CloseDropDownListElement(DropDownListElementWidget* elementToClose)
{
	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		//std::cout << element->getFullPath() << std::endl;
		if (element->getFullPath().find(elementToClose->getFullPath()) != -1 && 
			element->getFullPath() != elementToClose->getFullPath())
		{
			element->setIsRendering(false);
		}
	}

	FindAndSetDropDownListElementIndexes();

	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		element->UpdateDropDownListElementPosition();
	}
}

void DropDownListWidget::ReplaceDropDownListElement(DropDownListElementWidget* elementToMove, DropDownListElementWidget* destinationElement)
{
	if (destinationElement->getFullPath().find(elementToMove->getFullPath()) != -1)
		return;

	std::vector<std::string> StaticPaths;
	std::vector<std::string> MovingPaths;

	for (DropDownListElementWidget* elem : DropDownListElementsVector)
	{
		std::string StringToWrite;
		if (elem->getFullPath().find(elementToMove->getFullPath()) != -1)
		{
			StringToWrite = destinationElement->getFullPath() +
				elem->getFullPath().substr(elem->getFullPath().find(elementToMove->getName()), elem->getFullPath().find(" "))
				+ " " + elem->getName();
			
			if (elem->getIsDropDownListElementOpen())
				StringToWrite += " true" ;
			else 
				StringToWrite += " false";

			MovingPaths.push_back(StringToWrite);
		}
		else
		{
			StringToWrite = elem->getFullPath() + " " + elem->getName();
			if (elem->getIsDropDownListElementOpen())
				StringToWrite += " true";
			else
				StringToWrite += " false";
			StaticPaths.push_back(StringToWrite);
		}
	}

	
	std::cout << "MovingNodes" << std::endl;
	std::cout << elementToMove->getFullPath() << std::endl;
	std::cout << std::endl;

	std::cout << "DestinationNodes" << std::endl;
	std::cout << destinationElement->getFullPath() << std::endl;
	std::cout << std::endl;

	std::cout << "StaticPaths" << std::endl;
	for (std::string str : StaticPaths)
		std::cout << str << std::endl;
	std::cout << std::endl;

	std::cout << "MovingPaths" << std::endl;
	for (std::string str : MovingPaths)
		std::cout << str << std::endl;
	std::cout << std::endl;
	
	
	std::string Line;

	std::ofstream NodesTXTOut;
	NodesTXTOut.open("Nodes.txt");

	if (NodesTXTOut.is_open())
	{
		bool ShouldWriteMovingPaths = false;
		bool WasWriteMovingPaths = false;
		for (std::string stringToWriteIntoFile : StaticPaths)
		{
			if (ShouldWriteMovingPaths)
			{
				//std::cout << stringToWriteIntoFile.substr(0, stringToWriteIntoFile.find(" ")) << " " <<
				//	destinationElement->getFullPath() << std::endl;

				if (stringToWriteIntoFile.substr(0, stringToWriteIntoFile.find(" ")) > MovingPaths[0] || stringToWriteIntoFile.find(destinationElement->getFullPath()) == -1)
				{
					for (std::string str : MovingPaths)
						NodesTXTOut << str << std::endl;
					ShouldWriteMovingPaths = false;
					WasWriteMovingPaths = true;
				}
			}

			if (stringToWriteIntoFile.substr(0, stringToWriteIntoFile.find(" ")) == destinationElement->getFullPath())
			{	
				NodesTXTOut << stringToWriteIntoFile << std::endl;
				ShouldWriteMovingPaths = true;
			}

			else
			{
				NodesTXTOut << stringToWriteIntoFile << std::endl;
			}
		}
		if (WasWriteMovingPaths == false)
			for (std::string str : MovingPaths)
				NodesTXTOut << str << std::endl;
	}

	NodesTXTOut.close();
	
	LoadElementsFromFile();
}

DropDownListWidget::~DropDownListWidget()
{
	for (DropDownListElementWidget* folder : DropDownListElementsVector)
	{
		delete folder;
	}
}