#include "cipherentry.h"

#include <QDate>
#include <QTime>

CipherEntry::CipherEntry(): QObject(nullptr),
    id(0),
    name(QString("")),
    otherName(QString("")),
    username(QString("")),
    password(QString("")),
    remarks(QString("")),
    group(QString(""))
{
    this->setLastModified();
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
    this->setLastModified();
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
QString CipherEntry::getLastModified() {
    return this->lastModified;
}

bool CipherEntry::containsKeyWord(const QString& keyWord) const {
    return (this->name).contains(keyWord, Qt::CaseInsensitive) ||
            (this->otherName).contains(keyWord, Qt::CaseInsensitive) ||
            (this->group).contains(keyWord, Qt::CaseInsensitive);
}

void CipherEntry::setId(int id) {
    this->id = id;
}
void CipherEntry::setLastModified() {
    QString data = QDate::currentDate().toString("yyyy-M-d");
    QString time = QTime::currentTime().toString("hh:mm:ss");
    this->lastModified = data.append(" ").append(time);
}

void CipherEntry::setAllProperty(const QString& name, const QString& otherName,const QString& username,
                                 const QString& password, const QString& remarks, const QString& group,
                                 const QString& lastModified) {
    this->name = name;
    this->otherName = otherName;
    this->username = username;
    this->password = password;
    this->remarks = remarks;
    this->group = group;
    if (lastModified.length() == 0) {
        //如果没有传入这个参数，说明是修改
        this->setLastModified();
    } else {
        //传入这个参数，说明是读取
        this->lastModified = lastModified;
    }
}

QJsonObject CipherEntry::toJson() {
    QJsonObject ret;
    ret.insert(QString("name"), name);
    ret.insert(QString("otherName"), otherName);
    ret.insert(QString("username"), username);
    ret.insert(QString("password"), password);
    ret.insert(QString("remarks"), remarks);
    ret.insert(QString("group"), group);
    ret.insert(QString("lastModified"), lastModified);
    return ret;
}
