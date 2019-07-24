#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "IPCHeader.h"
#include <windows.h>



class EntityEditorApp : public aie::Application {
public:

	EntityEditorApp();
	virtual ~EntityEditorApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	HANDLE				fileHandle;
	HANDLE				countFileHandle;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	// define a block of entities that should be shared
	enum { ENTITY_COUNT = 10 };
	Entity m_entities[ENTITY_COUNT];

};