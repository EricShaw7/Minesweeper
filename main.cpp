#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "Random.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	const int numRows = 16;
	const int numColumns = 25;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

	sf::Texture hiddenTileTexture;
	hiddenTileTexture.loadFromFile("images/tile_hidden.png");
	sf::Sprite hiddenTileSprite(hiddenTileTexture);

	sf::Texture revealedTileTexture;
	revealedTileTexture.loadFromFile("images/tile_revealed.png");
	sf::Sprite revealedTileSprite(revealedTileTexture);

	sf::Texture happyFaceTexture;
	happyFaceTexture.loadFromFile("images/face_happy.png");
	sf::Sprite happyFaceSprite(happyFaceTexture);
	happyFaceSprite.setPosition(368, 512);

	sf::Texture loseFaceTexture;
	loseFaceTexture.loadFromFile("images/face_lose.png");
	sf::Sprite loseFaceSprite(loseFaceTexture);
	loseFaceSprite.setPosition(368, 512);

	sf::Texture winFaceTexture;
	winFaceTexture.loadFromFile("images/face_win.png");
	sf::Sprite winFaceSprite(winFaceTexture);
	winFaceSprite.setPosition(368, 512);

	sf::Texture digitsTexture;
	digitsTexture.loadFromFile("images/digits.png");
	sf::Sprite digitsSprite(digitsTexture);
	digitsSprite.setPosition(0, 512);

	sf::Texture debugTexture;
	debugTexture.loadFromFile("images/debug.png");
	sf::Sprite debugSprite(debugTexture);
	debugSprite.setPosition(496, 512);

	sf::Texture test1Texture;
	test1Texture.loadFromFile("images/test_1.png");
	sf::Sprite test1Sprite(test1Texture);
	test1Sprite.setPosition(560, 512);

	sf::Texture test2Texture;
	test2Texture.loadFromFile("images/test_2.png");
	sf::Sprite test2Sprite(test2Texture);
	test2Sprite.setPosition(624, 512);

	sf::Texture test3Texture;
	test3Texture.loadFromFile("images/test_3.png");
	sf::Sprite test3Sprite(test3Texture);
	test3Sprite.setPosition(688, 512);

	sf::Texture flagTexture;
	flagTexture.loadFromFile("images/flag.png");
	sf::Sprite flagSprite(flagTexture);

	sf::Texture mineTexture;
	mineTexture.loadFromFile("images/mine.png");
	sf::Sprite mineSprite(mineTexture);

	sf::Texture oneTexture;
	oneTexture.loadFromFile("images/number_1.png");
	sf::Sprite oneSprite(oneTexture);

	sf::Texture twoTexture;
	twoTexture.loadFromFile("images/number_2.png");
	sf::Sprite twoSprite(twoTexture);

	sf::Texture threeTexture;
	threeTexture.loadFromFile("images/number_3.png");
	sf::Sprite threeSprite(threeTexture);

	sf::Texture fourTexture;
	fourTexture.loadFromFile("images/number_4.png");
	sf::Sprite fourSprite(fourTexture);

	sf::Texture fiveTexture;
	fiveTexture.loadFromFile("images/number_5.png");
	sf::Sprite fiveSprite(fiveTexture);

	sf::Texture sixTexture;
	sixTexture.loadFromFile("images/number_6.png");
	sf::Sprite sixSprite(sixTexture);

	sf::Texture sevenTexture;
	sevenTexture.loadFromFile("images/number_7.png");
	sf::Sprite sevenSprite(sevenTexture);

	sf::Texture eightTexture;
	eightTexture.loadFromFile("images/number_8.png");
	sf::Sprite eightSprite(eightTexture);

	//sf::Sprite tiles[numRows * numColumns];

	int j = -1;
	vector<Tile> tiles;
	for (int i = 0; i < (numRows * numColumns); i++) //initializing all of the 400 tiles to empty tiles
	{
		if (i % 25 == 0)
		{
			j++;
		}
		int xPosition = 32 * (i % 25);
		int yPosition = 32 * j;
		Tile temp = Tile(i, hiddenTileSprite, flagSprite, mineSprite, revealedTileSprite, oneSprite, twoSprite, threeSprite,
			 fourSprite, fiveSprite, sixSprite, sevenSprite, eightSprite, xPosition, yPosition);
		tiles.push_back(temp);

		//tiles[i].sprite.setPosition(xPosition, yPosition);
	}

	int numMines = 0;
	while (numMines < 50) //makes 50 random tiles mines
	{
		int temp = Random::Int(0, 399);
		if (tiles[temp].isMine == false)
		{
			tiles[temp].isMine = true;
			numMines++;
		}
	}

	for (int i = 0; i < 400; i++) //initializing the 8 pointers for each tile
	{
		if (i >= 25)
		{
			tiles[i].up = &tiles[i - 25];
		}
		if (i < 375)
		{
			tiles[i].down = &tiles[i + 25];
		}
		if (i % 25 != 0)
		{
			tiles[i].left = &tiles[i - 1];
		}
		if ((i + 1) % 25 != 0)
		{
			tiles[i].right = &tiles[i + 1];
		}
		if (i >= 25 && (i + 1) % 25 != 0)
		{
			tiles[i].upRight = &tiles[i - 24];
		}
		if (i >= 25 && (i % 25) != 0)
		{
			tiles[i].upLeft = &tiles[i - 26];
		}
		if (i < 375 && (i + 1) % 25 != 0)
		{
			tiles[i].downRight = &tiles[i + 26];
		}
		if (i < 375 && (i % 25) != 0)
		{
			tiles[i].downLeft = &tiles[i + 24];
		}
	}

	int spacesCleared = 0;
	bool gameOver = false;
	bool gameWin = false;
	bool toggleOn = false;
	int numFlags = 0;
	int numberOfMines = 50;

	bool justRevealed = false;

	ifstream file1("boards/testboard1.brd");

	ifstream file2("boards/testboard2.brd");
	vector<bool> areMines;
	ifstream file3("boards/testboard3.brd");


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				int x = position.x;
				int y = position.y;
				if (event.mouseButton.button == sf::Mouse::Left) // if left click
				{
					if (x <= 800 && y <= 512) //if in range of the board
					{
						int columnNumber = x / 32;
						int rowNumber = y / 32;
						if (tiles[25 * rowNumber + columnNumber].isFlag == false && gameWin == false && gameOver == false)
						{
							tiles[25 * rowNumber + columnNumber].isRevealed = true;

							if (tiles[25 * rowNumber + columnNumber].isMine == true)
							{
								gameOver = true;
								for (int i = 0; i < 400; i++)
								{
									if (tiles[i].isMine == true)
										tiles[i].isRevealed = true;
								}
							}
						}
					}
					else if (x >= 368 && x <= 432 && y >= 512 && y <= 576) //smiley face is from (368, 512) to (432, 576)
					{
						//restart the board
						gameOver = false;
						gameWin = false;
						numFlags = 0;
						for (int i = 0; i < 400; i++)
						{
							tiles[i].isFlag = false;
							tiles[i].isRevealed = false;
							tiles[i].isMine = false;
							tiles[i].alreadyDrawn = false;
						}
						numMines = 0;
						numberOfMines = 50;
						while (numMines < numberOfMines) //makes 50 random tiles mines
						{
							int temp = Random::Int(0, 399);
							if (tiles[temp].isMine == false)
							{
								tiles[temp].isMine = true;
								numMines++;
							}
						}
					}
					else if (x >= 496 && x < 560 && y >= 512 && y <= 576) //debug is from (496, 512) to (560, 576)
					{
						if (toggleOn == false)
							toggleOn = true;
						else
							toggleOn = false;
					}
					else if (x >= 560 && x < 624 && y >= 512 && y <= 576) //test1 is from (560, 512) to (624, 576)
					{
						gameOver = false;
						gameWin = false;
						numFlags = 0;
						numMines = 0;
						numberOfMines = 0;
						for (int i = 0; i < 400; i++)
						{
							tiles[i].isFlag = false;
							tiles[i].isRevealed = false;
							tiles[i].isMine = false;
							tiles[i].alreadyDrawn = false;
						}
						file1.clear();
						file1.seekg(0, ios::beg);
						char value;

						int j = 0;
						while (file1.get(value))
						{
							if ((int)value - 48 == 1)
							{
								areMines.push_back(true);
								numMines++;
								numberOfMines++;
							}
							else
								areMines.push_back(false);
							j++;
							if (j % 25 == 0 && j != 0)
								file1.get(value);
						}
						for (int i = 0; i < 400; i++)
						{
							if (areMines[i] == true)
								tiles[i].isMine = true;
						}
						areMines.clear();
					}
					else if (x >= 624 && x < 688 && y >= 512 && y <= 576) //test2 is from (624, 512) to (688, 576)
					{
						gameOver = false;
						gameWin = false;
						numFlags = 0;
						numMines = 0;
						numberOfMines = 0;
						for (int i = 0; i < 400; i++)
						{
							tiles[i].isFlag = false;
							tiles[i].isRevealed = false;
							tiles[i].isMine = false;
							tiles[i].alreadyDrawn = false;
						}
						file2.clear();
						file2.seekg(0, ios::beg);
						char value;

						int j = 0;
						while (file2.get(value))
						{
							if ((int)value - 48 == 1)
							{
								areMines.push_back(true);
								numMines++;
								numberOfMines++;
							}
							else
								areMines.push_back(false);
							j++;
							if (j % 25 == 0 && j != 0)
								file2.get(value);
						}
						for (int i = 0; i < 400; i++)
						{
							if (areMines[i] == true)
								tiles[i].isMine = true;
						}
						areMines.clear();
					}
					else if (x >= 688 && x < 752 && y >= 512 && y <= 576) //test3 is from (688, 512) to (752, 576)
					{
						gameOver = false;
						gameWin = false;
						numFlags = 0;
						numMines = 0;
						numberOfMines = 0;
						for (int i = 0; i < 400; i++)
						{
							tiles[i].isFlag = false;
							tiles[i].isRevealed = false;
							tiles[i].isMine = false;
							tiles[i].alreadyDrawn = false;
						}
						file3.clear();
						file3.seekg(0, ios::beg);
						char value;
							
						int	j = 0;
						while (file3.get(value))
						{
							if ((int)value - 48 == 1)
							{
								areMines.push_back(true);
								numMines++;
								numberOfMines++;
							}
							else
								areMines.push_back(false);
							j++;
							if (j % 25 == 0 && j != 0)
								file3.get(value);
						}
					for (int i = 0; i < 400; i++)
					{
						if (areMines[i] == true)
							tiles[i].isMine = true;
					}
					areMines.clear();
					}
				}
				else if (gameOver == false) // if right click
				{
					if (x <= 800 && y <= 512) //if in range of the board
					{
						int columnNumber = x / 32;
						int rowNumber = y / 32;
						if (tiles[25 * rowNumber + columnNumber].isRevealed == false)
						{
							if (tiles[25 * rowNumber + columnNumber].isFlag == true)
							{
								tiles[25 * rowNumber + columnNumber].isFlag = false;
								numFlags--;
							}
							else
							{
								tiles[25 * rowNumber + columnNumber].isFlag = true;
								numFlags++;
							}

						}
					}
				}
			}
		}

		int j = 0;
		for (int i = 0; i < 400; i++)
		{
			if (tiles[i].isRevealed == false) //if tile is not revealed yet
			{
				window.draw(tiles[i].sprite);
			}
			else 
			{
				j++;
				window.draw(tiles[i].sprite4);
				if (tiles[i].isMine == false)
				{
					switch (tiles[i].findMines())
					{
					case 1:
						window.draw(tiles[i].spriteOne);
						break;
					case 2:
						window.draw(tiles[i].spriteTwo);
						break;
					case 3:
						window.draw(tiles[i].spriteThree);
						break;
					case 4:
						window.draw(tiles[i].spriteFour);
						break;
					case 5:
						window.draw(tiles[i].spriteFive);
						break;
					case 6:
						window.draw(tiles[i].spriteSix);
						break;
					case 7:
						window.draw(tiles[i].spriteSeven);
						break;
					case 8:
						window.draw(tiles[i].spriteEight);
						break;
					default: //need to reveal tiles surrounding it
						if (tiles[i].alreadyDrawn == false) {
							if (tiles[i].up != nullptr)
								if (tiles[i].up->isFlag == false)
									tiles[i].up->isRevealed = true;
							if (tiles[i].upRight != nullptr)
								if (tiles[i].upRight->isFlag == false)
									tiles[i].upRight->isRevealed = true;
							if (tiles[i].right != nullptr)
								if (tiles[i].right->isFlag == false)
									tiles[i].right->isRevealed = true;
							if (tiles[i].downRight != nullptr)
								if (tiles[i].downRight->isFlag == false)
									tiles[i].downRight->isRevealed = true;
							if (tiles[i].down != nullptr)
								if (tiles[i].down->isFlag == false)
									tiles[i].down->isRevealed = true;
							if (tiles[i].downLeft != nullptr)
								if (tiles[i].downLeft->isFlag == false)
									tiles[i].downLeft->isRevealed = true;
							if (tiles[i].left != nullptr)
								if (tiles[i].left->isFlag == false)
									tiles[i].left->isRevealed = true;
							if (tiles[i].upLeft != nullptr)
								if (tiles[i].upLeft->isFlag == false)
									tiles[i].upLeft->isRevealed = true;
						}
						tiles[i].alreadyDrawn = true;
						break;
					}
				}
			}
			spacesCleared = j;
		}

		//if (gameOver == false)
		//{
		for (int i = 0; i < 400; i++) //prints flags
		{
			if (tiles[i].isFlag == true)
			{
				window.draw(tiles[i].sprite2);
			}
		}
		//}

		//how the game determines which smiley face to show
		if (gameOver) 
		{
			window.draw(loseFaceSprite);
			for (int i = 0; i < 400; i++)
			{
				if (tiles[i].isMine == true)
				{
					window.draw(tiles[i].sprite3);
				}
			}
		}
		else if (spacesCleared >= 400 - numberOfMines)
		{
			window.draw(winFaceSprite);
			numFlags = numberOfMines;
			gameWin = true;
			for (int i = 0; i < 400; i++)
			{
				if (tiles[i].isMine == true)
				{
					//window.draw(tiles[i].sprite3);
					window.draw(tiles[i].sprite2);
				}
			}
		}
		else
		{
			window.draw(happyFaceSprite);
		}

		//printing the number of mines - number of flags
		int z = numberOfMines - numFlags;
		if (z < 0) //the case where we must print a negative first
		{
			digitsSprite.setPosition(0, 512);
			digitsSprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
			window.draw(digitsSprite); //prints -

			z *= -1;

			int a = z / 100;
			digitsSprite.setPosition(21, 512);
			digitsSprite.setTextureRect(sf::IntRect(a * 21, 0, 21, 32));
			window.draw(digitsSprite);

			a = z / 10;
			if (a >= 10)
				a -= 10;
			digitsSprite.setPosition(42, 512);
			digitsSprite.setTextureRect(sf::IntRect(a * 21, 0, 21, 32));
			window.draw(digitsSprite);

			a = z % 10;
			digitsSprite.setPosition(63, 512);
			digitsSprite.setTextureRect(sf::IntRect(a * 21, 0, 21, 32));
			window.draw(digitsSprite);
		}
		else if (z == 0)//the case where we flagged equal to the number of mines
		{
			digitsSprite.setPosition(0, 512);
			digitsSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
			window.draw(digitsSprite); //prints 0

			digitsSprite.setPosition(21, 512);
			digitsSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
			window.draw(digitsSprite); //prints 0

			digitsSprite.setPosition(42, 512);
			digitsSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
			window.draw(digitsSprite); //prints 0
		}
		else //"normal" case where theres not enough flags yet
		{
			int a = z / 100;
			digitsSprite.setPosition(0, 512);
			digitsSprite.setTextureRect(sf::IntRect(a*21, 0, 21, 32));
			window.draw(digitsSprite);

			a = z / 10;
			if (a >= 10)
				a -= 10;
			digitsSprite.setPosition(21, 512);
			digitsSprite.setTextureRect(sf::IntRect(a * 21, 0, 21, 32));
			window.draw(digitsSprite);

			a = z % 10;
			digitsSprite.setPosition(42, 512);
			digitsSprite.setTextureRect(sf::IntRect(a * 21, 0, 21, 32));
			window.draw(digitsSprite);
		}

		if (toggleOn)
		{
			for (int i = 0; i < 400; i++)
			{
				if (tiles[i].isMine == true)
				{
					window.draw(tiles[i].sprite3);
				}
			}
		}

		window.draw(debugSprite);
		window.draw(test1Sprite);
		window.draw(test2Sprite);
		window.draw(test3Sprite);

		window.display();
		window.clear();
	}

	return 0;
}

/*
comments to note about the location of certain tiles
tile 0 is from (0,0) to (32,32)
tile 1 is from (33, 0) to (64, 32)
tile 2 is from (65, 0) to (96, 32)

tile 25 is from (0, 32) to (32, 64)


debug is from (496, 512) to (560, 576)
*/