#pragma once
#include <QStringList>
#include <QMap>
#include "JiabaSegment.h"

typedef QMap<QString, int> WordVector;

class ParagraphLocate
{
public:
	static int locateOutlineByArticle(JiebaSegment* jieba, const QStringList& stop_words,
		const QString& artical, const QString& outline, int& start, int& end);

private:
	ParagraphLocate(JiebaSegment*& jieba, const QStringList& stop_words);

	QStringList stringToArray(const QString& text);

	WordVector stringToVector(const QString& text);

	double getVectorSimilarity(const WordVector& a, const WordVector& b);

	double getVectorSimilarity(WordVector a, WordVector b, const QMap<QString, double>TF);

private:
	JiebaSegment* jieba;
	QStringList stop_words;
};

