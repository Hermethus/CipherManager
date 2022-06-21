#ifndef LONGINFODIALOG_H
#define LONGINFODIALOG_H

#include <QDialog>

namespace Ui {
class LongInfoDialog;
}

class LongInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LongInfoDialog(const QString& title, QWidget *parent = 0);
    ~LongInfoDialog();

private:
    Ui::LongInfoDialog *ui;
};

#endif // LONGINFODIALOG_H
