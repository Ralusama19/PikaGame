#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>

bool isWhite(sf::Image& image, float px, float py){
	return image.getPixel(px, py) == sf::Color::White;
}

int main(){

	//CONSTANT AND 'GLOBAL' VARIABLES
	int speed = 100, speed2 = 100;
	float time_to_next_sprite = 0.09;
	enum direction { down, left, right, up , none};
	const int mx[5] = {0,	-1,    1,	 0,   0};
	const int my[5] = {1,	 0,	   0,	-1,   0};

	//'VECTOR2's
	sf::Vector2f spriteSize(28,28);
	sf::Vector2f spriteSize2(28,28);
	sf::Vector2f melocSize(16,14);
	sf::Vector2f zumoSize(14,14);
	sf::Vector2i spriteSource(0,down);
	sf::Vector2i spriteSource2(0,down);
	sf::Vector2f originalSpriteSize(0,0);
	sf::Vector2f originalSpriteSize2(0,0);
	sf::Vector2f playerPosition(350,280);
	sf::Vector2f playerPosition2(280,350);
	std::vector<std::pair<int, sf::Sprite> > bayas;
	//SFML OBJECTS
	sf::Event event;
	sf::Clock deltaClock, melocClock, zumoClock, zumo2Clock, pokeClock, poke2Clock, spawnClock;
	sf::Image image;
	sf::Sprite player, player2, background, meloc, zumo, stone, pokeball, zreza;
	sf::Texture tplayer, tplayer2, tbackground, tmeloc, tzumo, tstone, tpokeball, tzreza;

	//LOAD TEXTURES
	if(!image.loadFromFile("map.png")) std::cout << "collision map not loaded" << std::endl;
 	if(!tzumo.loadFromFile("zumo.png")) std::cout << "zumo texture Not Loaded " << std::endl;
	if(!tmeloc.loadFromFile("meloc.png")) std::cout << "meloc texture Not Loaded " << std::endl;
	if(!tzreza.loadFromFile("zreza.png")) std::cout << "zreza texture Not Loaded " << std::endl;
	if(!tstone.loadFromFile("piedratrueno.png")) std::cout << "stone texture Not Loaded " << std::endl;
	if(!tpokeball.loadFromFile("poke.png")) std::cout << "poke texture Not Loaded " << std::endl;
	if(!tbackground.loadFromFile("ground.png")) std::cout << "background texture Not Loaded " << std::endl;
	if(!tplayer.loadFromFile("pikachu.png")) std::cout << "personatge Not Loaded " << std::endl;
	if(!tplayer2.loadFromFile("pikachu.png")) std::cout << "personatge2 Not Loaded " << std::endl;
	spriteSize.x = originalSpriteSize.x = tplayer.getSize().x/4;
	spriteSize.y = originalSpriteSize.y = tplayer.getSize().y/4;

	spriteSize2.x = originalSpriteSize2.x = tplayer2.getSize().x/4;
	spriteSize2.y = originalSpriteSize2.y = tplayer2.getSize().y/4;

	//VARIABLES
	int melocCount = 0;
	bool speedup = false, speedup2 = false, raichu = false, raichu2 = false, poke=false, poke2 = false;
	direction d = none, q = none;
	bool keypressed = false;
	float deltatime = 0, movx = 0.0, movy = 0.0, scont = 0.0, scont2 = 0.0, movx2 = 0.0, movy2 = 0.0;
	float distx = spriteSize.x/4, disty = spriteSize.y/4, distx2 = spriteSize2.x/4, disty2 = spriteSize2.y/4;

	//Set player's properties
	player.setTexture(tplayer);
	player.setPosition(playerPosition);

	player2.setTexture(tplayer2);
	player2.setPosition(playerPosition2);

	//Set Background's properties
	background.setTexture(tbackground);


	//CREATE THE WINDOW
	sf::RenderWindow window(sf::VideoMode(639, 480), "Pika!");
	std::cout << "Howdy fellow trainer! Here's your chance to help Pikachu" << std::endl
	<< "collect all the Pechaberries he can get!" << std::endl
	<< "If you get the chance to collect a Mobile Orb, you'll be able to move faster!" << std::endl
	<< "Use them wisly, as they last only 10 seconds." << std::endl
	<< "Be careful with Pokeballs, they'll slow you down, you may want to avoid them." << std::endl
	<< "Although no one has seen it yet, some say a mighty stone could appear" << std::endl
	<< "and turn Pikachu into an even more powerfull creature. Keep your eyes wide open." << std::endl
	<< "Your score will appear down here, good luck!" << std::endl;

	sf::Music music;
	if (!music.openFromFile("pikaGirl.wav")) std::cout << "couldnt load music" << std::endl; // error
	music.play();
	//GAME LOOP
	while(window.isOpen()){

		//Loop for handling events
		while(window.pollEvent(event)){
			switch (event.type){
				//Close event
				case sf::Event::Closed:
					window.close();
					break;
				//KeyPressed event
				case  sf::Event::KeyPressed:
					//Close key
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
					}/*
					//Increasing Speed
					if (event.key.code == sf::Keyboard::S) {
						if(speed < 280){
							speed += 20;
							time_to_next_sprite -= 0.01;
						}
					}
					//Decreasing Speed
					if (event.key.code == sf::Keyboard::D) {
						if(speed > 80){
							speed -= 20;
							time_to_next_sprite += 0.01;
						}
					}*/
					break;
				//Default
				default:
					//Do nothing
					break;
			}
		}	
		if (poke and pokeClock.getElapsedTime().asSeconds() >= 5){
			poke = false;
			if(!tplayer.loadFromFile("pikachu.png")) std::cout << "personatge Not Loaded " << std::endl;
			spriteSize.x = originalSpriteSize.x = tplayer.getSize().x/4;
			spriteSize.y = originalSpriteSize.y = tplayer.getSize().y/4;
		}
		if (poke2 and poke2Clock.getElapsedTime().asSeconds() >= 5){
			poke2 = false;
			if(!tplayer2.loadFromFile("pikachu.png")) std::cout << "personatge Not Loaded " << std::endl;
			spriteSize2.x = originalSpriteSize.x = tplayer2.getSize().x/4;
			spriteSize2.y = originalSpriteSize.y = tplayer2.getSize().y/4;
		}
		if (zumoClock.getElapsedTime().asSeconds() >= 10) speedup = false;
		if (zumo2Clock.getElapsedTime().asSeconds() >= 10) speedup2 = false;

		if(poke) speed = 20;
		else if (speedup) speed = 240;
		else if(raichu) speed = 150;
		else speed = 100;

		if(poke2) speed2 = 20;
		else if (speedup2) speed2 = 240;
		else speed2 = 100;

		//Deltatime 
		deltatime = deltaClock.restart().asSeconds();
		scont += deltatime;
		scont2 += deltatime;

		//Update Direction 'd'
		d = none;

	        //By keyboard
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 	d = up;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	d = down;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	d = left;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	d = right;


		
		q = none;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) q = up;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))	q = down;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))	q = left;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))	q = right;

		//If there is a direction
		if(d != none){
			//Set value to movement variables and update spritesource
			if(spriteSource.y == d){
				movx += mx[d]*speed*deltatime;
				movy += my[d]*speed*deltatime;
			}
			else spriteSource.y = d; //so you can turn without walking
			if (scont >= time_to_next_sprite){
				scont = 0;
				++spriteSource.x;
			}
		}

		if (q != none){
			//Set value to movement variables and update spritesource
			if(spriteSource2.y == q){
				movx2 += mx[q]*speed2*deltatime;
				movy2 += my[q]*speed2*deltatime;
			}
			else spriteSource2.y = q; //so you can turn without walking
			if (scont2 >= time_to_next_sprite){
				scont2 = 0;
				++spriteSource2.x;
			}
		}
		

		int destix = playerPosition.x+movx;
		int destiy = playerPosition.y+movy;

		
		int destix2 = playerPosition2.x+movx2;
		int destiy2 = playerPosition2.y+movy2;
		
		
		//Calcule the point in the image corresponding to the point the player is in the background
		float px, py;
		px = image.getSize().x*destix/tbackground.getSize().x/background.getScale().x;
		py = image.getSize().y*destiy/tbackground.getSize().y/background.getScale().y;

		//Check if the color of the corresponding point is White (if it is let the player move)
		if( isWhite(image, px, py) && isWhite(image, px, image.getSize().y*(destiy-disty)/tbackground.getSize().y/background.getScale().y) &&
			isWhite(image, image.getSize().x*(destix+distx)/tbackground.getSize().x/background.getScale().x, image.getSize().y*(destiy-disty)/tbackground.getSize().y/background.getScale().y) &&
			isWhite(image, image.getSize().x*(destix-distx)/tbackground.getSize().x/background.getScale().x, image.getSize().y*(destiy-disty)/tbackground.getSize().y/background.getScale().y) &&
			isWhite(image, image.getSize().x*(destix+distx)/tbackground.getSize().x/background.getScale().x, py) &&
			isWhite(image, image.getSize().x*(destix-distx)/tbackground.getSize().x/background.getScale().x, py) 
			){
				playerPosition.x += movx;
				playerPosition.y += movy;
		}

		movx = movy = 0;

		px = image.getSize().x*destix2/tbackground.getSize().x/background.getScale().x;
		py = image.getSize().y*destiy2/tbackground.getSize().y/background.getScale().y;

		//Check if the color of the corresponding point is White (if it is let the player move)
		if( isWhite(image, px, py) && isWhite(image, px, image.getSize().y*(destiy2-disty2)/tbackground.getSize().y/background.getScale().y) &&
			isWhite(image, image.getSize().x*(destix2+distx2)/tbackground.getSize().x/background.getScale().x, image.getSize().y*(destiy2-disty2)/tbackground.getSize().y/background.getScale().y) &&
			isWhite(image, image.getSize().x*(destix2-distx2)/tbackground.getSize().x/background.getScale().x, image.getSize().y*(destiy2-disty2)/tbackground.getSize().y/background.getScale().y) &&
			isWhite(image, image.getSize().x*(destix2+distx2)/tbackground.getSize().x/background.getScale().x, py) &&
			isWhite(image, image.getSize().x*(destix2-distx2)/tbackground.getSize().x/background.getScale().x, py) 
			){
				playerPosition2.x += movx2;
				playerPosition2.y += movy2;
		}

		movx2 = movy2 = 0;

		//Checking the sprite sources and position to be ok
		if(spriteSource.x >= 4) spriteSource.x = 0;
		float aux = background.getTexture()->getSize().y * background.getScale().y;
		if(playerPosition.x < 0) playerPosition.x = 0;
		else if (playerPosition.y < 0) playerPosition.y = 0;
		else if (playerPosition.x > window.getSize().x) playerPosition.x = window.getSize().x-1;
		else if (playerPosition.y > aux) playerPosition.y = aux -1;

		if(spriteSource2.x >= 4) spriteSource2.x = 0;
		aux = background.getTexture()->getSize().y * background.getScale().y;
		if(playerPosition2.x < 0) playerPosition2.x = 0;
		else if (playerPosition2.y < 0) playerPosition2.y = 0;
		else if (playerPosition2.x > window.getSize().x) playerPosition2.x = window.getSize().x-10;
		else if (playerPosition2.y > aux) playerPosition2.y = aux -10;
		//Clear the window
		window.clear();

		//Set player properties (some are unnecessary but is useful in case there are changes i.e. the screen changes)
		player.setOrigin(spriteSize.x/2, spriteSize.y);
		player.setPosition(playerPosition.x, playerPosition.y);
		player.setTextureRect(sf::IntRect(spriteSource.x*spriteSize.x, spriteSource.y*spriteSize.y, spriteSize.x, spriteSize.y));

		player2.setOrigin(spriteSize2.x/2, spriteSize2.y);
		player2.setPosition(playerPosition2.x, playerPosition2.y);
		player2.setTextureRect(sf::IntRect(spriteSource2.x*spriteSize2.x, spriteSource2.y*spriteSize2.y, spriteSize2.x, spriteSize2.y));

		srand(time (NULL));

		float temps = (rand()%1 + 4);
		int spawn = (rand()%259 + 1); 
		
		//Set window view, draw and display
		window.draw(background);

		if (melocClock.getElapsedTime().asSeconds() >= temps){
			float melocX = rand()%639, melocY = rand()%480;
			while (!isWhite(image, melocX, melocY)){
				melocX = rand()%639;
				melocY = rand()%480;
			}
			meloc.setTexture(tmeloc);
			meloc.setOrigin(melocSize.x/2, melocSize.y);
			meloc.setPosition(melocX, melocY);
			bayas.push_back(std::make_pair(1,meloc));
			melocClock.restart();
		}

		if (spawnClock.getElapsedTime().asSeconds() >= 1){
			if (spawn%15 == 0){
				float zumoX = rand()%639, zumoY = rand()%480;
				while (!isWhite(image, zumoX, zumoY)){
					zumoX = rand()%639;
					zumoY = rand()%480;
				}
				zumo.setTexture(tzumo);
				zumo.setOrigin(zumoSize.x/2, zumoSize.y);
				zumo.setPosition(zumoX, zumoY);
				bayas.push_back(std::make_pair(0,zumo));
			}


			if (spawn%42 == 0){
				float zrezaX = rand()%639, zrezaY = rand()%480;
				while (!isWhite(image, zrezaX, zrezaY)){
					zrezaX = rand()%639;
					zrezaY = rand()%480;
				}
				zreza.setTexture(tzreza);
				zreza.setOrigin(6, 14);
				zreza.setPosition(zrezaX, zrezaY);
				bayas.push_back(std::make_pair(2,zreza));
			}

			if (spawn%69 == 0){
				float pokeballX = rand()%639, pokeballY = rand()%480;
				while (!isWhite(image, pokeballX, pokeballY)){
					pokeballX = rand()%639;
					pokeballY = rand()%480;
				}
				pokeball.setTexture(tpokeball);
				pokeball.setOrigin(7, 7);
				pokeball.setPosition(pokeballX, pokeballY);
				bayas.push_back(std::make_pair(3,pokeball));
			}

			if (spawn%70 == 0 and raichu == false){
				raichu = true;
				float stoneX = rand()%639, stoneY = rand()%480;
				while (!isWhite(image, stoneX, stoneY)){
					stoneX = rand()%639;
					stoneY = rand()%480;
				}
				stone.setTexture(tstone);
				stone.setOrigin(zumoSize.x/2, zumoSize.y);
				stone.setPosition(stoneX, stoneY);
				bayas.push_back(std::make_pair(4,stone));
			}
			spawnClock.restart();
		}
		int intersection;
		for (int i = 0; i < bayas.size(); ++i){
			if(player.getGlobalBounds().intersects(bayas[i].second.getGlobalBounds())) intersection = 1;
			else if (player2.getGlobalBounds().intersects(bayas[i].second.getGlobalBounds())) intersection = 2;
			else intersection = 0;

			if (intersection > 0){
				if (bayas[i].first == 0){ //es fugaesfera
					if (intersection == 1){
						speedup = true;
						zumoClock.restart();
					}
					else {
						speedup2 = true;
						zumo2Clock.restart();
					}
				}
				else if (bayas[i].first == 1){ //es baya meloc
					++melocCount;
					std::cout<< melocCount << std::endl;
				}
				else if (bayas[i].first == 2){ //es baya zreza
					melocCount = melocCount + 5;
					std::cout<< melocCount << std::endl;
				}
				else if (bayas[i].first == 3){ //es pokeball
					if (intersection == 1){
						poke = true;
						raichu = false;
						if(!tplayer.loadFromFile("pokeball.png")) std::cout << "pokeball Not Loaded " << std::endl;
						spriteSize.x = 14; 
						spriteSize.y = 14;
						distx = spriteSize.x/4, disty = spriteSize.y/4;
						pokeClock.restart();
					}
					else {
						poke2 = true;
						if(!tplayer2.loadFromFile("pokeball.png")) std::cout << "pokeball Not Loaded " << std::endl;
						spriteSize2.x = 14; 
						spriteSize2.y = 14;
						distx2 = spriteSize2.x/4, disty2 = spriteSize2.y/4;
						poke2Clock.restart();
					}
				}
				else if (bayas[i].first == 4){ //es piedra trueno
					raichu = true;
					if(!tplayer.loadFromFile("raichu.png")) std::cout << "raichu Not Loaded " << std::endl;
						spriteSize.x = tplayer.getSize().x/4;
						spriteSize.y = tplayer.getSize().y/4;
						distx = spriteSize.x/4, disty = spriteSize.y/4;
				}
				bayas.erase(bayas.begin()+i);
			}
			else window.draw(bayas[i].second);
		}
		window.draw(player);
		window.draw(player2);
		window.display();
	}
}