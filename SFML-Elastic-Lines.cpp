//============================================================================
// Name        : SFML-Elastic-Lines.cpp
// Author      : Carl Norwood
// Version     :
// Copyright   : WLGfx 2022
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "Elastic.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1024, 768), "WLGfx Elastic Lines");

	Elastic elastic(&window);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		elastic.update();
		elastic.draw();

		window.display();

		usleep(1000);
	}

	return 0;
}
