#-------------------------------------------------
#
# Project created by QtCreator 2012-09-10T23:38:45
#
#-------------------------------------------------

QT       += core gui xml

TARGET      = QSopherim
TEMPLATE    = app
DESTDIR     = build/bin
OBJECTS_DIR = build/obj
MOC_DIR     = build/moc
RCC_DIR     = build/rc
UI_DIR      = build/ui

DEPENDPATH += \
        src/gui/dialogs/about \
        src/gui/dialogs/settings \
        src/gui/panel/leftpanel/ \
        src/gui/panel/rightpanel/ \
        src/gui/panel/bottompanel/ \
        src/gui/dialogs/lansettings \
        src/gui/dialogs/managermodules \
        src/gui/dialogs/font \
        src/gui/dialogs/find \
        src/main \
        src/modules/biblequote \
        src/modules/biblemodule \
        src/modules/biblequote/biblequotedictmodule\
        src/modules/format \
        src/modules/metainfo \
        src/modules/ \
        src/defines \
        src/config \
        src/gui/view/moduleviewer \
        src/modules/processmodule \
        src/common \
        src/core \
        src/core/verse \
        src/core/verse/versification \
        src/core/link \
        src/xmlread/ \
        src/view/module \
        src/gui/note

INCLUDEPATH += \
        src/main \
        src/gui/dialogs/about \
        src/gui/dialogs/settings \
        src/gui/panel/leftpanel/ \
        src/gui/panel/rightpanel/ \
        src/gui/panel/bottompanel/ \
        src/gui/dialogs/lansettings \
        src/gui/dialogs/find \
        src/gui/dialogs/font \
        src/gui/dialogs/managermodules \
        src/modules/metainfo \
        src/gui/view/moduleviewer \
        src/defines \
        src/modules/biblequote \
        src/modules/biblemodule \
        src/modules/biblequote/biblequotedictmodule\
        src/modules/format \
        src/modules/processmodule \
        src/config \
        src/modules/ \
        src/common \
        src/core \
        src/core/verse \
        src/core/verse/versification \
        src/core/link \
        src/view/module \
        src/gui/view/module \
        src/xmlread/ \
        src/gui/note

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
        strongcommon.cpp \
        processmodule.cpp \
        biblemodule.cpp \
        metainfo.cpp \
        debughelper.cpp \
        chapter.cpp \
        book.cpp \
        range.cpp \
        ranges.cpp \
        rangeenum.cpp \
        textrange.cpp \
        textranges.cpp \
        verse.cpp \
        versification.cpp \
        versificationextendeddata.cpp \
        versification_kjv.cpp \
        versification_biblequote.cpp \
        bookv11n.cpp \
        strongurl.cpp \
        verseurl.cpp \
        verseurlrange.cpp \
        biblelink.cpp \
        url.cpp \
        qsopherimmodule.cpp \
        qsopherimmodulelist.cpp \
        noteeditor.cpp \
        managermodules.cpp \
        biblequotedictmodule.cpp \
        finddialog.cpp \
        fontdialog.cpp

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
        strongcommon.h \
        processmodule.h \
        biblemodule.h \
        metainfo.h \
        moduledefinition.h \
        debughelper.h \
        chapter.h \
        book.h \
        range.h \
        ranges.h \
        rangeenum.h \
        textrange.h \
        textranges.h \
        verse.h \
        versification.h \
        versificationextendeddata.h \
        versification_kjv.h \
        versification_biblequote.h \
        bookv11n.h \
        strongurl.h \
        verseurl.h  \
        verseurlrange.h  \
        biblelink.h  \
        url.h \
        qsopherimmodule.h \
        qsopherimmodulelist.h \
        noteeditor.h \
        managermodules.h \
        biblequotedictmodule.h \
        finddialog.h \
        fontdialog.h

FORMS    += \
        mainwindow.ui \
        about.ui \
        settings.ui \
        leftpanel.ui \
        rightpanel.ui \
        bottompanel.ui \
        leftpanel2.ui \
        moduleviewer.ui \
        noteeditor.ui \
        managermodules.ui \
        finddialog.ui \
        fontdialog.ui

RESOURCES += \
        resources/resources.qrc

TRANSLATIONS += \
        resources/lang/QSopherim_ru.ts \
        resources/lang/QSopherim_de.ts \
        resources/lang/QSopherim_fr.ts
