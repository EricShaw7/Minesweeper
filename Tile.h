#pragma once
#include <SFML/Graphics.hpp>

struct Tile
{
	int tileNumber;
	sf::Sprite sprite; //unrevealed tile
	sf::Sprite sprite2; //flag
	sf::Sprite sprite3; //mine
	sf::Sprite sprite4; //revealed tile

	sf::Sprite spriteOne;
	sf::Sprite spriteTwo;
	sf::Sprite spriteThree;
	sf::Sprite spriteFour;
	sf::Sprite spriteFive;
	sf::Sprite spriteSix;
	sf::Sprite spriteSeven;
	sf::Sprite spriteEight;

	int xPosition;
	int yPosition;
	bool isMine;
	bool isRevealed;
	bool isFlag;

	bool alreadyDrawn;

	Tile* up;
	Tile* upRight;
	Tile* right;
	Tile* downRight;
	Tile* down;
	Tile* downLeft;
	Tile* left;
	Tile* upLeft;

	Tile();

	Tile(int tileNum, sf::Sprite spr, sf::Sprite flag, sf::Sprite mine, sf::Sprite revealed, sf::Sprite one, sf::Sprite two, sf::Sprite three,
		sf::Sprite four, sf::Sprite five, sf::Sprite six, sf::Sprite seven, sf::Sprite eight, int xPos, int yPos); //constructor of a tile

	int findMines(); //find the number of adjacent mines

	bool checkMine(Tile* direction); //find if a particular adjacent tile is a mine
};
