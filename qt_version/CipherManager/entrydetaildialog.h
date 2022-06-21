#ifndef ENTRYDETAILDIALOG_H
#define ENTRYDETAILDIALOG_H

#include "cipherentry.h"
#include <QDialog>

namespace Ui {
class EntryDetailDialog;
}

class EntryDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDetailDialog(int id, QStringList* groupList, QWidget *parent = 0);
    explicit EntryDetailDialog(CipherEntry* entry, QStringList* groupList, QWidget *parent = 0);
    ~EntryDetailDialog();

    CipherEntry* getEntry();

public slots:
    void check();

private:
    Ui::EntryDetailDialog *ui;
    CipherEntry* entry;
    QStringList* groupList;

    void mySetupUI();
};

#endif // ENTRYDETAILDIALOG_H
