// Schemas.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>

#include "SchemasFunctions.h"
#include "DropDownListWidget.h"
#include "DropDownListElementWidget.h"
#include "DragAndDropWidget.h"
#include "ContextMenuWidget.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Works!");
	window.setFramerateLimit(60);

	DragAndDropWidget d(&window);
	ContextMenuWidget c(&window);
	DropDownListWidget f(&window, &d, &c, 400, 800);
	d.setWindowDropDownList(&f);

	while (window.isOpen())
	{
		window.clear(sf::Color(128, 128, 128));
		sf::Event event;

		while (window.pollEvent(event))
		{	
			c.InputHandler(event);
			f.InputHandler(event);
			d.InputHandler(event);

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered && event.text.unicode < 128)
			{
				std::cout << "Char:" << char(event.text.unicode) << " Code:" << event.text.unicode << std::endl;
			} 
		}

		f.Tick();
		c.Tick();
		d.Tick();
		window.display();
	}


	return 0;
}


