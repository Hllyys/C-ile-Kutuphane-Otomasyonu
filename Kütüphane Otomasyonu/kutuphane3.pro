QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    kitap.cpp \
    main.cpp \
    mainwindow.cpp \
    odunc_alinan.cpp \
    odunc_teslim_edilen.cpp \
    uye.cpp

HEADERS += \
    kitap.h \
    mainwindow.h \
    odunc_alinan.h \
    odunc_teslim_edilen.h \
    uye.h

FORMS += \
    kitap.ui \
    mainwindow.ui \
    odunc_alinan.ui \
    odunc_teslim_edilen.ui \
    uye.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    resources.qrc
