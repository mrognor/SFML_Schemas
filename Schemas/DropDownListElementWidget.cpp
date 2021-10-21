#include "DropDownListElementWidget.h"

DropDownListElementWidget::DropDownListElementWidget(DropDownListWidget* dropDownListParent, sf::RenderWindow* window, DragAndDropWidget* dropDownListElementWindowDragAndDropWidget, std::string name, std::string path, int numberInDropDownList)
	: DropDownListParent(dropDownListParent), ListElementWindow(window), DropDownListElementWindowDragAndDropWidget(dropDownListElementWindowDragAndDropWidget),Name(name), FullPath(path),  NumberInDropDownList(numberInDropDownList)
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
		ListElementWindow->draw(*MainDropDownListElementShape);
		ListElementWindow->draw(*MainDropDownListElementText);
		ListElementWindow->draw(*DropDownListElementOpenClosedConditionTriangle);
	}
}

void DropDownListElementWidget::InputHandler(sf::Event event)
{
	if (IsRendering)
	{
		/// Локальная переменная для отслеживания позиции курсора в окне
		sf::Vector2f CurrentMouseCoords = FindMouseCoords(ListElementWindow);

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
				// Тут делается сравнение координат. Так как при нажатии начинается операция Drag and drop 
				// в классе DragAndDroр. Операция началась, но перетаскивания не было. Поэтому нам надо сравнивать координаты
				if (IsMouseOnShape && DropDownListElementWindowDragAndDropWidget->getDragStartCoords() == CurrentMouseCoords)
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
				// Отработка отпускания клавиши на нашем элементе
				if (IsMouseOnShape && DropDownListElementWindowDragAndDropWidget->getIsDragAndDropInProcess()
					&& DropDownListElementWindowDragAndDropWidget->getCurrentDropDownListElement() != this)
				{
					DropDownListParent->ReplaceDropDownListElement(
						DropDownListElementWindowDragAndDropWidget->getCurrentDropDownListElement(),
						this);
				} 
			}
		}

		if (event.type == event.MouseButtonPressed && IsMouseOnShape && event.mouseButton.button == sf::Mouse::Left)
		{
			DropDownListElementWindowDragAndDropWidget->StartDragAndDropOperation(this);
		}

	}
}

DropDownListElementWidget::~DropDownListElementWidget()
{
	delete MainDropDownListElementShape;
	delete MainDropDownListElementText;
	delete DropDownListElementOpenClosedConditionTriangle;
}