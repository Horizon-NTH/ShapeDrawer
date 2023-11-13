#include "../include/ShapeDrawer.h"

int main()
{
	ShapeDrawer application;
	application.get_dataManager()->load("../assets/data.txt");
	application.run();
	return 0;
}