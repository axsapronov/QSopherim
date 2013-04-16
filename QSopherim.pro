#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T17:42:05
#
#-------------------------------------------------

QT       += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = QSopherim
TEMPLATE    = app
DESTDIR     = build/bin
OBJECTS_DIR = build/obj
MOC_DIR     = build/moc
RCC_DIR     = build/rc
UI_DIR      = build/ui


DEPENDPATH += \
        src/model \
        src/main \
        src/controller \
        src/observer \
        src/observable \
        src/debug \
        src/view \
        src/modelstatic

INCLUDEPATH += \
        src/model \
        src/main \
        src/view \
        src/modelstatic \
        src/controller \
        src/observer \
        src/observable \
        src/debug

SOURCES += main.cpp\
        mainwindow.cpp \
    src/model/abstractmodel.cpp \
    src/controller/abstractcontroller.cpp \
    src/observer/observer.cpp \
    src/observable/observable.cpp \
    src/view/abstractview.cpp \
    src/debug/debughelper.cpp \
    src/model/modelstatic/moduleinfo.cpp

HEADERS  += mainwindow.h \
    src/model/abstractmodel.h \
    src/controller/abstractcontroller.h \
    src/observer/observer.h \
    src/observable/observable.h \
    src/view/abstractview.h \
    src/debug/debughelper.h \
    src/model/modelstatic/moduleinfo.h


OTHER_FILES += \
    resources/view/mainwindow.qml

RESOURCES += \
    resources/resources.qrc

TRANSLATIONS += \
        resources/lang/QSopherim_ru.ts \
        resources/lang/QSopherim_de.ts \
        resources/lang/QSopherim_fr.ts

RC_FILE += resources/icon.rc
OTHER_FILES += resources/icon.rc
