#-------------------------------------------------
#
# Project created by QtCreator 2018-10-14T11:44:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModelisationJV
TEMPLATE = app


SOURCES += \
    src/analyticfield.cpp \
    src/analyticfieldpn.cpp \
    src/analyticfieldridge.cpp \
    src/analyticfieldridgeattenuate.cpp \
    src/analyticfieldsumpn.cpp \
    src/box2.cpp \
    src/dijkstra.cpp \
    src/disc.cpp \
    src/drainagearea.cpp \
    src/erosion.cpp \
    src/forest.cpp \
    src/grid2.cpp \
    src/heightfield.cpp \
    src/heightfieldmulti.cpp \
    src/hydroerosion.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/perlinnoise.cpp \
    src/poissondiscsampling.cpp \
    src/scalarfield2.cpp \
    src/thermalerosion.cpp \
    src/vec2.cpp \
    src/vec3.cpp \
    src/veget.cpp \
    src/vegetappletree.cpp \
    src/vegetfir.cpp

HEADERS  += \
    src/analyticfield.h \
    src/analyticfieldpn.h \
    src/analyticfieldridge.h \
    src/analyticfieldridgeattenuate.h \
    src/analyticfieldsumpn.h \
    src/box2.h \
    src/dijkstra.h \
    src/disc.h \
    src/drainagearea.h \
    src/erosion.h \
    src/forest.h \
    src/grid2.h \
    src/heightfield.h \
    src/heightfieldmulti.h \
    src/hydroerosion.h \
    src/mainwindow.h \
    src/perlinnoise.h \
    src/poissondiscsampling.h \
    src/scalarfield2.h \
    src/thermalerosion.h \
    src/vec2.h \
    src/vec3.h \
    src/veget.h \
    src/vegetappletree.h \
    src/vegetfir.h

FORMS    += \
    src/mainwindow.ui

RESOURCES += \
    resources.qrc
