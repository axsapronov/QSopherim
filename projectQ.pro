#-------------------------------------------------
#
# Project created by QtCreator 2012-09-10T23:38:45
#
#-------------------------------------------------

QT       += core gui xml

TARGET      = projectQ
TEMPLATE    = app
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
         src/modules/biblemodule \
         src/modules/format \
         src/modules/metainfo \
         src/modules/ \
         src/defines \
         src/config \
         src/view/moduleviewer \
         src/modules/processmodule \
         src/common \
         src/core \
         src/core/verse \
         src/core/verse/versification \
         src/core/link \
         src/xmlread/

INCLUDEPATH += \
         src/main \
         src/dialogs/about \
         src/dialogs/settings \
         src/panel/leftpanel/ \
         src/panel/rightpanel/ \
         src/panel/bottompanel/ \
         src/dialogs/lansettings \
         src/modules/metainfo \
         src/view/moduleviewer \
         src/defines \
         src/modules/biblequote \
         src/modules/biblemodule \
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
         src/xmlread/

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
         processmodule.cpp \
         biblemodule.cpp \
         metainfo.cpp \
         debughelper.cpp \
    src/core/verse/chapter.cpp \
    src/core/verse/book.cpp \
    src/core/verse/range.cpp \
    src/core/verse/ranges.cpp \
    src/core/verse/rangeenum.cpp \
    src/core/verse/textrange.cpp \
    src/core/verse/textranges.cpp \
    src/core/verse/verse.cpp \
    src/core/verse/versification.cpp \
    src/core/verse/versificationextendeddata.cpp \
    src/core/verse/versification/versification_kjv.cpp \
    src/core/verse/versification/versification_biblequote.cpp \
    src/core/verse/versification/bookv11n.cpp \
    src/core/link/strongurl.cpp \
    src/core/link/verseurl.cpp \
    src/core/link/verseurlrange.cpp \
    src/core/link/biblelink.cpp \
    src/core/link/url.cpp \
    src/view/module/projectqmodule.cpp \
    src/view/module/projectqmodulelist.cpp \
    src/xmlread/projectqxmlhandler.cpp \
         csaxhandler.cpp \
         cnode.cpp


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
         processmodule.h \
         biblemodule.h \
         metainfo.h \
         moduledefinition.h \
         debughelper.h \
    src/core/verse/chapter.h \
    src/core/verse/book.h \
    src/core/verse/range.h \
    src/core/verse/ranges.h \
    src/core/verse/rangeenum.h \
    src/core/verse/textrange.h \
    src/core/verse/textranges.h \
    src/core/verse/verse.h \
    src/core/verse/versification.h \
    src/core/verse/versificationextendeddata.h \
    src/core/verse/versification/versification_kjv.h \
    src/core/verse/versification/versification_biblequote.h \
    src/core/verse/versification/bookv11n.h \
    src/core/link/strongurl.h \
    src/core/link/verseurl.h  \
    src/core/link/verseurlrange.h  \
    src/core/link/biblelink.h  \
    src/core/link/url.h \
    src/view/module/projectqmodule.h \
    src/view/module/projectqmodulelist.h \
    src/xmlread/projectqxmlhandler.h \
         csaxhandler.h \
         cnode.h

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
