#pragma once

#include "SchemasClasses.h"
#include "MovingPoleNodeWidget.h"
#include "DropDownListWidget.h"
#include "MovingPoleNodeWidget.h"
#include "DragAndDropWidget.h"

class MovingPoleWidget
{
private:
	/// ���� ����
	sf::RenderWindow* MovingPoleWidgetWindow;

	/// ��������� �� DropDown ������
	DropDownListWidget* MovingPoleDropDownListWidget;

	DragAndDropWidget* MovingPoleDragAndDropWidget;

	std::vector<MovingPoleNodeWidget*> MovingPoleNodeVector;

	/// ���������� ��� ��������� ��������� ����
	sf::Vector2f LastMouseCoords;

	/// �������� ��� ��������� ���� ��������� ����
	sf::RenderTexture* MovingPoleWidgetTexture;

	/// ������ ��� ��������� ���� ��������� ����
	sf::Sprite* MovingPoleWidgetSprite;

	/// ���������� ��� �������� ������ ��������������
	bool IsDragStarted = false;

public:
	MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow, DropDownListWidget* movingPoleDropDownListWidget, DragAndDropWidget* movingPoleDragAndDropWidget);

	void Tick();

	void InputHandler(sf::Event event);

	sf::RenderTexture* GetMovingPoleWidgetTexture() { return MovingPoleWidgetTexture; }

	sf::Sprite* GetMovingPoleWidgetSprite() { return MovingPoleWidgetSprite; }

	~MovingPoleWidget();
};

