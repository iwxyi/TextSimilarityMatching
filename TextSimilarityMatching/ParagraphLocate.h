#pragma once
#include <QStringList>
#include <QMap>
#include "JiabaSegment.h"

typedef QMap<QString, int> WordVector;

class ParagraphLocate
{
public:
	static int locateOutlineByArticle(JiebaSegment* jieba, const QStringList& stop_words,
		const QString& artical, const QString& outline, int& start, int& ends);

private:
	ParagraphLocate(JiebaSegment*& jieba, const QStringList& stop_words);

	QStringList stringToArray(const QString& text);

	WordVector stringToVector(const QString& text);

private:
	JiebaSegment* jieba;
	QStringList stop_words;
};

