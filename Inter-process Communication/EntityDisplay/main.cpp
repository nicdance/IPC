#include "EntityDisplayApp.h"

int main() {
	
	auto app = new EntityDisplayApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}