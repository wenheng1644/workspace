QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += D:\MyGitHub\workspace\CppExcise\Cpp_Primer\DrawCardApp\source\

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../server/CardPool/cardpool.cpp \
    ../../server/drawCard/draw.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../server/CardPool/cardpool.h \
    ../../server/drawCard/draw.h \
    ../../server/drawCard/drawcard_Data.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../comm/config/drawCardInfo.csv \
    ../../comm/config/rare_quality_pro.csv

#RESOURCES += \
#    picture_src.qrc
