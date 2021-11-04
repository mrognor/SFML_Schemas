#include "DropDownListWidget.h"

DropDownListWidget::DropDownListWidget(sf::RenderWindow* mainWindow, DragAndDropWidget* dropDownListWindowDragAndDropWidget,
	ContextMenuWidget* dropDownListContextMenuWidget, int sizeX, int sizeY) : 
	DropDownListWindow(mainWindow), DropDownListDragAndDropWidget(dropDownListWindowDragAndDropWidget),
	DropDownListContextMenuWidget(dropDownListContextMenuWidget)
{
	DropDownListElementWidgetTexture = new sf::RenderTexture();
	DropDownListElementWidgetTexture->create(sizeX, sizeY);
	DropDownListElementWidgetTexture->clear(sf::Color::Black);

	DropDownListElementWidgetSprite = new sf::Sprite();
	DropDownListElementWidgetSprite->setTexture(DropDownListElementWidgetTexture->getTexture());

	LoadElementsFromFile();
}

void DropDownListElementWidget::setIsRendering(bool f)
{
	IsRendering = f; 
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
			DropDownListElementWidget* F = new DropDownListElementWidget(this, DropDownListWindow, 
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
	DropDownListElementWidgetTexture->clear(sf::Color::Black);

	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		element->Tick();
		element->DrawDropDownListElementToTexture(DropDownListElementWidgetTexture);
	}
	DropDownListElementWidgetTexture->display();

	DropDownListWindow->draw(*DropDownListElementWidgetSprite);
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

	std::vector<std::string> StaticNodes;
	std::vector<std::string> MovingNodes;

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

			MovingNodes.push_back(StringToWrite);
		}
		else
		{
			StringToWrite = elem->getFullPath() + " " + elem->getName();
			if (elem->getIsDropDownListElementOpen())
				StringToWrite += " true";
			else
				StringToWrite += " false";
			StaticNodes.push_back(StringToWrite);
		}
	}

	
	std::cout << "MovingNodes" << std::endl;
	std::cout << elementToMove->getFullPath() << std::endl;
	std::cout << std::endl;

	std::cout << "DestinationNodes" << std::endl;
	std::cout << destinationElement->getFullPath() << std::endl;
	std::cout << std::endl;

	std::cout << "StaticPaths" << std::endl;
	for (std::string str : StaticNodes)
		std::cout << str << std::endl;
	std::cout << std::endl;

	std::cout << "MovingPaths" << std::endl;
	for (std::string str : MovingNodes)
		std::cout << str << std::endl;
	std::cout << std::endl;
	
	
	std::string Line;

	WriteMovingNodesInAlphabeticOrder(StaticNodes, MovingNodes, destinationElement);
	
	LoadElementsFromFile();
}

void DropDownListWidget::AddNewDropDownListElement(DropDownListElementWidget* parentElementToNewElement, std::string newname)
{
	// —оздаю новый элемент и добавл€ю его в конец вектора
	DropDownListElementWidget* F = new DropDownListElementWidget(this, DropDownListWindow, DropDownListDragAndDropWidget,
		DropDownListContextMenuWidget, newname, DropDownListElementsVector[0]->getFullPath() + newname + "/", DropDownListElementsVector.size());
	F->setIsDropDownListElementOpen(true);
	DropDownListElementsVector.push_back(F);

	// »спользую функцию дл€ перемещени€ созданного элемента
	ReplaceDropDownListElement(F, parentElementToNewElement);
}

void DropDownListWidget::RenameDropDownListElement(DropDownListElementWidget* elementToRename, std::string newname)
{
	std::vector<std::string> StaticNodes;
	std::vector<std::string> MovingNodes;
	DropDownListElementWidget* ParentElement = DropDownListElementsVector[0];
	bool WasParentElementFound = false;

	for (DropDownListElementWidget* element : DropDownListElementsVector)
	{
		std::string StringToWrite;
			
		if (element->getFullPath().find(elementToRename->getFullPath()) != -1)
		{
			if (element == elementToRename)
			{
				StringToWrite =  element->getFullPath().replace(element->getFullPath().find(element->getName()),
					element->getName().size(), newname) + " " + newname + " ";
				WasParentElementFound = true;
			}
			else
			{
				StringToWrite = element->getFullPath().replace(element->getFullPath().find(elementToRename->getName()),
					elementToRename->getName().size(), newname) + " " + element->getName() + " ";
			}

			if (element->getIsDropDownListElementOpen())
				StringToWrite += "true";
			else
				StringToWrite += "false";

			MovingNodes.push_back(StringToWrite);
		}
	else
		{
			StringToWrite = element->getFullPath() + " " + element->getName() + " ";
			if (element->getIsDropDownListElementOpen())
				StringToWrite += "true";
			else
				StringToWrite += "false";

			StaticNodes.push_back(StringToWrite);
		}
	if(WasParentElementFound == false)
		ParentElement = element;
	}

	WriteMovingNodesInAlphabeticOrder(StaticNodes, MovingNodes, ParentElement);

	LoadElementsFromFile();
}

void DropDownListWidget::DeleteDropDownListElement(DropDownListElementWidget* elementToDelete)
{
	std::ofstream NodesTXTOut;
	NodesTXTOut.open("Nodes.txt");

	if (NodesTXTOut.is_open())
	{
		for (DropDownListElementWidget* element : DropDownListElementsVector)
		{
			//std::cout << element->getFullPath().find(elementToRename->getFullPath()) << std::endl;
			if (element->getFullPath().find(elementToDelete->getFullPath()) == -1)
			{
				NodesTXTOut << element->getFullPath() << " " << element->getName() << " ";
				if (element->getIsDropDownListElementOpen())
					NodesTXTOut << "true" << std::endl;
				else
					NodesTXTOut << "false" << std::endl;
			}
		}
	}

	NodesTXTOut.close();

	LoadElementsFromFile();
}

void DropDownListWidget::WriteMovingNodesInAlphabeticOrder(std::vector<std::string> staticNodes, std::vector<std::string> movingNodes,
	DropDownListElementWidget* destinationElement)
{
	std::ofstream NodesTXTOut;
	NodesTXTOut.open("Nodes.txt");

	if (NodesTXTOut.is_open())
	{
		bool ShouldWriteMovingNodes = false;
		bool WasWriteMovingNodes = false;
		for (std::string stringToWriteIntoFile : staticNodes)
		{
			if (ShouldWriteMovingNodes)
			{
				//std::cout << stringToWriteIntoFile.substr(0, stringToWriteIntoFile.find(" ")) << " " <<
				//	destinationElement->getFullPath() << std::endl;

				if (stringToWriteIntoFile.substr(0, stringToWriteIntoFile.find(" ")) > movingNodes[0] || stringToWriteIntoFile.find(destinationElement->getFullPath()) == -1)
				{
					for (std::string str : movingNodes)
						NodesTXTOut << str << std::endl;
					ShouldWriteMovingNodes = false;
					WasWriteMovingNodes = true;
				}
			}

			if (stringToWriteIntoFile.substr(0, stringToWriteIntoFile.find(" ")) == destinationElement->getFullPath())
			{
				NodesTXTOut << stringToWriteIntoFile << std::endl;
				ShouldWriteMovingNodes = true;
			}

			else
			{
				NodesTXTOut << stringToWriteIntoFile << std::endl;
			}
		}
		if (WasWriteMovingNodes == false)
			for (std::string str : movingNodes)
				NodesTXTOut << str << std::endl;
	}

	NodesTXTOut.close();
}

DropDownListWidget::~DropDownListWidget()
{
	delete DropDownListElementWidgetTexture;
	delete DropDownListElementWidgetSprite;

	for (DropDownListElementWidget* folder : DropDownListElementsVector)
	{
		delete folder;
	}
}