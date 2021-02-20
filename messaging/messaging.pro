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


android: {
    LIBS += -L$$PWD/../libzmq-android-arm-bin/lib/ -lzmq
    INCLUDEPATH += $$PWD/../libzmq-android-arm-bin/include
    DEPENDPATH += $$PWD/../libzmq-android-arm-bin/include

}
contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        Z:/git/sptest/../libzmq-android-arm-bin/lib/libzmq.so \
        $$PWD/../../Users/manish/android-ndk-r14b/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a/libc++_shared.so
}

unix: {
    LIBS += -L$$PWD/../../libzmq-bin-x64/lib/ -lzmq

    INCLUDEPATH += $$PWD/../../libzmq-bin-x64/include
    DEPENDPATH += $$PWD/../../libzmq-bin-x64/include
}

unix|win32: LIBS += -L$$OUT_PWD/../csvdb/ -lcsvdb

INCLUDEPATH += $$PWD/../csvdb
DEPENDPATH += $$PWD/../csvdb
