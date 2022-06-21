#include "newpassworddialog.h"
#include "ui_newpassworddialog.h"
#include <QMessageBox>

NewPasswordDialog::NewPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPasswordDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("创建密码");
    connect(this->ui->cancelButton, this->ui->cancelButton->clicked, this, reject);
    connect(this->ui->OKButton, this->ui->OKButton->clicked, this, check);
}

NewPasswordDialog::~NewPasswordDialog()
{
    delete ui;
}

void NewPasswordDialog::check() {
    QString input = this->ui->inputPasswordEdit->text();
    QString confirm = this->ui->confirmPasswordEdit->text();

    if (!input.length() || !confirm.length()) {
        QMessageBox::critical(this, "错误", "密码不能为空！");
        return;
    }
    if (input.compare(confirm)) {
        QMessageBox::critical(this, "错误", "两次输入的密码不一致！");
        return;
    }
    accept();
}

QString NewPasswordDialog::getPassword() {
    return this->ui->inputPasswordEdit->text();
}
