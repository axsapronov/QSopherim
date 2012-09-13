#-------------------------------------------------
#
# Project created by QtCreator 2012-09-10T23:38:45
#
#-------------------------------------------------

QT       += core gui

TARGET = projectQ
TEMPLATE = app
DESTDIR     = build/bin
OBJECTS_DIR = build/obj
MOC_DIR     = build/moc
RCC_DIR     = build/rc
UI_DIR      = build/ui

DEPENDPATH += \
         src/dialogs/about \
         src/dialogs/settings \
         src/panel/leftpanel/ \
         src/panel/rightpanel/ \
         src/panel/bottompanel/ \
         src/main \
         src/defines \
         src/config \
         src/moduleviewer

INCLUDEPATH += \
         src/main \
         src/dialogs/about \
         src/dialogs/settings \
         src/panel/leftpanel/ \
         src/panel/rightpanel/ \
         src/panel/bottompanel/ \
         src/dialogs/lansettings \
         src/moduleviewer \
         src/defines \
         src/config

SOURCES  += \
         main.cpp \
         mainwindow.cpp  \
         about.cpp \
         settings.cpp \
         leftpanel.cpp \
         rightpanel.cpp \
         bottompanel.cpp \
         config.cpp \
    src/panel/leftpanel/leftpanel2.cpp \
    src/moduleviewer/moduleviewer.cpp

HEADERS  += \
         mainwindow.h \
         about.h \
         defines.h \
         settings.h \
         leftpanel.h \
         rightpanel.h \
         bottompanel.h \
         config.h \
    src/panel/leftpanel/leftpanel2.h \
    src/moduleviewer/moduleviewer.h

FORMS    += \
         mainwindow.ui \
         about.ui \
         settings.ui \
         leftpanel.ui \
         rightpanel.ui \
         bottompanel.ui \
    src/panel/leftpanel/leftpanel2.ui \
    src/moduleviewer/moduleviewer.ui

RESOURCES += \
    resources/resources.qrc

TRANSLATIONS += \
    resources/lang/projectQ_ru.ts \
    resources/lang/projectQ_de.ts \
    resources/lang/projectQ_fr.ts
