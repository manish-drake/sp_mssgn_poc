#-------------------------------------------------
#
# Project created by QtCreator 2021-02-20T12:27:54
#
#-------------------------------------------------

QT       -= core gui

TARGET = messaging
TEMPLATE = lib
CONFIG += c++11

DEFINES += MESSAGING_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    listener.cpp \
    delegate.cpp \
    messages.cpp \
    messenger.cpp \

HEADERS += \
    listener.h \
    idelegator.h \
    delegate.h \
    messages.h \
    messenger.h \
    messaging_exceptions.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=
##############ZMQ REFERENCE##################
unix:{ LIBS += -L$$PWD/../../3rdparty/libzmq-bin-x64/lib/ -lzmq

INCLUDEPATH += $$PWD/../../3rdparty/libzmq-bin-x64/include
DEPENDPATH += $$PWD/../../3rdparty/libzmq-bin-x64/include
}

android:{ LIBS += -L$$PWD/../3rdparty/libzmq-android-arm-bin/lib/ -lzmq

INCLUDEPATH += $$PWD/../3rdparty/libzmq-android-arm-bin/include
DEPENDPATH += $$PWD/../3rdparty/libzmq-android-arm-bin/include
}

win32:{ LIBS += -L$$PWD/../3rdparty/libzmq32/lib/ -lzmq

INCLUDEPATH += $$PWD/../3rdparty/libzmq32/include
DEPENDPATH += $$PWD/../3rdparty/libzmq32/include
}

#---------------ANDROID DIST FILES-------------------
    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        ANDROID_EXTRA_LIBS = \
            $$PWD/../../3rdparty/libzmq-android-arm-bin/lib/libzmq.so \
            /home/manish/Android/android-ndk-r10e/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a/libc++_shared.so
    }
#----------------------------------------------------

#############################################

#>>>>>>>>>>>>>>>>>>>>CSVDB REFERENCES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

win32: {
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-csvdb-Desktop/release/ -lcsvdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-csvdb-Desktop/debug/ -lcsvdb

INCLUDEPATH += $$PWD/../csvdb
DEPENDPATH += $$PWD/../csvdb
}

android:{
    LIBS += -L$$PWD/../build-csvdb-Android/ -lcsvdb

    INCLUDEPATH += $$PWD/../csvdb
    DEPENDPATH += $$PWD/../csvdb
}
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


