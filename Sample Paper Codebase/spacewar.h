// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "planet.h"
#include "ship.h"
#include "playership.h"
#include <list>
using namespace std;
//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
    TextureManager nebulaTexture;   // nebula texture
    TextureManager gameTextures;    // game texture
	TextureManager playerShipTexture;
	Ship ship1, ship2;
    Planet  planet;         // the planet
    Image   nebula;         // backdrop image
	PlayerShip    playerShip;

	// GAME EDITED
	//must use namepsace std if lazy to code std:: list<Ship*> aiShipList;
	list<Ship*> aiShipList;
	TextureManager aITexture;

	TextureManager heartTexture;
	Image *heart;
	list<Image*> heartList;
	float heartScale = 0.3f;
	///////////////////////////////////////////////////////////////////////



public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
