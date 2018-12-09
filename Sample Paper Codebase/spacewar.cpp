// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include <ctime>
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	// GAME EDITED
	//THIS LINE OF CODE DAMN IMPORTANT
	srand(time(NULL));
	// to edit the seed here for the rng to be truly random
	//////////////////////////////////
    // nebula texture
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!playerShipTexture.initialize(graphics, PLAYERSHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing playership texture"));

    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));


	if (!playerShip.initialize(this, playerShipNS::WIDTH, playerShipNS::HEIGHT, playerShipNS::TEXTURE_COLS, &playerShipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player ship"));


	if (!playerShip.initialize(this, playerShipNS::WIDTH, playerShipNS::HEIGHT, playerShipNS::TEXTURE_COLS, &playerShipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player ship"));




	// GPP EDITED////////////////////////////////////////////////////////////////////////////

	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing AI textures"));


	if (!aITexture.initialize(graphics, PLAYERSHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing AI textures"));

	//2) Introduce 2 new spaceships
	// the exam already introduced 2 spaceships
	if (!ship2.initialize(this, playerShipNS::WIDTH, playerShipNS::HEIGHT, playerShipNS::TEXTURE_COLS, &aITexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ai ship"));
	if (!ship1.initialize(this, playerShipNS::WIDTH, playerShipNS::HEIGHT, playerShipNS::TEXTURE_COLS, &aITexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ai ship"));

	//pass by reference by address here
	aiShipList.push_back(&ship1);
	aiShipList.push_back(&ship2);
	for each (Ship *ship in aiShipList) {
		ship->setFrames(playerShipNS::PLAYERSHIP_START_FRAME, playerShipNS::PLAYERSHIP_END_FRAME);
		ship->setCurrentFrame(playerShipNS::PLAYERSHIP_START_FRAME);
		ship->setDegrees(270);
		ship->setX(GAME_WIDTH);
		ship->setY(static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / (GAME_HEIGHT))));
		//ship.setY(GAME_HEIGHT);
	}


	for (int i = 0; i < 3; i++) 
	{
		heart = new Image();
		if (!heart->initialize(graphics,130,120,0,&heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player ship"));

		//this one use brain logic
		// to print the heart in which column of the game_width :D
		heart->setX(GAME_WIDTH / 10 * i);
		heart->setScale(heartScale);
		heartList.push_back(heart);
	}
	////////////////////////////////////////////////////////////////////////////




	playerShip.setFrames(playerShipNS::PLAYERSHIP_START_FRAME, playerShipNS::PLAYERSHIP_END_FRAME);
	playerShip.setCurrentFrame(playerShipNS::PLAYERSHIP_START_FRAME);
	playerShip.setX(10);
	playerShip.setY(GAME_HEIGHT / 2);
	playerShip.setDegrees(90);
	playerShip.setVelocity(VECTOR2(-playerShipNS::SPEED, -playerShipNS::SPEED)); // VECTOR2(X, Y)

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
    planet.update(frameTime);
	playerShip.update(frameTime);

	/*for each (Ship *ship in aiShipList) 
	{
		ship->setX(ship->getX() - static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / (shipNS::SPEED)))*frameTime);
	}*/

	ship1.setX(ship1.getX() - 100.0f*frameTime);
	ship2.setX(ship2.getX() - 200.0f*frameTime);

	//change the ships direction here
	//Input *input = new Input();
	//press "W"
	// placed magic number here too lazy
	if (input->wasKeyPressed(0x57))
	{
		//playerShip.setY(playerShip.getY() + 100.0f*frameTime);
		playerShip.setX(playerShip.getX() + 100.0f*frameTime);
	}
	//press "S"
	if (input->wasKeyPressed(0x53)) {
		playerShip.setX(playerShip.getX() - 100.0f*frameTime);
	}
	//press "A"
	if (input->wasKeyPressed('A')) 
	{
		//just rotate the damn image to the left
		//qn never specify
		playerShip.setRadians(playerShip.getRadians() - playerShipNS::ROTATION_RATE*frameTime);
	}
	//press "D" to rotate to the right
	if (input->wasKeyPressed('D'))
	{
		//just rotate the damn image to the left
		//qn never specify
		playerShip.setRadians(playerShip.getRadians() + playerShipNS::ROTATION_RATE*frameTime);
	}

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{
	//GPP EDITED
	for each (Ship *ship in aiShipList) 
	{
		if (ship->getX() + ship->getWidth() < 0) 
		{
			ship->setX(GAME_WIDTH);
		}

	}

	/////////////

}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
	//GPP EDITED///////////////////////////////////////////
    //VECTOR2 collisionVector;
    //// if collision between ship and planet
    //if(ship1.collidesWith(planet, collisionVector))
    //{
    //    // bounce off planet
    //    ship1.bounce(collisionVector, planet);
    //    
    //}

	for each (Ship *ship in aiShipList) 
	{
		VECTOR2 collisionVector;
		ship->setCollisionRadius(100.0f);
		if (playerShip.collidesWith(*ship, collisionVector)) 
		{
			if (heartList.size() != 0) {
				SAFE_DELETE(*heartList.begin());
				heartList.erase(heartList.begin());
				break;
			}
			else
				continue;
		}

	}
	////////////////////////////////////////////////////////
    
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    nebula.draw();                          // add the orion nebula to the scene
	playerShip.draw();

	/*for each(Ship ship in aiShipList) 
	{
		ship.draw();
	}*/
	ship2.draw();
	ship1.draw();

	for each (Image *heart in heartList) 
	{
		//draW the hearts 
		heart->draw();
	}
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    nebulaTexture.onLostDevice();
    gameTextures.onLostDevice();
	playerShipTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
    gameTextures.onResetDevice();
    nebulaTexture.onResetDevice();
	playerShipTexture.onResetDevice();
    Game::resetAll();
    return;
}
