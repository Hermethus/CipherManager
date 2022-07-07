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
    int globalId;
    QMap<int, CipherEntry*>* book;

    explicit CipherBook();
    explicit CipherBook(int globalId);
    explicit CipherBook(QJsonObject&);
    ~CipherBook();

    void add(CipherEntry*);
    void remove(int);
    CipherEntry* getById(int id);
    QVector<CipherEntry*>* search(const QString&) const;
    QJsonObject* toJSON();

signals:

public slots:
};

#endif // CIPHERBOOK_H
