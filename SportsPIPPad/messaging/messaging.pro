QT       -= core gui
QT += network

TARGET = messaging
TEMPLATE = lib
CONFIG += c++11

DEFINES += MESSAGING_LIBRARY

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../csvdb/release/ -lcsvdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../csvdb/debug/ -lcsvdb
else:unix: LIBS += -L$$OUT_PWD/../csvdb/ -lcsvdb

INCLUDEPATH += $$PWD/../../csvdb
DEPENDPATH += $$PWD/../../csvdb

#######################ZMQ REFERENCES######################
android: {
    LIBS += -L$$PWD/../../3rdparty/libzmq-android-arm-bin/lib/ -lzmq
    INCLUDEPATH += $$PWD/../../3rdparty/libzmq-android-arm-bin/include
    DEPENDPATH += $$PWD/../../3rdparty/libzmq-android-arm-bin/include

}


unix:!ios{
    LIBS += -L$$PWD/../../3rdparty/libzmq-bin-x64/lib/ -lzmq

    INCLUDEPATH += $$PWD/../../3rdparty/libzmq-bin-x64/include
    DEPENDPATH += $$PWD/../../3rdparty/libzmq-bin-x64/include
}


win32:{
    win32: LIBS += -L$$PWD/../../3rdparty/libzmq32/lib/ -lzmq

    INCLUDEPATH += $$PWD/../../3rdparty/libzmq32/include
    DEPENDPATH += $$PWD/../../3rdparty/libzmq32/include
}

ios: {
    LIBS += -L$$PWD/../../3rdparty/libzmq-ios/lib/ -lzmq

    INCLUDEPATH += $$PWD/../../3rdparty/libzmq-ios/include
    DEPENDPATH += $$PWD/../../3rdparty/libzmq-ios/include
}
ios: PRE_TARGETDEPS += $$PWD/../../3rdparty/libzmq-ios/lib/libzmq.a
###############################################################


HEADERS += \
    ../../messaging/delegate.h \
    ../../messaging/idelegator.h \
    ../../messaging/listener.h \
    ../../messaging/messages.h \
    ../../messaging/messaging_exceptions.h \
    ../../messaging/messenger.h

SOURCES += \
    ../../messaging/delegate.cpp \
    ../../messaging/listener.cpp \
    ../../messaging/messages.cpp \
    ../../messaging/messenger.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logging/release/ -llogging
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logging/debug/ -llogging
else:unix: LIBS += -L$$OUT_PWD/../logging/ -llogging

INCLUDEPATH += $$PWD/../../logging
DEPENDPATH += $$PWD/../../logging
