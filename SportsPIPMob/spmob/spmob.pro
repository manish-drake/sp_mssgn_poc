QT += quick

TEMPLATE = app

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        viewmodel.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



HEADERS += \
    viewmodel.h

android: {
    LIBS += -L$$PWD/../../3rdparty/libzmq-android-arm-bin/lib/ -lzmq
    INCLUDEPATH += $$PWD/../../3rdparty/libzmq-android-arm-bin/include
    DEPENDPATH += $$PWD/../../3rdparty/libzmq-android-arm-bin/include

}
contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../3rdparty/libzmq-android-arm-bin/lib/libzmq.so \
        /home/manish/Android/android-ndk-r10e/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a/libc++_shared.so
}


unix:{ LIBS += -L$$PWD/../../3rdparty/libzmq-bin-x64/lib/ -lzmq

INCLUDEPATH += $$PWD/../../3rdparty/libzmq-bin-x64/include
DEPENDPATH += $$PWD/../../3rdparty/libzmq-bin-x64/include
}

unix|win32: LIBS += -L$$OUT_PWD/../../csvdb/ -lcsvdb

INCLUDEPATH += $$PWD/../../csvdb
DEPENDPATH += $$PWD/../../csvdb

unix|win32: LIBS += -L$$OUT_PWD/../../ftpclient/ -lftpclient

INCLUDEPATH += $$PWD/../../ftpclient
DEPENDPATH += $$PWD/../../ftpclient

unix|win32: LIBS += -L$$OUT_PWD/../../messaging/ -lmessaging

INCLUDEPATH += $$PWD/../../messaging
DEPENDPATH += $$PWD/../../messaging
