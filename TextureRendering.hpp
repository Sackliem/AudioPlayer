#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include"Tools.hpp"

class TextureRend
{
private:



public:
	TextureRend(){}
	TextureRend(const TextureRend& obj){}
	~TextureRend() {}
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos;


	void Load(std::string Name, int x, int y) {
		texture.loadFromFile(Name);
		sprite.setTexture(texture);
		pos.x = x; pos.y = y;
		sprite.setPosition(pos);
	}
};

void SprLoad(TextureRend mass[16]) {
	std::string names[15] = { "resources\\btnleft.png","resources\\btnright.png","resources\\pausebtn.png",
							"resources\\reply.png", "resources\\stopbtn.png", "resources\\pausebtneff.png",
							"resources\\playbtn.png", "resources\\playbtneff.png", "resources\\stopbtneff.png",
							"resources\\replyeff.png","resources\\lineSound.png", "resources\\VolumeLine.png", 
							"resources\\sols.png", "resources\\btnlefteff.png", "resources\\btnrighteff.png" };
	mass[0].Load(names[0], 120, 130);//btnleft
	mass[1].Load(names[1], 240, 130);//btnright
	mass[2].Load(names[2], 180, 130);//pausebtn
	mass[3].Load(names[3], 380, 134);//reply
	mass[4].Load(names[4], 50, 130); //stopbtn
	mass[5].Load(names[5], 180, 130);//pausebtneff
	mass[6].Load(names[6], 180, 130);//playbtn
	mass[7].Load(names[7], 180, 130);//playbtneff
	mass[8].Load(names[8], 50, 130); //stopbtneff
	mass[9].Load(names[9], 380, 134);//replyeff
	mass[10].Load(names[10], 16, 182);//lineSound
	mass[11].Load(names[11], 410, 5);//VolumeLine
	mass[12].Load(names[12], 16, 181);//sols for SoundLine
	mass[13].Load(names[12], 408, 5);//solsfor VolumeLine
	mass[14].Load(names[13], 120, 130);//btnlefteff
	mass[15].Load(names[14], 240, 130);//btnrighteff
}

void Rend(sf::RenderWindow& window, TextureRend SpLoad[16], sf::Text& text, std::vector<sf::RectangleShape> Block) {
	// Clear the window
	window.clear(sf::Color(41, 47, 54));

	//sprite draw

	if (isLeftBtn == 0) window.draw(SpLoad[0].sprite);			//Previous track
	else if (isLeftBtn == 1)  window.draw(SpLoad[14].sprite);	//

	if (isRightBtn == 0) window.draw(SpLoad[1].sprite);			//next track
	else if (isRightBtn == 1)  window.draw(SpLoad[15].sprite);	//

	if (isPlaying == 0) {										//Play and pause
		if (isPlay == 0) { window.draw(SpLoad[2].sprite); }		//
		else if (isPlay == 1)  window.draw(SpLoad[5].sprite);	//
	}															//
	else if (isPlaying == 1) {									//
		if (isPause == 0) window.draw(SpLoad[6].sprite);		//
		else if (isPause == 1)  window.draw(SpLoad[7].sprite);	//
	}															//

	if (isloop == 0) window.draw(SpLoad[3].sprite);				//Loop
	else if (isloop == 1) window.draw(SpLoad[9].sprite);		//

	if (isStop == 0) window.draw(SpLoad[4].sprite);				//Stop
	else if (isStop == 1) window.draw(SpLoad[8].sprite);		//

	window.draw(SpLoad[10].sprite);
	window.draw(SpLoad[12].sprite);
	window.draw(SpLoad[11].sprite);
	window.draw(SpLoad[13].sprite);
	window.draw(text);
	if (isPlaying) {
		for (int i = 0; i < Block.size(); i++) {
			window.draw(Block[i]);
		}
	}
	window.display();
}

