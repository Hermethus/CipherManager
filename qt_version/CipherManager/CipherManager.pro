#-------------------------------------------------
#
# Project created by QtCreator 2022-06-14T08:53:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CipherManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    util/cipherutil.cpp \
    util/qaesencryption.cpp \
    cipherentry.cpp \
    cipherbook.cpp \
    passworddialog.cpp \
    newpassworddialog.cpp \
    changepassworddialog.cpp \
    entrydetaildialog.cpp \
    longinfodialog.cpp

HEADERS += \
        mainwindow.h \
    util/aesni/aesni-enc-cbc.h \
    util/aesni/aesni-enc-ecb.h \
    util/aesni/aesni-key-exp.h \
    util/cipherutil.h \
    util/qaesencryption.h \
    cipherentry.h \
    cipherbook.h \
    passworddialog.h \
    newpassworddialog.h \
    changepassworddialog.h \
    entrydetaildialog.h \
    longinfodialog.h

FORMS += \
        mainwindow.ui \
    passworddialog.ui \
    newpassworddialog.ui \
    changepassworddialog.ui \
    entrydetaildialog.ui \
    longinfodialog.ui

RESOURCES += \
    res.qrc

RC_ICON += icon.ico
RC_FILE += CipherManager.rc