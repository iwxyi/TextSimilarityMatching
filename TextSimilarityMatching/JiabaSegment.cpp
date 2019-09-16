#include "JiabaSegment.h"


JiabaSegment::JiabaSegment(QString dict_path)
{
	this->file_path = dict_path;
	init();
}

JiabaSegment::~JiabaSegment()
{
}

bool JiabaSegment::init()
{
	QDir dir(file_path);
	if (!dir.exists())
	{
		qDebug() << QStringLiteral("词库路径：") << file_path << QStringLiteral("不存在");
		return false;
	}

	const QString DICT_PATH = file_path + "jieba.dict.utf8";
	const QString HMM_PATH = file_path + "hmm_model.utf8";
	const QString USER_DICT_PATH = file_path + "user.dict.utf8";
	const QString IDF_PATH = file_path + "idf.utf8";
	const QString STOP_WORD_PATH = file_path + "stop_words.utf8";

	jieba = new cppjieba::Jieba(
		DICT_PATH.toLatin1().data(),
		HMM_PATH.toLatin1().data(),
		USER_DICT_PATH.toLatin1().data(),
		IDF_PATH.toLatin1().data(),
		STOP_WORD_PATH.toLatin1().data()
	);

	qDebug() << QStringLiteral("初始化成功");
	return true;
}

QStringList JiabaSegment::WordSegment(QString text)
{
	return QStringList();
}
