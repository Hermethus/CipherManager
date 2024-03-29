﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QWidget>
#include <QVector>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QKeyEvent>
#include <QLabel>

#include "cipherbook.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newFile();
    void openCipher();
    void openPlain();
    void save();
    void saveAsCipher();
    void saveAsPlain();
    void closeFile();
    void exitExe();

    void openCipherByFilename(const QString& filename);
    void openPlainByFilename(const QString& filename);

    void changePassword();
    void addEntry();
    void alterEntry();
    void deleteEntry();

    void help();
    void about();

    void copyUsername();
    void copyPassword();

    void search();
    void clear();

    void clickedAtIndex(const QModelIndex&);

private:
    Ui::MainWindow *ui;
    CipherBook* cipherBook;
    QString* filepath;
    QByteArray* key;
    QStringList* groupList;
    bool isSaved;

    QLabel* globalIdLabel;
    QLabel* tipsLabel;
    QLabel* lastModifiedLabel;

    void mySetupUi();
    void setupActions();

    //UI按键
    void alterActionsOnOpenFile();
    void alterActionsOnCloseFile();
    void alterActionsOnSelect();
    void alterActionsOnClear();
    void updateModifiedWhenSave();
    void clearRight();

    void closeEvent(QCloseEvent*);

    //左侧边栏
    void updateSearchTreeView(QVector<CipherEntry*>*);
    void clearSearchTreeView();
    void renewGroupList();
    void renewGroupList(const QString& group);

    void setCurrentPath(const QString* path);

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    void simpleInfoBox(const QString& text);
    void actionSuccessTips(const QString& text);
};

#endif // MAINWINDOW_H
