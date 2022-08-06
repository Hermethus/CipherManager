#include "cipherutil.h"

#include <QDebug>

CipherUtil::CipherUtil() {
}
CipherUtil::~CipherUtil() {
}


QByteArray CipherUtil::getSaveHash(QByteArray input) {
    QByteArray qb;
    qb.append(QCryptographicHash::hash(input, QCryptographicHash::Keccak_512));
    qb.append(QCryptographicHash::hash(input, QCryptographicHash::RealSha3_512));
    return QCryptographicHash::hash(qb, QCryptographicHash::Sha3_256);
}

QByteArray CipherUtil::encode(QByteArray& plainText, const QByteArray& key) {
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::OFB);
    return encryption.encode(plainText, key, iv);
}
QByteArray CipherUtil::decode(QByteArray& encodedText, const QByteArray& key) {
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::OFB);
    QByteArray decodedText = encryption.decode(encodedText, key, iv);
    return encryption.removePadding(decodedText);
}

void CipherUtil::saveTextToFile(const QByteArray& content, QString& filepath) {
    QFile f(filepath);
    f.open(QFile::WriteOnly|QFile::Text);
    f.write(content);
    f.close();
}

void CipherUtil::savePlainJson(QJsonObject* obj, QString& filepath) {
    QByteArray pJson = getPlainJson(obj);
    saveTextToFile(pJson, filepath);
}

void CipherUtil::encodeAndSave(QJsonObject* obj, const QByteArray& key, const QString& filepath) {
    QByteArray jsonBytes = CipherUtil::getPlainJson(obj);
    QByteArray encoded = CipherUtil::encode(jsonBytes, key);
    CipherUtil::saveBytesToFile(encoded, filepath);
}

QByteArray CipherUtil::readTextFile(const QString& filepath) {
    QFile f(filepath);
    f.open(QFile::ReadOnly|QFile::Text);
    QByteArray ret = f.readAll();
    f.close();
    return ret;
}

//将JSON对象转为JSON字符串
QByteArray CipherUtil::getPlainJson(QJsonObject* obj) {
    return QJsonDocument(*obj).toJson();
}
//将JSON字符串转为JSON对象
QJsonObject CipherUtil::toJsonObj(QByteArray& rawJson) {
    QJsonDocument qjd = QJsonDocument::fromJson(rawJson);
    return qjd.object();
}

QJsonObject CipherUtil::readPlainFileAndDecode(const QString& filepath) {
    QByteArray raw = readTextFile(filepath);
    return toJsonObj(raw);
}

void CipherUtil::saveBytesToFile(const QByteArray& content, const QString& filepath) {
    QFile f(filepath);
    f.open(QFile::WriteOnly|QFile::Truncate);
    QDataStream out(&f);
    out << content;
    f.close();
}

QByteArray CipherUtil::readBinaryFile(const QString& filepath) {
    QFile f(filepath);
    f.open(QFile::ReadOnly);
    QDataStream in(&f);
    QByteArray ret;
    in >> ret;
    return ret;
}

QJsonObject CipherUtil::readBinaryFileAndDecode(const QString& filepath, QByteArray& key) {
    QByteArray raw = readBinaryFile(filepath);
    QByteArray decoded = decode(raw, key);
    return toJsonObj(decoded);
}
