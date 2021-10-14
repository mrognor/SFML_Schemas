// Schemas.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>

#include "SchemasFunctions.h"
#include "DropDownList.h"
#include "DropDownListElement.h"
#include "DragAndDropWidget.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Works!");
	window.setFramerateLimit(60);

	DragAndDropWidget d(&window);
	DropDownList f(&window, &d, 400, 800);
	

	while (window.isOpen())
	{
		window.clear(sf::Color(128, 128, 128));
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			f.InputHandler(event);
			d.InputHandler(event);
		}

		f.Tick();
		d.Tick();
		window.display();
	}


	return 0;
}


