#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>
#include <QByteArray>

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(const QByteArray& oldPassword, QWidget *parent = 0);

    QString getPassword();
    ~ChangePasswordDialog();

public slots:
    void check();

private:
    Ui::ChangePasswordDialog *ui;
    QByteArray oldPassword;
};

#endif // CHANGEPASSWORDDIALOG_H
