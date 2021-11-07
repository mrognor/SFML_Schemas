#pragma once

#include "SchemasClasses.h"
#include "MovingPoleNodeWidget.h"
#include "DropDownListWidget.h"

class MovingPoleWidget
{
private:
	/// ���� ����
	sf::RenderWindow* MovingPoleWidgetWindow;

	DropDownListWidget* MovingPoleDropDownListWidget;

	sf::RectangleShape ShapeToTest;
	
	/// ���������� ��� ��������� ��������� ����
	sf::Vector2f LastMouseCoords;

	/// �������� ��� ��������� ���� ��������� ����
	sf::RenderTexture* MovingPoleWidgetTexture;

	/// ������ ��� ��������� ���� ��������� ����
	sf::Sprite* MovingPoleWidgetSprite;

	/// ���������� ��� �������� ������ ��������������
	bool IsDragStarted = false;

public:
	MovingPoleWidget(sf::RenderWindow* movingPoleWidgetWindow, DropDownListWidget* movingPoleDropDownListWidget);

	void Tick();

	void InputHandler(sf::Event event);

	~MovingPoleWidget();
};

