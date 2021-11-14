// Данный файл содержит список всех классов проекта для компиляции проекта 
#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <fstream>
#include "SchemasFunctions.h"

class DropDownListWidget;
class DropDownListElementWidget;
class DragAndDropWidget;
class ContextMenuWidget;
class TextInputWidget;
class MovingPoleWidget;
class MovingPoleNodeWidget;
class MovingPoleConnectionWidget;

struct InputNode
{
	sf::CircleShape* Circle;
	bool Value;
	MovingPoleConnectionWidget* InputConnection = nullptr;
	MovingPoleNodeWidget* ParentNodeWidget;
};
struct OutputNode
{
	sf::CircleShape* Circle;
	bool Value;
	std::string Formula;
	MovingPoleConnectionWidget* OutputConnection = nullptr;
};

enum ConnectionTypes
{
	InputOutput,
	OutputInput
};