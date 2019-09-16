#pragma once
#include <QStringList>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include "jiaba\\include\\Jieba.hpp"

using namespace std;

class JiabaSegment
{
public:
	JiabaSegment(QString dict_path);
	~JiabaSegment();

	bool init();

	QStringList WordSegment(QString text);

private:
	QString file_path;

	cppjieba::Jieba* jieba;
};

