#include <QtCore/QCoreApplication>
#include <QFile.h>
#include "JiabaSegment.h"

/*
 * ²Î¿¼²©¿Í£ºhttps://www.cnblogs.com/liangjf/p/8283519.html
 */

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString run_path = QCoreApplication::applicationDirPath();
	qDebug() << "run path:" << run_path;

	JiabaSegment* js = new JiabaSegment(run_path + "/dict/");

	return a.exec();
}
