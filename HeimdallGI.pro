QT          += core network sql
QT          -= gui
TARGET       = Application.hgi
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
SOURCES     += main.cpp \
		CGI.cpp \
		Configuration.cpp \
		DBI.cpp \
		HTML.cpp \
		Router.cpp \
		Template.cpp \
		TestController.cpp \
		View.cpp

HEADERS     += \
		CGI.h \
		Configuration.h \
		DBI.h \
		HTML.h \
		Router.h \
		Template.h \
		TestController.h \
		View.h

OTHER_FILES += \
	Application.ini

RESOURCES   += \
	Resources.qrc
