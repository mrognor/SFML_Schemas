#pragma once

#include "SchemasClasses.h"
#include "DropDownListWidget.h"
#include "DragAndDropWidget.h"

/// ����� ��� �������� DropDownListWidget 
class DropDownListElementWidget
{
private:
	/// ��������� �� ������������ ������(DropDownListWidget)
	DropDownListWidget* DropDownListParent;

	/// ���������� ��� ������������ �������(DragAndDropWidget)
	DragAndDropWidget* DropDownListElementWindowDragAndDropWidget;

	/// ��������� �� ���� ���������� � ������� ��������� ������(DropDownListWidget)
	sf::RenderWindow* ListElementWindow;

	/// ��������� �� RectangleShape, ���������� ������� ��������������� �������(DropDownListElementWidget)
	sf::RectangleShape* MainDropDownListElementShape;

	/// ��������� �� CircleShape, ���������� ����������� ������������� ��������� 
	// ���������� �����
	sf::CircleShape* DropDownListElementOpenClosedConditionTriangle;

	/// ����� 
	sf::Font font;

	/// ��������� �� Text, ���������� ������� ������� �������(DropDownListElementWidget)
	sf::Text* MainDropDownListElementText;

	/// ������ ���� ������� ��������(DropDownListElementWidget)
	std::string FullPath;

	/// ������ ��� ������� ��������(DropDownListElementWidget)
	std::string Name;

	/// ���������� ��� ������������ ����. True - ���� ���� �� MainDropDownListElementShape, false � ��������� ������
	bool IsMouseOnShape;

	/// ������� ������� �������� � ������(DropDownListWidget). ��������� y ���������� ��� ������� ������� 
	int NumberInDropDownList;
	
	/// ������ ���������� ������ ��� ����������� ��������� �����.
	/// False - ������ ������ �� ������ �������������� �� ���� 
	/// True - ������ ������ �� ������ �������������� �� ����
	bool IsRendering = true;

	/// ������ ���������� ������ ��� ����������� ��������� �����. 
	/// False - ��� ���� �� ������ ��������������(IsRendering = false)
	/// True - ��� ���� ������ ��������������(IsRendering = true)
	bool IsDropDownListElementOpen = true;

public:
	/// ������� ������ RectangleShape ��� ���� ������� �������. �������� ������� UpdateDropDownListElementPosition.
	/// UpdateDropDownListElementPosition ���������� ���� ������� � ����� � ���������� �������. ������� ��������������� 
	/// �� DropDownListWidget.
	DropDownListElementWidget(DropDownListWidget* dropDownListParent, sf::RenderWindow* window, DragAndDropWidget* dropDownListElementWindowDragAndDropWidget,
		std::string name, std::string path, int numberInDropDownList);

	/// ������ ��� ������� ���� 
	void setFullPath(std::string path) { FullPath = path; }
	/// ������ ��� ������� ���� 
	std::string getFullPath() { return FullPath; }

	/// ������ ��� �����
	void setName(std::string name) { Name = name; }
	// ������ ��� �����
	std::string getName() { return Name; }

	/// ������������� ������� ������� ������� � ������ DropDownListWidget
	void setNumberInDropDownList(int numberInList) { NumberInDropDownList = numberInList; }
	/// �������� ������� ������� ������� � ������ DropDownListWidget
	int getNumberInDropDownList() { return NumberInDropDownList; }

	/// ������ ��� ���������� ��� ��������� �������(DropDownListElementWidget)
	void setIsRendering(bool f) { IsRendering = f; }
	// ������ ��� ���������� ��� ��������� �������(DropDownListElementWidget)
	bool getIsRendering() { return IsRendering; }

	/// ������ ��� ���������� ��� �������� ����� 
	void setIsDropDownListElementOpen(bool f);
	// ������ ��� ���������� ��� �������� �����
	bool getIsDropDownListElementOpen() { return IsDropDownListElementOpen; }

	/// ������ ������� ���������� ���� �������(DropDownListElementWidget) � ����� � ������ �������
	/// ��� ����������� ������� ���� ���������� NumberInDropDownList
	/// ��� ���������� ��������������� �� DropDownListWidget.
	void UpdateDropDownListElementPosition();

	/// �������, ���������� ������ ���� 
	void Tick();

	// ���������� ����� 
	void InputHandler(sf::Event event);

	/// �������� ���������
	bool operator== (const DropDownListElementWidget& Obj);
	/// �������� ��������� 
	bool operator!= (const DropDownListElementWidget& Obj);
	/// ����������. ����������� ������ �� �� MainDropDownListElementShape � MainDropDownListElementText
	~DropDownListElementWidget();
};