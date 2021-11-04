#pragma once

#include "SchemasClasses.h"
#include "DropDownListWidget.h"
#include "DragAndDropWidget.h"
#include "ContextMenuWidget.h"

/// ����� ��� �������� DropDownListWidget 
class DropDownListElementWidget
{
private:
	/// ��������� �� ������������ ������(DropDownListWidget)
	DropDownListWidget* DropDownListParent;

	/// ���������� ��� ������������ �������(DragAndDropWidget)
	DragAndDropWidget* DropDownListElementDragAndDropWidget;

	/// ��������� �� ���� ���������� � ������� ��������� ������(DropDownListWidget)
	sf::RenderWindow* DropDownListWindow;

	/// ��������� �� �������� ��� ������(DropDownList)
	sf::RenderTexture* DropDownListElementWidgetDropDownListWidgetTexture;

	/// ���������� ��� ������������ �������(ContextMenuWidget)
	ContextMenuWidget* DropDownListElementContextMenuWidget;

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
	DropDownListElementWidget(DropDownListWidget* dropDownListParent, sf::RenderWindow* window, 
		sf::RenderTexture* dropDownListElementWidgetDropDownListWidgetTexture, DragAndDropWidget * dropDownListElementDragAndDropWidget,
 ContextMenuWidget* dropDownListElementContextMenu,
		std::string name, std::string path, int numberInDropDownList);

	/// ������ ��� ������� ���� 
	void setFullPath(std::string path) { FullPath = path; }
	/// ������ ��� ������� ���� 
	std::string getFullPath() { return FullPath; }

	/// ������ ��� �����
	void setName(std::string name) { Name = name; }
	/// ������ ��� �����
	std::string getName() { return Name; }

	/// ������������� ������� ������� ������� � ������ DropDownListWidget
	void setNumberInDropDownList(int numberInList) { NumberInDropDownList = numberInList; }
	/// �������� ������� ������� ������� � ������ DropDownListWidget
	int getNumberInDropDownList() { return NumberInDropDownList; }

	/// ������ ��� ���������� ��� ��������� �������(DropDownListElementWidget)
	void setIsRendering(bool f);
	/// ������ ��� ���������� ��� ��������� �������(DropDownListElementWidget)
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

	/// ���������� ����� 
	void InputHandler(sf::Event event);

	/// �������� ���������
	bool operator== (const DropDownListElementWidget& Obj);
	/// �������� ��������� 
	bool operator!= (const DropDownListElementWidget& Obj);
	/// ����������. ����������� ������ �� �� MainDropDownListElementShape � MainDropDownListElementText
	~DropDownListElementWidget();
};