QT += network multimedia sql testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_synctest.cpp


RESOURCES += \
    res.qrc

DESTDIR = $$PWD/../installer/packages/SoundBand.Tests/data

include($$PWD/../Sync/Sync.pri)
