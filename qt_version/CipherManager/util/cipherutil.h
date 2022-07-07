#ifndef CIPHERUTIL_H
#define CIPHERUTIL_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <QFile>
#include <QDataStream>

#include "qaesencryption.h"

class CipherUtil
{
public:
    CipherUtil();
    ~CipherUtil();
    static QByteArray getSHA256(QByteArray input);

    static void savePlainJson(QJsonObject* obj, QString& filepath);
    static void encodeAndSave(QJsonObject* obj, const QByteArray& key, const QString& filepath);

    static QJsonObject readBinaryFileAndDecode(const QString&, QByteArray& key);
    static QJsonObject readPlainFileAndDecode(const QString&);

    static QJsonObject toJsonObj(QByteArray&);
    static QByteArray getPlainJson(QJsonObject*);

private:
    static QByteArray encode(QByteArray& plainText, const QByteArray& key);
    static QByteArray decode(QByteArray& encodedText, QByteArray& key);

    static void saveTextToFile(const QByteArray&, QString&);
    static void saveBytesToFile(const QByteArray&, const QString&);

    static QByteArray readBinaryFile(const QString&);
    static QByteArray readTextFile(const QString&);

};

#endif // CIPHERUTIL_H
