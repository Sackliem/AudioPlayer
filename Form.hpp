#pragma once

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace form {
	Font None;				

	class Label {
	public:
		string text;	
	protected:
		double x;		
		double y;		

		Text TXT;		

	public:
		Label(double _x = 0, double _y = 0, string _text = "Текст")
		{
			None.loadFromFile("DolomanPavljenko.otf");			

			x = _x;
			y = _y;
			text = _text;								
			TXT.setFont(None);							
			TXT.setCharacterSize(20); 					
			TXT.setOutlineColor(Color::White);
			TXT.setPosition(x, y);						
		}
		Text displayText()
		{
			TXT.setString(text);						
			return TXT;
		}
	};

	class Button : public Label {
	protected:
		double width;		
		double height;		
		RectangleShape BOX;	
	public:
		Button(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "Кнопка")
		{
			None.loadFromFile("DolomanPavljenko.otf");			

			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;								
			TXT.setFont(None);							
			TXT.setCharacterSize(20); 					
			TXT.setOutlineColor(Color::White);
			TXT.setPosition(x, y);						

			BOX.setSize(Vector2f(width, height));		
			BOX.setPosition(x, y);						
			BOX.setFillColor(sf::Color(133, 133, 133));	
			BOX.setOutlineThickness(2);					
			BOX.setOutlineColor(Color(66, 66, 66));		
		}
		//Button checked selection
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {
				return  true;
			}
			else {
				return false;
			}
		}
		//Text output
		Text displayText()
		{
			TXT.setString(text); 
			return TXT;
		}
		
		RectangleShape displayButton()
		{
			return BOX;
		}


	};

	class Input : public Button {
	protected:
		bool focus;
	public:
		Input(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "")
		{
			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;								
			focus = false;								

			TXT.setFont(None);							
			TXT.setCharacterSize(20); 					
			TXT.setOutlineColor(Color::Black);
			TXT.setPosition(x, y);						

			BOX.setSize(Vector2f(width, height));		
			BOX.setPosition(x, y);						
			BOX.setOutlineColor(Color::White);
		}
		
		void reText(char _tmp)
		{
			text.erase(text.size() - 1);

			if (_tmp != 8) {
				text += _tmp;
			}
			else {
				if (text.size() > 0) {
					text.erase(text.size() - 1);
				}

			}
			text += "|";
			TXT.setString(text);
		}

		// Focus checked Input
		bool select()
		{
			return focus;
		}

		// INstall focus Input
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) { 	
				focus = true;																	
				text += "|";																	
			}
			else {																				
				if (text.size() > 0) {															
					if (text[text.size() - 1] == 124) {											
						text.erase(text.size() - 1);											
					}
				}
				focus = false;																	
			}
			return focus;
		}

		//Output Text
		Text displayText()
		{
			TXT.setString(text);						
			return TXT;
		}

		//background Input
		RectangleShape displayBOX()
		{
			return BOX;
		}

		
		string readText()
		{
			if (text[text.size() - 1] == 124) { 	
				text.erase(text.size() - 1);
			}
			return text;
		}
	};

}
