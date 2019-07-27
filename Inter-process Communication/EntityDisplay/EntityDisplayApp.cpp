#include "EntityDisplayApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>

EntityDisplayApp::EntityDisplayApp() {

}

EntityDisplayApp::~EntityDisplayApp() {

}

bool EntityDisplayApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	setBackgroundColour(1, 1, 1);

	// gain access to a named shared memory block that already exists 
	fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, 
								FALSE, 
								mem_block);
	
	// gain access to a named shared memory block that already exists 
	countFileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS,
		FALSE,
		count_mem_block);

	return true;
}

void EntityDisplayApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;

	// close the shared file 
	CloseHandle(fileHandle);
	CloseHandle(countFileHandle);
}

void EntityDisplayApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();



	// Check to make sure Handles access have to a named shared memory block
	// This allows the display to run if the server hasn't loaded yet. The display will  attempt to reconnect if unable to.
	if (fileHandle != NULL && countFileHandle!= NULL) {
		// Sets up a pointer to memory for the shared data
		int* count = (int*)MapViewOfFile(countFileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
		Entity* data = (Entity*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Entity) * *count);

		// Clear current entity list and then  reads in each entity from the shared data location.
		m_entities.clear();
		for (int i = 0; i < *count; i++)
		{
			m_entities.push_back(data[i]);
		}

		// unmap the memory block since we're done with it 
		UnmapViewOfFile(data);
		UnmapViewOfFile(count);
	}
	else { // Retry accessing the named shared memory blocks

		// gain access to a named shared memory block that already exists 
		fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS,
			FALSE,
			mem_block);

		// gain access to a named shared memory block that already exists 
		countFileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS,
			FALSE,
			count_mem_block);
	}
}



void EntityDisplayApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw entities
	for (auto& entity : m_entities) {
		m_2dRenderer->setRenderColour(entity.r, entity.g, entity.b, 1.0f);
		m_2dRenderer->drawBox(entity.x, entity.y, entity.size, entity.size, entity.rotation);
	}
	
	// output some text, uses the last used colour

	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}