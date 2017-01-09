#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T09:47:30
#
#-------------------------------------------------

QT       += core gui sensors multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sensors
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    camerasurfacewidget.cpp \
    threadsensors.cpp \
    threadimage.cpp

HEADERS  += mainwindow.h \
    camerasurfacewidget.h \
    threadsensors.h \
    threadimage.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

