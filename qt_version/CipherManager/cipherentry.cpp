#include "cipherentry.h"

CipherEntry::CipherEntry(): QObject(nullptr),
    id(0),
    name(QString("")),
    otherName(QString("")),
    username(QString("")),
    password(QString("")),
    remarks(QString("")),
    group(QString(""))
{
}

CipherEntry::CipherEntry(int id): QObject(nullptr),
    id(id),
    name(QString("")),
    otherName(QString("")),
    username(QString("")),
    password(QString("")),
    remarks(QString("")),
    group(QString(""))
{
    Q_ASSERT(id > 0);
}

int CipherEntry::getId() {
    return this->id;
}
QString CipherEntry::getName() {
    return this->name;
}
QString CipherEntry::getOtherName() {
    return this->otherName;
}
QString CipherEntry::getUsername() {
    return this->username;
}
QString CipherEntry::getPassword() {
    return this->password;
}
QString CipherEntry::getRemarks() {
    return this->remarks;
}
QString CipherEntry::getGroup() {
    return this->group;
}

bool CipherEntry::containsKeyWord(const QString& keyWord) const {
    return (this->name).contains(keyWord, Qt::CaseInsensitive) ||
            (this->otherName).contains(keyWord, Qt::CaseInsensitive) ||
            (this->group).contains(keyWord, Qt::CaseInsensitive);
}

void CipherEntry::setId(int id) {
    this->id = id;
}

void CipherEntry::setAllProperty(const QString& name, const QString& otherName,const QString& username,
                                 const QString& password, const QString& remarks, const QString& group) {
    this->name = name;
    this->otherName = otherName;
    this->username = username;
    this->password = password;
    this->remarks = remarks;
    this->group = group;
}

QJsonObject CipherEntry::toJson() {
    QJsonObject ret;
    ret.insert(QString("name"), name);
    ret.insert(QString("otherName"), otherName);
    ret.insert(QString("username"), username);
    ret.insert(QString("password"), password);
    ret.insert(QString("remarks"), remarks);
    ret.insert(QString("group"), group);
    return ret;
}
