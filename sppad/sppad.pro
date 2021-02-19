QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        csvlist.cpp \
        delegate.cpp \
        listener.cpp \
        main.cpp \
        messages.cpp \
        messenger.cpp \
    ftpclient.cpp \
    ftpcontrolchannel.cpp \
    ftpdatachannel.cpp \
    viewmodel.cpp

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
    csvlist.h \
    delegate.h \
    listener.h \
    messages.h \
    messaging_exceptions.h \
    messenger.h \
    ftpclient.h \
    ftpcontrolchannel.h \
    ftpdatachannel.h \
    viewmodel.h
unix: {
    LIBS += -L$$PWD/../../libzmq-bin-x64/lib/ -lzmq

    INCLUDEPATH += $$PWD/../../libzmq-bin-x64/include
    DEPENDPATH += $$PWD/../../libzmq-bin-x64/include
}



    android:{ LIBS += -L$$PWD/../build-sptest-Qt_6_0_1_for_iOS-Debug/iOS-arm64/lib/ -lzmq

    INCLUDEPATH += $$PWD/../build-sptest-Qt_6_0_1_for_iOS-Debug/iOS-arm64/include
    DEPENDPATH += $$PWD/../build-sptest-Qt_6_0_1_for_iOS-Debug/iOS-arm64/include
}
#    win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../build-sptest-Qt_6_0_1_for_iOS-Debug/iOS-arm64/lib/zmq.lib
#    else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../build-sptest-Qt_6_0_1_for_iOS-Debug/iOS-arm64/lib/libzmq.a
