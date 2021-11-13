// ������ ���� �������� ������ ���� ������� ������� ��� ���������� ������� 
#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <fstream>
#include "SchemasFunctions.h"

struct InputNode
{
	sf::CircleShape* Circle;
	bool Value;
};
struct OutputNode
{
	sf::CircleShape* Circle;
	std::string Formula;
};

class DropDownListWidget;
class DropDownListElementWidget;
class DragAndDropWidget;
class ContextMenuWidget;
class TextInputWidget;
class MovingPoleWidget;
class MovingPoleNodeWidget;
class MovingPoleConnectionWidget;