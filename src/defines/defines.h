#ifndef __DEFINES_H
#define __DEFINES_H

#define GL_PROG_VERSION_STR	"pre-alpha-2.5"
#define GL_PROG_BUILD_STR	"2013.02.11"
#define GL_PROG_NAME            "QSopherim"
#define GL_PROG_AUTHOR          "Sapronov Alexander"
#define GL_WEB_SITE             "http://warmonger1.github.com/QSopherim"

//

#define GL_FORMAT_MODULE QString(".qsi")
#define GL_FORMAT_TEXT QString(".qst")
#define GL_FORMAT_NOTES QString(".qsn")

#define GL_SYMBOL_SPLIT_CHAPTER QString("[*::*]")
#define GL_SYMBOL_SPLIT_BOOK QString("[*:*]")

#define GL_SYMBOL_SPLIT_JOURNAL QString("[^:^]")

#define GL_COLOR_DAY QColor(240, 240, 255)
#define GL_COLOR_NIGHT QColor(119, 119, 119)
#define GL_COLOR_NIGHT_TEXT QColor(204, 204, 204)

#define GL_MODULE_PATH QString("modules/")

#endif // __DEFINES_H
