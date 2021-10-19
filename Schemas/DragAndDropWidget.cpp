#include "DragAndDropWidget.h"


DragAndDropWidget::DragAndDropWidget(sf::RenderWindow* dragAndDropWidgetWindow)
{
	DragAndDropWidgetWindow = dragAndDropWidgetWindow;
	DragAndDropWidgetShape = new sf::RectangleShape;

	DragAndDropWidgetText = new sf::Text;
	font.loadFromFile("Font.ttf");
	DragAndDropWidgetText->setFont(font);
	DragAndDropWidgetText->setFillColor(sf::Color::Black);
}

void DragAndDropWidget::Tick()
{
	
	if (IsDragAndDropInProcess)
	{
		/// Локальная переменная для отслеживания позиции курсора в окне
		sf::Vector2f CurrentMouseCoords = FindMouseCoords(DragAndDropWidgetWindow);

		if (CurrentMouseCoords != DragStartCoords)
		{
			DragAndDropWidgetShape->setPosition(CurrentMouseCoords);
			DragAndDropWidgetText->setPosition(CurrentMouseCoords);
			DragAndDropWidgetWindow->draw(*DragAndDropWidgetShape);
			DragAndDropWidgetWindow->draw(*DragAndDropWidgetText);
		}
	}
}

void DragAndDropWidget::InputHandler(sf::Event event)
{
	if (event.type == event.MouseButtonReleased)
	{
		IsDragAndDropInProcess = false;
		CurrentDropDownListElement = nullptr;
	}
}

void DragAndDropWidget::StartDragAndDropOperation(DropDownListElement* currentDropDownListElement)
{
	IsDragAndDropInProcess = true;
	DragStartCoords = FindMouseCoords(DragAndDropWidgetWindow);
	CurrentDropDownListElement = currentDropDownListElement;
	DragAndDropWidgetText->setString(CurrentDropDownListElement->getName());
	DragAndDropWidgetShape->setSize(sf::Vector2f(DragAndDropWidgetText->getGlobalBounds().width + 5,
		DragAndDropWidgetText->getGlobalBounds().height * 2));
}

DragAndDropWidget::~DragAndDropWidget()
{
	delete DragAndDropWidgetShape;
	delete DragAndDropWidgetText;
}
