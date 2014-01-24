QT             += core network sql

QT             -= gui

TARGET          = Application.hgi

CONFIG         += console

CONFIG         -= app_bundle

TEMPLATE        = app

QMAKE_CXXFLAGS += -std=c++11

DEFINES        += HGI_CONFIG_FILE=\"\\\":/Configuration/Application.ini\\\"\"

SOURCES        += \
		main.cpp \
		CGI.cpp \
		Configuration.cpp \
		DBI.cpp \
		HTML.cpp \
		Interpretation/Functions.cpp \
		Interpreter.cpp \
		Router.cpp \
		Template.cpp \
		TestController.cpp \
		View.cpp \
		NeuralNetwork.cpp \
		Log.cpp \
		Base.cpp \
		Model.cpp \
		ErrorController.cpp \

HEADERS        +=  \
		CGI.h \
		Configuration.h \
		DBI.h \
		HTML.h \
		Interpretation/Functions.h \
		Interpreter.h \
		Router.h \
		Singleton.h \
		Template.h \
		TestController.h \
		View.h \
		NeuralNetwork.h \
		Log.h \
		Base.h \
		Model.h \
		ErrorController.h \

OTHER_FILES    += \
		Application.ini \
		run.sh \
		notFound.hgt \
		serverFault.hgt \
    HGML.json

RESOURCES      += \
		Resources.qrc
