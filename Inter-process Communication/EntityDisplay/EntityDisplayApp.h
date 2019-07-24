#pragma once

#include "../EntityEditor/IPCHeader.h"
#include <vector>
#include "Application.h"
#include "Renderer2D.h"
#include <windows.h>


class EntityDisplayApp : public aie::Application {
public:
	
	EntityDisplayApp();
	virtual ~EntityDisplayApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	HANDLE				fileHandle;
	HANDLE				countFileHandle;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	// an array of an unknown number of entities
	enum { ENTITY_COUNT = 10 };
	std::vector<Entity> m_entities;

};