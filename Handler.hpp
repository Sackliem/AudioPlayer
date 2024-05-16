#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "TextureRendering.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Tools.hpp"


void windowEvents(sf::SoundBuffer& buffer, sf::Sound& sound, std::vector<std::string>& names, 
				sf::Text& text, sf::RenderWindow& window, TextureRend SpLoad[16], sf::Vector2i posm, sf::Mouse mouse)
{
	while (window.isOpen())
	{
		posm = mouse.getPosition(window); //get mouse position
		//volume position
		volume = sound.getVolume();
		//sound position
		current_soundPos = sound.getPlayingOffset().asMilliseconds();
		SpLoad[12].pos.x = (current_soundPos * 400) / Dur + 16;
		SpLoad[12].sprite.setPosition(SpLoad[12].pos);


		//Discrete Fourier transform
		int tm = sound.getPlayingOffset().asSeconds();
		int tsr = buffer.getDuration().asSeconds();
		const sf::Int16* samples = buffer.getSamples();
		std::size_t count = buffer.getSampleCount();
		std::vector<sf::RectangleShape> drawblock;
		float vol = sound.getVolume();
		int j = 0;
		if (isPlaying) {
			for (int i = tm * (count - 100000) / tsr; i < (tm + 1) * ((count - 100000) / tsr); i += 200) {
				//drawblock.push_back(sf::RectangleShape(sf::Vector2f(2.f, static_cast<float>(samples[i]) * (vol / 30) / 1000)));
				drawblock.push_back(sf::RectangleShape(sf::Vector2f(2.f, static_cast<float>(samples[i]) / 600)));
				//drawblock.push_back(sf::RectangleShape(sf::Vector2f(2.f, static_cast<float>(std::abs(samples[i]))/1000*( -1))));
				drawblock[j].setPosition(static_cast<float>(j + 4), 300.f);
				j++;
			}
		}


		int tet = 10;

		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			//play and pause
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (!isPlaying)
					sound.play();
				else
					sound.pause();
				isPlaying = !isPlaying;
				sf::sleep(sf::seconds(0.5));
			}
			if (SpLoad[2].sprite.getGlobalBounds().contains(posm.x, posm.y)) {
				if (isPlaying == 0) isPlay = 1;
				if (isPlaying == 1) isPause = 1;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (!isPlaying)
						sound.play();
					else
						sound.pause();
					isPlaying = !isPlaying;
				}
			}
			else {
				if (isPlaying == 0) isPlay = 0;
				if (isPlaying == 1) isPause = 0;
			}

			//next track
			if (SpLoad[1].sprite.getGlobalBounds().contains(posm.x, posm.y)) {
				isRightBtn = 1;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (soncon == names.size() - 1) soncon = 0;
					else soncon++;
					sound.stop();
					loadSoundBuffer(buffer, sound, names, text);
					sound.play();
					isPlaying = 1;
					isPlay = 1;
				}
			}
			else isRightBtn = 0;

			////previos track
			if (SpLoad[0].sprite.getGlobalBounds().contains(posm.x, posm.y)) {
				isLeftBtn = 1;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					soncon--;
					if (soncon == -1) soncon = names.size() - 1;
					sound.stop();
					loadSoundBuffer(buffer, sound, names, text);
					sound.play();
					isPlaying = 1;
					isPlay = 1;
				}
			}
			else isLeftBtn = 0;

			////stop
			if (SpLoad[4].sprite.getGlobalBounds().contains(posm.x, posm.y)) {
				isStop = 1;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					isStop = 0;
					sound.stop();
					isPlaying = 0;
				}
			}
			else isStop = 0;
			//loop
			if (SpLoad[3].sprite.getGlobalBounds().contains(posm.x, posm.y)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					isloop = !isloop;
					sound.setLoop(isloop);
				}
			}

			//sound shift
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				current_soundPos += 2000;
				sound.setPlayingOffset(sf::milliseconds(current_soundPos));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				current_soundPos -= 2000;
				sound.setPlayingOffset(sf::milliseconds(current_soundPos));
			}

			//volume Change
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					if (SpLoad[13].sprite.getGlobalBounds().contains(posm.x, posm.y)) {
						dY = posm.y - SpLoad[13].sprite.getPosition().y;
						isMove = 1;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.key.code == sf::Mouse::Left) {
					isMove = 0;
				}
			}
			if (isMove) {
				if (posm.y > 4 && posm.y < 105) {
					SpLoad[13].sprite.setPosition(408, posm.y - dY);
					volume = -SpLoad[13].sprite.getPosition().y + volumeshift;
					sound.setVolume(volume);
				}
			}
		}

		//chek sound status
		if (sound.getStatus() == sf::SoundSource::Status::Stopped) {
			isPlaying = 0;
			isPlay = 0;
		}

		// Display things on screen
		Rend(window, SpLoad, text, drawblock);
	}
}