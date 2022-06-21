#include "cipherbook.h"
#include <QDebug>

CipherBook::CipherBook()
    :globalId(1)
{
    this->book = new QMap<int, CipherEntry*>();
}

CipherBook::CipherBook(int globalId)
    :globalId(globalId)
{
    this->book = new QMap<int, CipherEntry*>();
}

CipherBook::CipherBook(QJsonObject& obj) {
    this->globalId = obj["globalId"].toString().toInt();
    this->book = new QMap<int, CipherEntry*>();

    for(auto it=obj.begin(); it!=obj.end(); it++) {
        int id = it.key().toInt();
        if (id == 0) break;
        CipherEntry* entry = new CipherEntry(id);
        QJsonObject properties = it.value().toObject();
        entry->setAllProperty(
                    properties["name"].toString(),
                    properties["otherName"].toString(),
                    properties["username"].toString(),
                    properties["password"].toString(),
                    properties["remarks"].toString(),
                    properties["group"].toString());
        if (entry->getName().length() == 0) {
            this->globalId = 0;
            return;
        }
        this->book->insert(id, entry);
    }
}

CipherBook::~CipherBook() {
    for (auto it = book->begin(); it != book->end(); it++) {
        delete it.value();
    }
    delete book;
}


//增删改查
void CipherBook::add(CipherEntry* obj) {
    book->insert(globalId, obj);
    globalId++;
}

//成功返回0，否则返回-1
void CipherBook::remove(int id) {
    CipherEntry* tmp = this->book->take(id);
    delete tmp;
}

//由于直接进行指针操作，无须在此处额外修改
void CipherBook::modify(int id, CipherEntry* obj) {
    Q_ASSERT(this->book->contains(id));
    Q_ASSERT(obj->getId() == id);
}

CipherEntry* CipherBook::getById(int id){
    return this->book->value(id);
}


QVector<CipherEntry*>* CipherBook::search(const QString& keyWord) const {
    QVector<CipherEntry*>* ret = new QVector<CipherEntry*>();

    if (keyWord.length() == 0) {
        return ret;
    }

    if (keyWord.compare("*") == 0) {
        for (auto it=this->book->begin(); it != this->book->end(); it++) {
            ret->append(it.value());
        }
        return ret;
    }

    for (auto it=this->book->begin(); it != this->book->end(); it++) {
        if ((*it)->containsKeyWord(keyWord)) {
            ret->append(it.value());
        }
    }
    return ret;
}

QJsonObject* CipherBook::toJSON() {
    QJsonObject* ret = new QJsonObject();
    ret->insert(QString("globalId"), QString::number(this->globalId));

    for (auto it=this->book->begin(); it!=this->book->end(); it++) {
        ret->insert(QString::number(it.key()), it.value()->toJson());
    }
    return ret;
}
