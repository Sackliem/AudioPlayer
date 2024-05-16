#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "TextureRendering.hpp"
#include <string>
#include <iostream>
#include "Tools.hpp"
#include "Handler.hpp"
#include "FormLoad.h"



int StartAudio() {
	
	sf::Mouse mouse;
	sf::Vector2i posm;

	//Directory of music
	std::vector<std::string> names;
	std::wstring Dir;
	formLoad(Dir);
	if (Dir.size() == 0) Dir = L"music";
	if (DirOpen(names, Dir) == -1) {
		return -1;
	}

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(Width, Height, 32), "AudioPlayer",
							sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	//Text(musics name)
	sf::Font font; 
	font.loadFromFile("DolomanPavljenko.otf");
	sf::Text text("", font, 20);
	text.setOutlineColor(sf::Color::Red);
	text.setPosition(5, 5);

	//load soundbuffer
	sf::SoundBuffer buffer;
	sf::Sound sound(buffer);
	loadSoundBuffer(buffer, sound, names, text);

	//Texture loading
	TextureRend SpLoad[16];
	SprLoad(SpLoad);

	//main cycle
	windowEvents(buffer, sound, names, text, window, SpLoad, posm, mouse);

	return EXIT_SUCCESS;
}


int main()
{	
	int Success = 0;
	Success = StartAudio();
	if (Success == -1) std::cout << "Audio Loading problem" << std::endl;

}

//добавь визуализацию частотной спектра во время воспроизведения аудио