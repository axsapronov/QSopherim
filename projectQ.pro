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
         src/modules/biblequote \
         src/modules/format \
         src/defines \
         src/config \
         src/moduleviewer \
         src/modules/processmodule \
         src/common

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
         src/modules/biblequote \
         src/modules/format \
         src/modules/processmodule \
         src/config \
         src/common

SOURCES  += \
         main.cpp \
         mainwindow.cpp  \
         about.cpp \
         settings.cpp \
         leftpanel.cpp \
         rightpanel.cpp \
         bottompanel.cpp \
         config.cpp \
         leftpanel2.cpp \
         moduleviewer.cpp \
         biblequote.cpp \
         format.cpp \
         filecommon.cpp \
         stringcommon.cpp \
         processmodule.cpp


HEADERS  += \
         mainwindow.h \
         about.h \
         defines.h \
         settings.h \
         leftpanel.h \
         rightpanel.h \
         bottompanel.h \
         config.h \
         leftpanel2.h \
         moduleviewer.h \
         biblequote.h \
         format.h \
         filecommon.h \
         stringcommon.h \
         processmodule.h

FORMS    += \
         mainwindow.ui \
         about.ui \
         settings.ui \
         leftpanel.ui \
         rightpanel.ui \
         bottompanel.ui \
         leftpanel2.ui \
         moduleviewer.ui

RESOURCES += \
    resources/resources.qrc

TRANSLATIONS += \
    resources/lang/projectQ_ru.ts \
    resources/lang/projectQ_de.ts \
    resources/lang/projectQ_fr.ts
