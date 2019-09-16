#include "ParagraphLocate.h"

/************************************************************************
* 获取定位结果的静态函数，可直接调用
************************************************************************/
int ParagraphLocate::locateOutlineByArticle(JiebaSegment* jieba, const QStringList& stop_words, 
	const QString& artical, const QString& outline, int& start, int& end)
{
	// 段落文本转向量
	ParagraphLocate pl(jieba, stop_words);
	WordVector artical_vector = pl.stringToVector(artical);

	// 每个分段转换为向量
	QStringList paras = outline.split("\n", QString::SkipEmptyParts);
	QList<WordVector> para_vectors;
	foreach (QString para, paras)
	{
		para_vectors.append(pl.stringToVector(para.trimmed()));
	}

	// 词频统计，获取每个词语的重要性


	// 遍历每个分段，获取相似度最大的一段
	double max_simi = 0; // 最大相似度
	int max_simi_index = -1; // 最大相似度的位置
	for (int i = 0; i < para_vectors.size(); i++)
	{
		double simi = pl.getVectorSimilarity(artical_vector, para_vectors.at(i));
		if (simi > max_simi)
		{
			max_simi = simi;
			max_simi_index = i;
		}
	}
	if (max_simi_index > -1)
	{
		QString para = paras.at(max_simi_index);
		start = outline.indexOf(para);
		end = start + para.length();
	}

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
	foreach (QString word, list)
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

/************************************************************************
 * 单纯计算两个向量之间的相似度
 ************************************************************************/
double ParagraphLocate::getVectorSimilarity(const WordVector& a, const WordVector& b)
{
	// 将 a 和 b 统一词包
	QList<int> v1, v2;
	QStringList word_orders;
	for (WordVector::const_iterator it = a.begin(); it != a.end(); it++)
	{
		v1.append(it.value());
		v2.append(b.contains(it.key()) ? b[it.key()] : 0);
		word_orders.append(it.key());
	}
	for (WordVector::const_iterator it = b.begin(); it != b.end(); it++)
	{
		if (a.contains(it.key())) // 这个词语已经在前面出现过了
			continue;
		v1.append(0);
		v2.append(it.value());
		word_orders.append(it.key());
	}

	qDebug() << word_orders;
	qDebug() << v1;
	qDebug() << v2;

	// 计算向量余弦值
	int numerator = 0, denominator1 = 0, denominator2 = 0; // 分子和分母
	for (int i = 0; i < v1.size(); i++)
	{
		numerator += v1.at(i) * v2.at(i);
		denominator1 += v1.at(i) * v1.at(i);
		denominator2 += v2.at(i) * v2.at(i);
	}
	double ans = numerator / sqrt(denominator1 * denominator2);
	qDebug() << "ans:" << ans;
	qDebug() << "-------------------";

	return ans;
}

/************************************************************************
 * 根据TF-IDF（词频-反文档频率）计算两个向量之间的相似度
 ************************************************************************/
double ParagraphLocate::getVectorSimilarity(WordVector a, WordVector b, const QMap<QString, double> TF)
{
	return 0.0;
}
