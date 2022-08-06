#ifndef CIPHERBOOK_H
#define CIPHERBOOK_H
#include "cipherentry.h"

#include <QObject>
#include <QMap>
#include <QVector>
#include <QString>
#include <QJsonObject>

class CipherBook : public QObject
{
    Q_OBJECT
public:
    QMap<int, CipherEntry*>* book;

    explicit CipherBook();
    explicit CipherBook(int globalId);
    explicit CipherBook(QJsonObject&);
    ~CipherBook();

    //增删改查
    void add(CipherEntry*);
    void remove(int);
    CipherEntry* getById(int id);
    QVector<CipherEntry*>* search(const QString&) const;
    QJsonObject* toJSON();

    int getGlobalId();
    QString getLastModified();
    void setLastModified();

signals:

public slots:

private:
    int globalId;
    QString lastModified;
};

#endif // CIPHERBOOK_H
