#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include "Form.hpp"
#include <string>

using namespace std;
using namespace form;
using namespace sf;


void errorForm(const char* str) {
	RenderWindow window(sf::VideoMode(400, 100), "Error");

	Label label(5, 5, str);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(41, 47, 54));
		window.draw(label.displayText());
		window.display();
	}
}

void formLoad(std::wstring& widestr) {
	RenderWindow window(sf::VideoMode(400, 80), "Form");

	Button button2(5, 40, 390, 30, "Select Directory");
	Input input(5, 5, 390, 30);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Vector2i mouse = Mouse::getPosition(window);

					if (button2.select(mouse)) { 
						if (input.text.length() != 0) {
							String str = input.readText();
							widestr = std::wstring(str.begin(), str.end());
							window.close();
						}
						else
						{
							errorForm("Need to input the dir name");
						}
					}

					input.select(mouse);

				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (input.text.length() != 0) {
					String str = input.readText();
					widestr = std::wstring(str.begin(), str.end());
					window.close();
				}
				else
				{
					errorForm("Need to input the dir name");
				}
			}
			if (event.type == sf::Event::TextEntered) {
				if (input.select()) {
					input.reText(event.text.unicode);
				}
			}

		}

		window.clear(sf::Color(41, 47, 54));

		window.draw(button2.displayButton());
		window.draw(button2.displayText());
		window.draw(input.displayButton());
		window.draw(input.displayText());
		window.display();
		sleep(milliseconds(1000 / 60));
	}
}




