#-------------------------------------------------
#
# Project created by QtCreator 2018-05-26T11:47:14
#
#-------------------------------------------------

QT       += core gui

CONFIG  += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cipher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        ciphers.cpp \
    caesar.cpp \
    generator.cpp \
    morse.cpp \
    translit.cpp \
    leshill.cpp

HEADERS  += mainwindow.h\
            ciphers.h \
    caesar.h \
    generator.h \
    morse.h \
    translit.h \
    leshill.h

FORMS    += mainwindow.ui \
    caesar.ui \
    generator.ui \
    morse.ui \
    translit.ui \
    leshill.ui

#INCLUDEPATH += $$quote("D:\Armadillo\include\armadillo_bits")

#LIBS += \
#    -L$$quote("D:\Armadillo\examples\lib_win64") \
#    -llapack_win64_MT \
#    -lblas_win64_MT

RESOURCES += \
    resources.qrc
