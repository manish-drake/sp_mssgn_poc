#-------------------------------------------------
#
# Project created by QtCreator 2021-02-24T13:45:18
#
#-------------------------------------------------

QT       += network

TARGET = ftpclient
TEMPLATE = lib

DEFINES += FTPCLIENT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    ../../ftpclient/commandbase.h \
    ../../ftpclient/commandopts.h \
    ../../ftpclient/commandport.h \
    ../../ftpclient/commandstor.h \
    ../../ftpclient/commanddata.h \
    ../../ftpclient/commandquit.h \
    ../../ftpclient/commandpwd.h \
    ../../ftpclient/ftpclient.h \
    ../../ftpclient/pipeline.h \
    ../../ftpclient/ftpcontrolchannel.h \
    ../../ftpclient/ftpdatachannel.h \
    ../../ftpclient/commanduser.h

SOURCES += \
    ../../ftpclient/commandbase.cpp \
    ../../ftpclient/pipeline.cpp \
    ../../ftpclient/ftpclient.cpp \
    ../../ftpclient/ftpcontrolchannel.cpp \
    ../../ftpclient/ftpdatachannel.cpp \
    ../../ftpclient/commandport.cpp \
    ../../ftpclient/commandstor.cpp \
    ../../ftpclient/commanddata.cpp \
    ../../ftpclient/commandquit.cpp \
    ../../ftpclient/commandpwd.cpp \
    ../../ftpclient/commandopts.cpp \
    ../../ftpclient/commanduser.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logging/release/ -llogging
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logging/debug/ -llogging
else:unix: LIBS += -L$$OUT_PWD/../logging/ -llogging

INCLUDEPATH += $$PWD/../../logging
DEPENDPATH += $$PWD/../../logging
