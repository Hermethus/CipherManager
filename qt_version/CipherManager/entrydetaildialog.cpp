#include "entrydetaildialog.h"
#include "ui_entrydetaildialog.h"

#include <QMessageBox>

EntryDetailDialog::EntryDetailDialog(int id, QStringList* groupList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDetailDialog),
    entry(new CipherEntry(id)),
    groupList(groupList)
{
    ui->setupUi(this);
    this->setWindowTitle("添加");
    mySetupUI();
}

EntryDetailDialog::EntryDetailDialog(CipherEntry* entry, QStringList* groupList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDetailDialog),
    entry(entry),
    groupList(groupList)
{
    ui->setupUi(this);
    this->setWindowTitle("修改");
    mySetupUI();
}

void EntryDetailDialog::mySetupUI() {
    connect(this->ui->cancelButton, this->ui->cancelButton->clicked, this, reject);
    connect(this->ui->OKButton, this->ui->OKButton->clicked, this, check);

    ui->nameEdit->setText(entry->getName());
    ui->otherNameEdit->setText(entry->getOtherName());
    ui->usernameEdit->setText(entry->getUsername());
    ui->passwordEdit->setText(entry->getPassword());
    ui->confirmEdit->setText(entry->getPassword());
    ui->groupEdit->addItems(*groupList);
    ui->groupEdit->setCurrentText(entry->getGroup());
    ui->remarksEdit->setPlainText(entry->getRemarks());
}

CipherEntry* EntryDetailDialog::getEntry() {
    return entry;
}

void EntryDetailDialog::check() {
    QString name = ui->nameEdit->text();
    QString password = ui->passwordEdit->text();
    QString group = ui->groupEdit->currentText();

    if (name.length() == 0) {
        QMessageBox::critical(this, "错误", "标识不能为空！");
        return;
    }
    if (password.compare(ui->confirmEdit->text())) {
        QMessageBox::critical(this, "错误", "两次输入的密码不一致！");
        return;
    }
    if (group.compare("未分组") == 0) group.clear();

    entry->setAllProperty(name, ui->otherNameEdit->text(),
                          ui->usernameEdit->text(), password,
                          ui->remarksEdit->document()->toPlainText(), group);
    accept();
}


EntryDetailDialog::~EntryDetailDialog()
{
    delete ui;
}
