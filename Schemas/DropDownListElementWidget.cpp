#include "DropDownListElementWidget.h"

DropDownListElementWidget::DropDownListElementWidget(DropDownListWidget* dropDownListParent,
	sf::RenderWindow* window, sf::RenderTexture* dropDownListElementWidgetDropDownListWidgetTexture,
	DragAndDropWidget * dropDownListElementDragAndDropWidget,
	ContextMenuWidget* dropDownListElementContextMenu, std::string name,
 std::string path, 
	int numberInDropDownList)
	: DropDownListParent(dropDownListParent), DropDownListWindow(window), 
	DropDownListElementWidgetDropDownListWidgetTexture(dropDownListElementWidgetDropDownListWidgetTexture),
	DropDownListElementDragAndDropWidget(dropDownListElementDragAndDropWidget),
	DropDownListElementContextMenuWidget(dropDownListElementContextMenu), Name(name),
	FullPath(path),  NumberInDropDownList(numberInDropDownList)
{
	font.loadFromFile("Font.ttf");

	MainDropDownListElementShape = new sf::RectangleShape();
	MainDropDownListElementShape->setSize(sf::Vector2f(8000, 40));

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

void DropDownListElementWidget::Tick()
{
	if (IsRendering)
	{
		DropDownListElementWidgetDropDownListWidgetTexture->draw(*MainDropDownListElementShape);
		DropDownListElementWidgetDropDownListWidgetTexture->draw(*MainDropDownListElementText);

		if (IsFolder)
			DropDownListElementWidgetDropDownListWidgetTexture->draw(*DropDownListElementOpenClosedConditionTriangle);
	}
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

void DropDownListElementWidget::InputHandler(sf::Event event)
{
	if (IsRendering)
	{
		/// Локальная переменная для отслеживания позиции курсора в окне
		sf::Vector2f CurrentMouseCoords = FindMouseCoords(DropDownListWindow);

		// OnHovered
		
		if (IsShapeInSpriteContain(*DropDownListParent->GetSprite(), *MainDropDownListElementShape, CurrentMouseCoords) &&
			DropDownListElementContextMenuWidget->getIsMouseOnShape() == false && 
			CurrentMouseCoords.x < DropDownListElementWidgetDropDownListWidgetTexture->getSize().x - 10) // 10 тут - ширина paddingshape в DropDownList 
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
				if (IsMouseOnShape && DropDownListElementDragAndDropWidget->getDragStartCoords() == CurrentMouseCoords)
				{
					if (IsFolder)
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
				}
				// Отработка отпускания клавиши на нашем элементе
				if (IsMouseOnShape && DropDownListElementDragAndDropWidget->getIsDragAndDropInProcess()
					&& DropDownListElementDragAndDropWidget->getCurrentDropDownListElement() != this && IsFolder)
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
					DropDownListElementContextMenuWidget->OpenContextMenu(this);
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