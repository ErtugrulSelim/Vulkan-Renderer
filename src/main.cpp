#include "app.h"

int main() {

	App* myApp = new App(1080, 1080, true);

	myApp->run();
	delete myApp;

	return 0;
}