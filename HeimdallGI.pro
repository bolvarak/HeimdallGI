QT             += core network sql

QT             -= gui

TARGET          = Application.hgi

CONFIG         += console

CONFIG         -= app_bundle

TEMPLATE        = app

QMAKE_CXXFLAGS += -std=c++11

DEFINES        += HGI_CONFIG_FILE=\"\\\"/srv/tbrown/playground.einhammr.com/data/hgi/conf/application.ini\\\"\"

SOURCES        += \
		main.cpp \
		CGI.cpp \
		Configuration.cpp \
		DBI.cpp \
		HTML.cpp \
		Router.cpp \
		Template.cpp \
		TestController.cpp \
		View.cpp \
		Log.cpp \
		Base.cpp \
		Model.cpp \
                ErrorController.cpp
                # Ion.cpp

HEADERS        +=  \
		CGI.h \
		Configuration.h \
		DBI.h \
		HTML.h \
		Router.h \
		Singleton.h \
		Template.h \
		TestController.h \
		View.h \
		Log.h \
		Base.h \
		Model.h \
                ErrorController.h
                # Ion.h

OTHER_FILES    += \
		Application.ini \
		run.sh \
		notFound.hgt \
                serverFault.hgt
                # HGML.json

RESOURCES      += \
		Resources.qrc
