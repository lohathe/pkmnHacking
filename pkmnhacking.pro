######################################################################
# Automatically generated by qmake (2.01a) Mon Jan 28 19:44:18 2013
######################################################################

TEMPLATE = app
TARGET = PkmnHack
DESTDIR = ./
OBJECTS_DIR = ./build
MOC_DIR = ./src/moc
DEPENDPATH += . \
              src \
              include/controller \
              include/model \
              include/view \
              src/controller \
              src/model \
              src/view
INCLUDEPATH += . include/model

# Input
HEADERS += include/controller/pkmnpartycontroller.h \
           include/controller/pkmnsavestatecontroller.h \
           include/model/pkmnaliment.h \
           include/model/pkmndataformat.h \
           include/model/pkmnelement.h \
           include/model/pkmnmove.h \
           include/model/pkmnsavestate.h \
           include/model/pkmnsavestatemodel.h \
           include/model/pkmnspecies.h \
           include/model/pkmnstate.h \
           include/model/pkmnstringreader.h \
           include/model/pkmntype.h \
           include/view/pkmnmovepickerview.h \
           include/view/pkmnpartylistitemview.h \
           include/view/pkmnpartylistview.h \
           include/view/pkmnpartyview.h \
           include/view/pkmnsavestateview.h \
           include/view/pkmnspeciespickerview.h
SOURCES += src/main.cpp \
           src/controller/pkmnpartycontroller.cpp \
           src/controller/pkmnsavestatecontroller.cpp \
           src/model/pkmnmove.cpp \
           src/model/pkmnsavestate.cpp \
           src/model/pkmnsavestatemodel.cpp \
           src/model/pkmnspecies.cpp \
           src/model/pkmnstate.cpp \
           src/model/pkmnstringreader.cpp \
           src/view/pkmnmovepickerview.cpp \
           src/view/pkmnpartylistitemview.cpp \
           src/view/pkmnpartylistview.cpp \
           src/view/pkmnpartyview.cpp \
           src/view/pkmnsavestateview.cpp \
           src/view/pkmnspeciespickerview.cpp
RESOURCES += pkmnhacking.qrc