#ifndef NEWPASSWORDDIALOG_H
#define NEWPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class NewPasswordDialog;
}

class NewPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPasswordDialog(QWidget *parent = 0);

    QString getPassword();
    ~NewPasswordDialog();

public slots:
    void check();

private:
    Ui::NewPasswordDialog *ui;
};

#endif // NEWPASSWORDDIALOG_H
