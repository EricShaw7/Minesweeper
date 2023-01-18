#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(int tileNum, sf::Sprite spr, sf::Sprite flag, sf::Sprite mine, sf::Sprite revealed, sf::Sprite one, sf::Sprite two, sf::Sprite three,
	sf::Sprite four, sf::Sprite five, sf::Sprite six, sf::Sprite seven, sf::Sprite eight, int xPos, int yPos)
{
	tileNumber = tileNum;

	sprite = spr; //sprite of the tile
	sprite2 = flag; //sprite of the flag
	sprite3 = mine; //sprite of the mine
	sprite4 = revealed;

	spriteOne = one;
	spriteTwo = two;
	spriteThree = three;
	spriteFour = four;
	spriteFive = five;
	spriteSix = six;
	spriteSeven = seven;
	spriteEight = eight;

	sprite.setPosition(xPos, yPos);
	sprite2.setPosition(xPos, yPos);
	sprite3.setPosition(xPos, yPos);
	sprite4.setPosition(xPos, yPos);

	spriteOne.setPosition(xPos, yPos);
	spriteTwo.setPosition(xPos, yPos);
	spriteThree.setPosition(xPos, yPos);
	spriteFour.setPosition(xPos, yPos);
	spriteFive.setPosition(xPos, yPos);
	spriteSix.setPosition(xPos, yPos);
	spriteSeven.setPosition(xPos, yPos);
	spriteEight.setPosition(xPos, yPos);


	xPosition = xPos;
	yPosition = yPos;
	isMine = false;
	isRevealed = false;
	isFlag = false;

	alreadyDrawn = false;

	up = nullptr;
	upRight = nullptr;
	right = nullptr;
	downRight = nullptr;
	down = nullptr;
	downLeft = nullptr;
	left = nullptr;
	upLeft = nullptr;
}

int Tile::findMines()
{
	int numMines = 0;

	if (checkMine(up))
		numMines++;
	if (checkMine(upRight))
		numMines++;
	if (checkMine(right))
		numMines++;
	if (checkMine(downRight))
		numMines++;
	if (checkMine(down))
		numMines++;
	if (checkMine(downLeft))
		numMines++;
	if (checkMine(left))
		numMines++;
	if (checkMine(upLeft))
		numMines++;

	return numMines;
}

bool Tile::checkMine(Tile* direction)
{
	if (direction != nullptr)
	{
		if (direction->isMine == true)
		{
			return true;
		}
	}
	return false;
}