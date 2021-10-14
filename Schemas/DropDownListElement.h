#pragma once

#include "SchemasClasses.h"
#include "DropDownList.h"
#include "DragAndDropWidget.h"

/// ����� ��� �������� DropDownList 
class DropDownListElement
{
private:
	/// ��������� �� ������������ ������(DropDownList)
	DropDownList* DropDownListParent;

	/// ���������� ��� ������������ �������(DragAndDropWidget)
	DragAndDropWidget* DropDownListElementWindowDragAndDropWidget;

	/// ��������� �� ���� ���������� � ������� ��������� ������(DropDownList)
	sf::RenderWindow* ListElementWindow;

	/// ��������� �� RectangleShape, ���������� ������� ��������������� �������(DropDownListElement)
	sf::RectangleShape* MainDropDownListElementShape;

	/// ����� 
	sf::Font font;

	/// ��������� �� Text, ���������� ������� ������� �������(DropDownListElement)
	sf::Text* MainDropDownListElementText;

	/// ������ ���� ������� ��������(DropDownListElement)
	std::string FullPath;

	/// ������ ��� ������� ��������(DropDownListElement)
	std::string Name;

	/// ���������� ��� ������������ ����. True - ���� ���� �� MainDropDownListElementShape, false � ��������� ������
	bool IsMouseOnShape;

	/// ������� ������� �������� � ������(DropDownList). ��������� y ���������� ��� ������� ������� 
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
	/// �� DropDownList.
	DropDownListElement(DropDownList* dropDownListParent, sf::RenderWindow* window, DragAndDropWidget* dropDownListElementWindowDragAndDropWidget,
		std::string name, std::string path, int numberInDropDownList);

	/// ������ ��� ������� ���� 
	void setFullPath(std::string path) { FullPath = path; }
	/// ������ ��� ������� ���� 
	std::string getFullPath() { return FullPath; }

	/// ������ ��� �����
	void setName(std::string name) { Name = name; }
	// ������ ��� �����
	std::string getName() { return Name; }

	/// ������������� ������� ������� ������� � ������ DropDownList
	void setNumberInDropDownList(int numberInList) { NumberInDropDownList = numberInList; }
	/// �������� ������� ������� ������� � ������ DropDownList
	int getNumberInDropDownList() { return NumberInDropDownList; }

	/// ������ ��� ���������� ��� ��������� �������(DropDownListElement)
	void setIsRendering(bool f) { IsRendering = f; }
	// ������ ��� ���������� ��� ��������� �������(DropDownListElement)
	bool getIsRendering() { return IsRendering; }

	/// ������ ��� ���������� ��� �������� ����� 
	void setIsDropDownListElementOpen(bool f) { IsDropDownListElementOpen = f; }
	// ������ ��� ���������� ��� �������� �����
	bool getIsDropDownListElementOpen() { return IsDropDownListElementOpen; }

	/// ������ ������� ���������� ���� �������(DropDownListElement) � ����� � ������ �������
	/// ��� ����������� ������� ���� ���������� NumberInDropDownList
	/// ��� ���������� ��������������� �� DropDownList.
	void UpdateDropDownListElementPosition();

	/// �������, ���������� ������ ���� 
	void Tick();

	// ���������� ����� 
	void InputHandler(sf::Event event);

	/// �������� ���������
	bool operator== (const DropDownListElement& Obj);
	/// �������� ��������� 
	bool operator!= (const DropDownListElement& Obj);
	/// ����������. ����������� ������ �� �� MainDropDownListElementShape � MainDropDownListElementText
	~DropDownListElement();
};