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
	}
}

void DragAndDropWidget::StartDragAndDropOperation(DropDownListElement* currentDropDownListElement,
	sf::Vector2f dragStartCoords)
{

	IsDragAndDropInProcess = true;
	DragStartCoords = dragStartCoords;
	CurrentDropDownListElement = currentDropDownListElement;
	DragAndDropWidgetText->setString(CurrentDropDownListElement->getName() + "DRAG");
	DragAndDropWidgetShape->setSize(sf::Vector2f(DragAndDropWidgetText->getGlobalBounds().width,
		DragAndDropWidgetText->getGlobalBounds().height));
}

DragAndDropWidget::~DragAndDropWidget()
{
	delete DragAndDropWidgetShape;
	delete DragAndDropWidgetText;
}
