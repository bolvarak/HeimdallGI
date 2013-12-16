QT       += core network sql
QT       -= gui
TARGET    = Application.hgi
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
SOURCES  += main.cpp \
        #DBI.cpp \
        Router.cpp \
        View.cpp \
        CGI.cpp \
        HTML.cpp \
        Template.cpp \
        TestController.cpp \
    Configuration.cpp

HEADERS  += \
	#DBI.h \
        Router.h \
        View.h \
        CGI.h \
        HTML.h \
        Template.h \
        TestController.h \
    Configuration.h

OTHER_FILES += \
    Application.ini

RESOURCES += \
    Resources.qrc
