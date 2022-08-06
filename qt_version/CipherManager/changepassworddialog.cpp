#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"
#include "util/cipherutil.h"

#include <QMessageBox>

ChangePasswordDialog::ChangePasswordDialog(const QByteArray& oldPassword, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog),
    oldPassword(oldPassword)
{
    ui->setupUi(this);
    this->setWindowTitle("修改密码");
    connect(this->ui->cancelButton, this->ui->cancelButton->clicked, this, reject);
    connect(this->ui->OKButton, this->ui->OKButton->clicked, this, check);
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::check() {
    QString old = ui->oldPasswordEdit->text();
    QString input = ui->newPasswordEdit->text();
    QString confirm = ui->confirmPasswordEdit->text();

    QByteArray old256 = CipherUtil::getSaveHash(old.toLocal8Bit());

    if (!input.length() || !confirm.length() || !old.length()) {
        QMessageBox::critical(this, "错误", "密码不能为空！");
        return;
    }
    if (old256 != oldPassword) {
        QMessageBox::critical(this, "错误", "旧密码输入错误！");
        return;
    }
    if (input.compare(confirm)) {
        QMessageBox::critical(this, "错误", "两次输入的密码不一致！");
        return;
    }
    accept();
}

QString ChangePasswordDialog::getPassword() {
    return ui->newPasswordEdit->text();
}
