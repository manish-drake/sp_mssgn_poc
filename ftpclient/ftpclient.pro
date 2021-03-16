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
    commandbase.h \
    commandopts.h \
    commandport.h \
    commandstor.h \
    commanddata.h \
    commandquit.h \
    commandpwd.h \
    ftpclient.h \
    pipeline.h \
    ftpcontrolchannel.h \
    ftpdatachannel.h \
    commanduser.h

SOURCES += \
    commandbase.cpp \
    pipeline.cpp \
    ftpclient.cpp \
    ftpcontrolchannel.cpp \
    ftpdatachannel.cpp \
    commandport.cpp \
    commandstor.cpp \
    commanddata.cpp \
    commandquit.cpp \
    commandpwd.cpp \
    commandopts.cpp \
    commanduser.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logging/release/ -llogging
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logging/debug/ -llogging
else:unix: LIBS += -L$$OUT_PWD/../logging/ -llogging

INCLUDEPATH += $$PWD/../logging
DEPENDPATH += $$PWD/../logging

