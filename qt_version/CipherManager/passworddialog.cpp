#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <QMessageBox>

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("请输入密码");
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

QString PasswordDialog::getPassword() {
    QString ret = this->ui->passwordEdit->text();
    if (!ret.length()) {
        QMessageBox::critical(this, "错误", "密码不能为空！");
    }
    return ret;
}
