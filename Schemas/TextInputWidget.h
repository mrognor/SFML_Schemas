#pragma once

#include "SchemasClasses.h"

class TextInputWidget
{
private:
	/// ��������� �� ���� � ������� ��������� ��� ������
	sf::RenderWindow* TextInputWidgetWindow;

	/// �������� ������ �������. 
	/// �������� ��������� ��� �������� ������ �� ��������� ���� �����
	sf::RenderTexture TextInputWidgetTexture;

	/// ���� ���� ����� 
	sf::RectangleShape TextInputWidgetMainShape;

	// ������ ��� ������� ������� ���� �����
	sf::RectangleShape TextInputWidgetRightPaddingShape;

	/// ���� ������� 
	sf::RectangleShape TextInputWidgetCursorShape;

	/// �����
	sf::Font font;

	/// �������� ����� ���� ����� 
	sf::Text TextInputWidgetMainText;

	/// �������������� ����� ���� �����.
	/// �� �������������� �� ������, ������ ��� ����������
	/// ������� ������� � ��������. �������� ����� ��������� ������
	/// ������� � �������� ������ ������������ ���������� CursorPosition
	sf::Text TextInputWidgetCursorText;

	/// ����� ��������� � ���� ����� 
	sf::Text TextInputWidgetHintText;

	/// ���� ��������
	sf::RectangleShape TextInputWidgetSliderShape;

	/// ���� ����� ���������
	sf::RectangleShape TextInputWidgetHighlightShape;

	/// ������ ��� ����� ��������. ������ ��� � ��������
	sf::Sprite TextInputWidgetSprite;

	/// ���������� ��� ����������� ������ ����� ������ 
	bool IsTextInputStarted = false;

	/// ������� ������� ������ ������
	int CursorPosition = 0;

	/// ������� ������ ������ ���������
	int HighliteStartPosition = 0;

	/// ���������� ��� ����������� ������ �������������� ��������
	bool IsSliderDragStarted = false;

	/// ������� ������� �� ������
	float CursorClickPosition;

public:
	TextInputWidget(sf::RenderWindow* textInputWidgetWindow);

	void Tick();

	void InputHandler(sf::Event event);

	void SetPosition(sf::Vector2f Vec);

	void SetString(sf::String newstring);

	void SetHintString(sf::String hintString);

	sf::String GetString();

	~TextInputWidget();
};


