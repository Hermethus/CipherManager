#ifndef CIPHERENTRY_H
#define CIPHERENTRY_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class CipherEntry : public QObject
{
    Q_OBJECT
public:
    explicit CipherEntry();
    explicit CipherEntry(int id);

    int getId();
    QString getName();
    QString getOtherName();
    QString getUsername();
    QString getPassword();
    QString getRemarks();
    QString getGroup();
    bool containsKeyWord(const QString&) const;
    void setId(int);
    void setAllProperty(const QString& name, const QString& otherName, const QString& username,
                        const QString& password, const QString& remarks, const QString& group);
    QJsonObject toJson();

private:
    int id;
    QString name;
    QString otherName;
    QString username;
    QString password;
    QString remarks;
    QString group;

signals:

public slots:
};

#endif // CIPHERENTRY_H
