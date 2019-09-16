#include "ParagraphLocate.h"

/************************************************************************
* 获取定位结果的静态函数，可直接调用
************************************************************************/
int ParagraphLocate::locateOutlineByArticle(JiebaSegment* jieba, const QStringList& stop_words,
	const QString& artical, const QString& outline, int& start, int& ends)
{
	ParagraphLocate pl(jieba, stop_words);
	WordVector artical_vector = pl.stringToVector(artical);
	QStringList paras = outline.split("\n", QString::SkipEmptyParts);


	return 0;
}

/************************************************************************
* 构造函数
************************************************************************/
ParagraphLocate::ParagraphLocate(JiebaSegment*& jieba, const QStringList& stop_words) :
	jieba(jieba), stop_words(stop_words)
{
}

/************************************************************************
* 将字符串转换成词语词组
************************************************************************/
QStringList ParagraphLocate::stringToArray(const QString& text)
{
	QStringList words = jieba->WordSegment(text);
	for (int i = 0; i < words.size(); i++) // 遍历章节词组的每一个
	{
		if (stop_words.contains(words.at(i)))
		{
			words.removeAt(i--);
		}
	}
	return words;
}

/************************************************************************
* 将字符串转换成词语向量
* map 格式：["名称" => 出现次数]
************************************************************************/
WordVector ParagraphLocate::stringToVector(const QString& text)
{
	WordVector map;
	WordVector::iterator it;
	QStringList list = stringToArray(text);
	for each (QString word in list)
	{
		if ((it = map.find(word)) != map.end()) // 如果这个词语存在，值+1
		{
			(*it)++;
		}
		else // 如果这个词语不存在，添加并设置值为1
		{
			map.insert(word, 1);
		}
	}

	return map;
}