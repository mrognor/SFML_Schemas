#include "DropDownListElementWidget.h"

DropDownListElementWidget::DropDownListElementWidget(DropDownListWidget* dropDownListParent,
	sf::RenderWindow* window, DragAndDropWidget * dropDownListElementDragAndDropWidget, 
	ContextMenuWidget* dropDownListElementContextMenu, std::string name,
 std::string path, 
	int numberInDropDownList)
	: DropDownListParent(dropDownListParent), DropDownListElementWindow(window), 
	DropDownListElementDragAndDropWidget(dropDownListElementDragAndDropWidget),
	DropDownListElementContextMenuWidget(dropDownListElementContextMenu), Name(name),
	FullPath(path),  NumberInDropDownList(numberInDropDownList)
{
	font.loadFromFile("Font.ttf");

	MainDropDownListElementShape = new sf::RectangleShape();
	MainDropDownListElementShape->setSize(sf::Vector2f(380 - 20 * CountInStr(FullPath, "/"), 40));
	
	MainDropDownListElementText = new sf::Text;
	MainDropDownListElementText->setFont(font);
	MainDropDownListElementText->setString(sf::String(Name));
	MainDropDownListElementText->setFillColor(sf::Color::Black);

	DropDownListElementOpenClosedConditionTriangle = new sf::CircleShape(10.f, 3);
	DropDownListElementOpenClosedConditionTriangle->setFillColor(sf::Color::Blue);
	DropDownListElementOpenClosedConditionTriangle->setRotation(180);

	UpdateDropDownListElementPosition();
}

void DropDownListElementWidget::setIsDropDownListElementOpen(bool f)
{
	IsDropDownListElementOpen = f; 
	if (f)
		DropDownListElementOpenClosedConditionTriangle->setRotation(180);
	else
		DropDownListElementOpenClosedConditionTriangle->setRotation(90);
}

void DropDownListElementWidget::UpdateDropDownListElementPosition()
{
	MainDropDownListElementShape->setPosition(10 + 20 * CountInStr(FullPath, "/"), 10 + NumberInDropDownList * 50);

	MainDropDownListElementText->setPosition(15 + 20 * CountInStr(FullPath, "/"), 15 + NumberInDropDownList * 50);

	DropDownListElementOpenClosedConditionTriangle->setPosition(10 + 20 * CountInStr(FullPath, "/"), 40 + NumberInDropDownList * 50);
}

bool DropDownListElementWidget::operator==(const DropDownListElementWidget& Obj)
{
	if (FullPath == Obj.FullPath && Name == Obj.Name)
		return true;
	return false;
}

bool DropDownListElementWidget::operator!=(const DropDownListElementWidget& Obj)
{
	if (FullPath == Obj.FullPath && Name == Obj.Name)
		return false;
	return true;
}

void DropDownListElementWidget::Tick()
{
	if (IsRendering)
	{
		DropDownListElementWindow->draw(*MainDropDownListElementShape);
		DropDownListElementWindow->draw(*MainDropDownListElementText);
		DropDownListElementWindow->draw(*DropDownListElementOpenClosedConditionTriangle);
	}
}

void DropDownListElementWidget::InputHandler(sf::Event event)
{
	if (IsRendering)
	{
		/// ��������� ���������� ��� ������������ ������� ������� � ����
		sf::Vector2f CurrentMouseCoords = FindMouseCoords(DropDownListElementWindow);

		// OnHovered
		if (MainDropDownListElementShape->getGlobalBounds().contains(CurrentMouseCoords.x, CurrentMouseCoords.y) &&
			DropDownListElementContextMenuWidget->getIsMouseOnShape() == false)
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
				// ��� �������� ��������� ���������. ��� ��� ��� ������� ���������� �������� Drag and drop 
				// � ������ DragAndDro�. �������� ��������, �� �������������� �� ����. ������� ��� ���� ���������� ����������
				if (IsMouseOnShape && DropDownListElementDragAndDropWidget->getDragStartCoords() == CurrentMouseCoords)
				{
					if (IsDropDownListElementOpen)
					{
						IsDropDownListElementOpen = false;
						DropDownListParent->CloseDropDownListElement(this);
						DropDownListElementOpenClosedConditionTriangle->setRotation(90);
					}
					else
					{
						IsDropDownListElementOpen = true;
						DropDownListParent->OpenDropDownListElement(this);
						DropDownListElementOpenClosedConditionTriangle->setRotation(180);
					}
				}
				// ��������� ���������� ������� �� ����� ��������
				if (IsMouseOnShape && DropDownListElementDragAndDropWidget->getIsDragAndDropInProcess()
					&& DropDownListElementDragAndDropWidget->getCurrentDropDownListElement() != this)
				{
					DropDownListParent->ReplaceDropDownListElement(
						DropDownListElementDragAndDropWidget->getCurrentDropDownListElement(),
						this);
				} 
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (IsMouseOnShape)
				{
					DropDownListElementContextMenuWidget->OpenContextMenu();
				}
			}
		}

		if (event.type == event.MouseButtonPressed && IsMouseOnShape && event.mouseButton.button == sf::Mouse::Left)
		{
			DropDownListElementDragAndDropWidget->StartDragAndDropOperation(this);
		}

	}
}

DropDownListElementWidget::~DropDownListElementWidget()
{
	delete MainDropDownListElementShape;
	delete MainDropDownListElementText;
	delete DropDownListElementOpenClosedConditionTriangle;
}