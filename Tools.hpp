#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "FileGetNames.h"
#include "FormLoad.h"
#include <iostream>

const int Width = 432;
const int Height = 400;

int isPlaying = 0, isloop = 0, soncon = 0;
float volume = 100, speed = 1, shift = 2; int volumeshift = 105;
int isStop = 0, isPlay = 0, isLeftBtn = 0, isRightBtn = 0, isPause = 0, isMinusBtn = 0, isPlus = 0, dY, isMove = 0;
int Dur = 0, current_soundPos = 0;

int DirOpen(std::vector<std::string>& names, std::wstring Dir) {
	getfilename(names, Dir);
	if (names.size() == 0) {
		//std::cout << "No music in direcotry with extention .wav" << std::endl;
		errorForm("No music in direcotry\nwith extention .wav\nor the path does not exist");
		return -1;
	}
	return 1;
}

void loadSoundBuffer(sf::SoundBuffer& buffer, sf::Sound& sound, std::vector<std::string>& names, sf::Text& text) {
	while (true) {
		if (!buffer.loadFromFile(names[soncon])) {
			std::cout << "load problem " << names[soncon] << std::endl;
			auto iter = names.cbegin();
			names.erase(iter + soncon);
			soncon++;
			text.setString("Played Music: " + names[soncon].substr(6) + "\n Duration: " +
				std::to_string((int)buffer.getDuration().asSeconds()) + " seconds");
		}
		else
			break;
	}
	Dur = buffer.getDuration().asMilliseconds();
	text.setString("Played Music: " + names[soncon].substr(6) + "\n Duration: " +
		std::to_string((int)buffer.getDuration().asSeconds()) + " seconds");
}
