#pragma once

#include "SchemasClasses.h"
#include "DropDownListElement.h"

class DropDownList
{
private:
	/// ��������� �� ������� ���� ���������� 
	sf::RenderWindow* Window;

	/// RectangleShape. �������������, �������� ������� ����� ������� ������
	sf::RectangleShape WidgetBody;

	/// ������ �� ���� ��������� �������(DropDownListElement)
	std::vector<DropDownListElement*> DropDownListElementsVector;

public:
	///
	DropDownList(sf::RenderWindow* mainWindow, int sizeX, int sizeY);

	/// ������� ��������� ����� ������������. �������� ����� ���� ��������� �������(DropDownListElement)
	void InputHandler(sf::Event event);

	/// 
	void Tick();

	/// ������� ��� �������� DropDownListElement
	void OpenDropDownListElement(DropDownListElement* elementToOpen);
	/// ������� ��� �������� DropDownListElement
	void CloseDropDownListElement(DropDownListElement* elementToClose);
	
	/// ������� ��� ���������� ������� ���������(DropDownElement)
	/// ������� ����� � ������������� �������� ������ ��������
	void FindAndSetDropDownListElementIndexes();

	~DropDownList();
};

