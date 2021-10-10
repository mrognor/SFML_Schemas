#pragma once

#include "SchemasClasses.h"
#include "DropDownList.h"

/// ����� ��� �������� DropDownList 
class DropDownListElement
{
private:
	/// ��������� �� ������������ ������(DropDownList)
	DropDownList* DropDownListParent;

	/// ��������� �� ���� ���������� � ������� ��������� ������(DropDownList)
	sf::RenderWindow* Window;

	/// ��������� �� RectangleShape, ���������� ������� ��������������� �������(DropDownListElement)
	sf::RectangleShape* MainDropDownListElementShape;

	/// ��������� �� Text, ���������� ������� ������� �������(DropDownListElement)
	sf::Text* MainDropDownListElementText;
	 
	/// ����� 
	sf::Font font;

	/// ������ ���� ������� ��������(DropDownListElement)
	std::string FullPath;

	/// ������ ��� ������� ��������(DropDownListElement)
	std::string Name;

	/// ���������� ��� ������������ ����. True - ���� ���� �� MainDropDownListElementShape, false � ��������� ������
	bool IsMouseOnShape;

	/// ������� ������� �������� � ������(DropDownList). ��������� y ���������� ��� ������� ������� 
	int NumberInDropDownList;

public:
	/// ������� ������ RectangleShape ��� ���� ������� �������. �������� ������� SetDropDownListElementPosition.
	/// SetDropDownListElementPosition ���������� ���� ������� � ����� � ���������� �������. ������� ��������������� 
	/// �� DropDownList.
	DropDownListElement(DropDownList* dropDownListParent, sf::RenderWindow* window, std::string name, std::string path, int numberInDropDownList);

	/// ������ ��� ������� ���� 
	void setFullPath(std::string path) { FullPath = path; }
	/// ������ ��� ������� ���� 
	std::string getFullPath() { return FullPath; }

	/// ������ ��� �����
	void setName(std::string name) { Name = name; }
	// ������ ��� �����
	std::string getName() { return Name; }

	/// ������ ������� ���������� ���� �������(DropDownListElement) � ����� � ������ �������
	/// ��� ����������� ������� ���� ���������� NumberInDropDownList
	/// ��� ���������� ��������������� �� DropDownList.
	void SetDropDownListElementPosition();

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