#include <QtCore/QCoreApplication>
#include <QFile.h>
#include "JiabaSegment.h"
#include "ParagraphLocate.h"

/*
 * 参考博客（TF-IDF）：https://www.cnblogs.com/liangjf/p/8283519.html
 * 测试小说（斗罗大陆）：https://www.81xzw.com/book/110171/
 */

QString readTextFile(QString path)
{
	QFile file(path);
	file.open(QFile::ReadOnly | QFile::Text);
	return file.readAll();
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	const QString run_path = QCoreApplication::applicationDirPath();
	const QStringList stop_words = readTextFile(run_path + "/stopwords.txt")
		.split("\n", QString::SkipEmptyParts) << "　" << " " << "\n";
	JiebaSegment* jieba = new JiebaSegment(run_path + "/dict/");
	const QString artical = readTextFile(run_path + "/article.txt");
	const QString paragraph = readTextFile(run_path + "/paragraph.txt");

	int start = -1, end = -1;
	ParagraphLocate::locateOutlineByArticle(jieba, stop_words, artical, paragraph, start, end);

	return a.exec();
}
