// Schemas.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>

#include "SchemasFunctions.h"
#include "DropDownListWidget.h"
#include "DropDownListElementWidget.h"
#include "DragAndDropWidget.h"
#include "ContextMenuWidget.h"
#include "MovingPoleWidget.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Works!");
	window.setFramerateLimit(60);

	DragAndDropWidget d(&window);
	ContextMenuWidget c(&window);
	
	DropDownListWidget f(&window, &d, &c, 400, 8000);

	MovingPoleWidget m(&window, &f, &d);

	d.setWindowDropDownList(&f);
	c.SetContextMenuWidgetDropDownList(&f);

	// create own view
	sf::View view = window.getDefaultView();

	while (window.isOpen())
	{
		window.clear(sf::Color(128, 128, 128));
		sf::Event event;

		while (window.pollEvent(event))
		{	
			m.InputHandler(event);
			c.InputHandler(event);
			f.InputHandler(event);
			d.InputHandler(event);

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				// resize my view
				view.setSize(sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
				view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
				window.setView(view);
			}

		}

		m.Tick();
		f.Tick();
		c.Tick();
		d.Tick();
		window.display();
	}


	return 0;
}


