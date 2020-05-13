#include "Xonix.h"
#include <QtWidgets/QApplication>
#include "QMetaType"

Q_DECLARE_METATYPE(PlayerDirection);
auto PlayerDirectionId = qRegisterMetaType<PlayerDirection>();

int main(int argc, char* argv[])
{
	
	srand(static_cast<unsigned int>(time(0)));
	QApplication a(argc, argv);
	Xonix w;
	w.show();
	return a.exec();
}