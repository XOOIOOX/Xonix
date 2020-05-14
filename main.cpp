#include "QMetaType"
#include "Xonix.h"
#include <QApplication>

Q_DECLARE_METATYPE(PlayerDirection);
auto PlayerDirectionId = qRegisterMetaType<PlayerDirection>();

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(0)));
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
	QApplication a(argc, argv);
	Xonix w;
	w.show();
	return a.exec();
}