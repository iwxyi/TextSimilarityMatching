#pragma once
#include <QStringList>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include "jiaba\\include\\Jieba.hpp"

using namespace std;

class JiebaSegment
{
public:
	JiebaSegment(QString dict_path);
	~JiebaSegment();

	bool init();

	QStringList WordSegment(QString text);

private:
	QString file_path;
	bool inited;

	cppjieba::Jieba* jieba;
};

