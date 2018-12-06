#include "cMainMenu.h"
#include "cGame.h"


void cMainMenu::update(double deltaTime)
{
	if (goButton.getTexture() == NULL) goButton.setTexture(this->goButtonUnpressed);
	if (quitButton.getTexture() == NULL) quitButton.setTexture(this->quitButtonUnpressed);
	
	// Get the x and y of the mouse 
	int x, y;
	Uint32 state = SDL_GetMouseState(&x, &y);
	SDL_Point mousePosition{ x, y };

	// Make a rectangle representing the button (probably don't need to do this every frame)
	SDL_Rect buttonDest = {
		WINDOW_WIDTH / 2 - goButton.getTexture()->getTWidth() / 2,
		WINDOW_HEIGHT / 2 - goButton.getTexture()->getTHeight() / 2 - 50,
		goButton.getTexture()->getTWidth(),
		goButton.getTexture()->getTHeight() };


	// Check if the mouse is inside the button rectangle
	if (SDL_PointInRect(&mousePosition, &buttonDest)) {
		// If it is, change teh texture to the pressed version
		goButton.setTexture(this->goButtonPressed);

		// Deactivate the menu if the left button key is pressed
		if (state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			this->active = false;
			cGame::getInstance()->replay();
		}
	}
	else goButton.setTexture(this->goButtonUnpressed); // If the mouse is not over the button, set the texture

	timeSinceDroppedToMainMenu += deltaTime;
	
	// Only get clicks for the exit button after a certain time has passed
	if (timeSinceDroppedToMainMenu > TIME_TO_DEBOUNCE_EXIT_BUTTON) {

		// Quit button goes in top left corner, offset slightly
		SDL_Rect quitButtonDest = {
			10,
			10,
			quitButton.getTexture()->getTWidth(),
			quitButton.getTexture()->getTHeight() };

		// Check if the mouse is inside the button rectangle
		if (SDL_PointInRect(&mousePosition, &quitButtonDest)) {
			// If it is, change teh texture to the pressed version
			quitButton.setTexture(this->quitButtonPressed);

			// Deactivate the menu if the left button key is pressed
			if (state & SDL_BUTTON(SDL_BUTTON_LEFT)) cGame::getInstance()->loop = false;
		}
		else quitButton.setTexture(this->quitButtonUnpressed); // If the mouse is not over the button, set the texture
	}
}

void cMainMenu::updateGameOver(double deltaTime)
{
	if (replayButton.getTexture() == NULL) replayButton.setTexture(this->replayButtonUnpressed);

	// Get the x and y of the mouse 
	int x, y;
	Uint32 state = SDL_GetMouseState(&x, &y);
	SDL_Point mousePosition{ x, y };

	// Make a rectangle representing the button (probably don't need to do this every frame)
	SDL_Rect buttonDest = {
		WINDOW_WIDTH / 2 - replayButton.getTexture()->getTWidth() / 2,
		WINDOW_HEIGHT / 2 - replayButton.getTexture()->getTHeight() / 2 + 50,
		replayButton.getTexture()->getTWidth(),
		replayButton.getTexture()->getTHeight() };


	// Check if the mouse is inside the button rectangle
	if (SDL_PointInRect(&mousePosition, &buttonDest)) {
		// If it is, change teh texture to the pressed version
		replayButton.setTexture(this->replayButtonPressed);

		// If mouse is being clicked, replay game
		if (state & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			cGame::getInstance()->gameover = false;
			cGame::getInstance()->replay();
		}
	}
	else replayButton.setTexture(this->replayButtonUnpressed); // If the mouse is not over the button, set the texture

	// Quit button goes in top left corner, offset slightly
	SDL_Rect quitButtonDest = {
		10,
		10,
		quitButton.getTexture()->getTWidth(),
		quitButton.getTexture()->getTHeight() };

	// Check if the mouse is inside the button rectangle
	if (SDL_PointInRect(&mousePosition, &quitButtonDest)) {
		// If it is, change teh texture to the pressed version
		quitButton.setTexture(this->quitButtonPressed);

		if (state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			this->active = true; // Re-enable the main menu when button is pressed
			cGame::getInstance()->gameover = false;
			this->timeSinceDroppedToMainMenu = 0; // Start the countdown timer before quit button right underneath can be pressed
		}
	}
	else quitButton.setTexture(this->quitButtonUnpressed); // If the mouse is not over the button, set the texture
}

void cMainMenu::render(SDL_Renderer * theRenderer)
{
	// Render the background
	background.render(theRenderer, NULL, NULL, FPoint{1, 1});

	// Center the button
	SDL_Rect buttonDest = {		WINDOW_WIDTH / 2 - goButton.getTexture()->getTWidth() / 2,
		WINDOW_HEIGHT / 2 - goButton.getTexture()->getTHeight() / 2 - 50,
		goButton.getTexture()->getTWidth(),
		goButton.getTexture()->getTHeight() };

	// Render the button
	goButton.render(theRenderer, NULL, &buttonDest, FPoint() = {1, 1});

	// Quit button goes in top left corner, offset slightly
	SDL_Rect quitButtonDest = {
		10,
		10,
		quitButton.getTexture()->getTWidth(),
		quitButton.getTexture()->getTHeight() };

	// Render the button
	quitButton.render(theRenderer, NULL, &quitButtonDest, FPoint() = { 1, 1 });
}

void cMainMenu::renderGameOver(SDL_Renderer * theRenderer)
{
	// Render the background
	gameOverBackground.render(theRenderer, NULL, NULL, FPoint{ 1, 1 });

	// Center the button
	SDL_Rect buttonDest = {
		WINDOW_WIDTH / 2 - replayButton.getTexture()->getTWidth() / 2,
		WINDOW_HEIGHT / 2 - replayButton.getTexture()->getTHeight() / 2 + 50,
		replayButton.getTexture()->getTWidth(),
		replayButton.getTexture()->getTHeight() };

	// Render the button
	replayButton.render(theRenderer, NULL, &buttonDest, FPoint() = { 1, 1 });

	// Quit button goes in top left corner, offset slightly
	SDL_Rect quitButtonDest = {
		10,
		10,
		quitButton.getTexture()->getTWidth(),
		quitButton.getTexture()->getTHeight() };

	// Render the button
	quitButton.render(theRenderer, NULL, &quitButtonDest, FPoint() = { 1, 1 });
}

cMainMenu::cMainMenu()
{
}


cMainMenu::~cMainMenu()
{
}
