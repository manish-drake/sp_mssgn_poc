QT += quick

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
        ftpcontrolchannel.cpp \
        ftpdatachannel.cpp \
        main.cpp \
        viewmodel.cpp \
    listener.cpp \
    csvlist.cpp \
    messenger.cpp \
    messages.cpp \
    delegate.cpp \
    ftpclient.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


android: {
    LIBS += -L$$PWD/../libzmq-android-arm-bin/lib/ -lzmq
    INCLUDEPATH += $$PWD/../libzmq-android-arm-bin/include
    DEPENDPATH += $$PWD/../libzmq-android-arm-bin/include
}
HEADERS += \
    ftpcontrolchannel.h \
    ftpdatachannel.h \
    viewmodel.h \
    csvlist.h \
    messenger.h \
    messaging_exceptions.h \
    listener.h \
    messages.h \
    delegate.h \
    ftpclient.h \
    idelegator.h

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
