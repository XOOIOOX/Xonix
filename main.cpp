#include "Xonix.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(0)));
	QApplication a(argc, argv);
	Xonix w;
	w.show();
	return a.exec();
}