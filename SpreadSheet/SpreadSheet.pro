QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cell.cpp \
    findd.cpp \
    gotocell.cpp \
    main.cpp \
    mainwindow.cpp \
    sortDialog.cpp \
    spreadsheet.cpp

HEADERS += \
    cell.h \
    findd.h \
    gotocell.h \
    mainwindow.h \
    sortDialog.h \
    spreadsheet.h

FORMS += \
    gotocell.ui \
    mainwindow.ui \
    sort.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
