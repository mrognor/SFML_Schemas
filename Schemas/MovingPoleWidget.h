#pragma once

#include "SchemasClasses.h"
#include "MovingPoleNodeWidget.h"
#include "DropDownListWidget.h"
#include "MovingPoleNodeWidget.h"

class MovingPoleWidget
{
private:
	/// ���� ����
	sf::RenderWindow* MovingPoleWidgetWindow;

	/// ��������� �� DropDown ������
	DropDownListWidget* MovingPoleDropDownListWidget;
	
	MovingPoleNodeWidget* TestPoleWidget1;

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

