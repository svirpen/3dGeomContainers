TEMPLATE = app
CONFIG += console
CONFIG += c++1z c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp


SOURCES += \
        addit.cpp \
        curvelisttasks.cpp \
        main.cpp

HEADERS += \
  addit.h \
  curvelisttasks.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Geom3dLib/release/ -lGeom3dLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Geom3dLib/debug/ -lGeom3dLib
else:unix: LIBS += -L$$OUT_PWD/../Geom3dLib/ -lGeom3dLib

INCLUDEPATH += $$PWD/../Geom3dLib
DEPENDPATH += $$PWD/../Geom3dLib
