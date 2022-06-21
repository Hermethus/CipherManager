#include "cipherutil.h"

CipherUtil::CipherUtil() {
}
CipherUtil::~CipherUtil() {
}


QByteArray CipherUtil::getSHA256(QByteArray input) {
    QByteArray qb;
    qb.append(QCryptographicHash::hash(input, QCryptographicHash::Md5));
    qb.append(QCryptographicHash::hash(input, QCryptographicHash::Sha224));
    return QCryptographicHash::hash(qb, QCryptographicHash::Sha256);
}

QByteArray CipherUtil::encode(QByteArray& plainText, const QByteArray& key) {
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::ECB);
    return encryption.encode(plainText, key);
}
QByteArray CipherUtil::decode(QByteArray& encodedText, QByteArray& key) {
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::ECB);
    QByteArray decodedText = encryption.decode(encodedText, key);
    return encryption.removePadding(decodedText);
}

QByteArray CipherUtil::getPlainJson(QJsonObject* obj) {
    return QJsonDocument(*obj).toJson();
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

QByteArray CipherUtil::readTextFile(QString& filepath) {
    QFile f(filepath);
    f.open(QFile::ReadOnly|QFile::Text);
    QByteArray ret = f.readAll();
    f.close();
    return ret;
}

QJsonObject CipherUtil::toJsonObj(QByteArray& rawJson){
    QJsonDocument qjd = QJsonDocument::fromJson(rawJson);
    return qjd.object();
}

QJsonObject CipherUtil::readPlainFileAndDecode(QString& filepath) {
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

QByteArray CipherUtil::readBinaryFile(QString& filepath) {
    QFile f(filepath);
    f.open(QFile::ReadOnly);
    QDataStream in(&f);
    QByteArray ret;
    in >> ret;
    return ret;
}

QJsonObject CipherUtil::readBinaryFileAndDecode(QString& filepath, QByteArray& key) {
    QByteArray raw = readBinaryFile(filepath);
    QByteArray decoded = decode(raw, key);
    return toJsonObj(decoded);
}
