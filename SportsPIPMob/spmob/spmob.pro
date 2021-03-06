TEMPLATE=app

QT += quick qml multimedia network
TARGET=SPIP

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
    ../../common/network.cpp \
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
    ../../common/network.h \
    viewmodel.h
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



#-------------------------------------------------------------------------------------------------------------------


    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        ANDROID_EXTRA_LIBS = \
        Z:/git/sp_mssgn_poc/SportsPIPMob/spmob/../../3rdparty/libzmq-android-arm-bin/lib/libzmq.so \
        Z:/Users/manish/android-ndk-r14b/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a/libc++_shared.so \
        $$PWD/../../ftpclient/libftpclient.so
}


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../csvdb/release/ -lcsvdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../csvdb/debug/ -lcsvdb
else:unix: LIBS += -L$$OUT_PWD/../csvdb/ -lcsvdb

INCLUDEPATH += $$PWD/../../csvdb
DEPENDPATH += $$PWD/../../csvdb

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ftpclient/release/ -lftpclient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ftpclient/debug/ -lftpclient
else:unix: LIBS += -L$$OUT_PWD/../ftpclient/ -lftpclient

INCLUDEPATH += $$PWD/../../ftpclient
DEPENDPATH += $$PWD/../../ftpclient

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../messaging/release/ -lmessaging
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../messaging/debug/ -lmessaging
else:unix: LIBS += -L$$OUT_PWD/../messaging/ -lmessaging

INCLUDEPATH += $$PWD/../../messaging
DEPENDPATH += $$PWD/../../messaging

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logging/release/ -llogging
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logging/debug/ -llogging
else:unix: LIBS += -L$$OUT_PWD/../logging/ -llogging

INCLUDEPATH += $$PWD/../../logging
DEPENDPATH += $$PWD/../../logging
