#ifndef CIPHERUTIL_H
#define CIPHERUTIL_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <QFile>
#include <QDataStream>

#include "qaesencryption.h"

const static QByteArray iv = QCryptographicHash::hash(QByteArray("iv"), QCryptographicHash::Md5);

class CipherUtil
{
public:
    CipherUtil();
    ~CipherUtil();
    static QByteArray getSaveHash(QByteArray input);

    //保存接口
    static void savePlainJson(QJsonObject* obj, QString& filepath);
    static void encodeAndSave(QJsonObject* obj, const QByteArray& key, const QString& filepath);

    //读取接口
    static QJsonObject readBinaryFileAndDecode(const QString& filepath, QByteArray& key);
    static QJsonObject readPlainFileAndDecode(const QString& filepath);

private:
    //加密解密
    static QByteArray encode(QByteArray& plainText, const QByteArray& key);
    static QByteArray decode(QByteArray& encodedText, const QByteArray& key);

    //JSON对象与字符串的转换
    static QJsonObject toJsonObj(QByteArray& rawJson);
    static QByteArray getPlainJson(QJsonObject* obj);

    //保存文件
    static void saveTextToFile(const QByteArray&, QString&);
    static void saveBytesToFile(const QByteArray&, const QString&);

    //读取文件
    static QByteArray readBinaryFile(const QString&);
    static QByteArray readTextFile(const QString&);

};

#endif // CIPHERUTIL_H
