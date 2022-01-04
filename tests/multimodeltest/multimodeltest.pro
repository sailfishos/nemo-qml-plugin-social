TEMPLATE = app
TARGET = multimodeltest

QT = core qml network testlib

INCLUDEPATH += ../../src/

HEADERS +=  ../../src/contentiteminterface.h \
            ../../src/contentiteminterface_p.h \
            ../../src/identifiablecontentiteminterface.h \
            ../../src/identifiablecontentiteminterface_p.h \
            ../../src/socialnetworkinterface.h \
            ../../src/socialnetworkinterface_p.h \
            ../../src/socialnetworkmodelinterface.h \
            ../../src/socialnetworkmodelinterface_p.h \
            ../../src/filterinterface.h \
            ../../src/contentitemtypefilterinterface.h \

SOURCES +=  ../../src/contentiteminterface.cpp \
            ../../src/identifiablecontentiteminterface.cpp \
            ../../src/socialnetworkinterface.cpp \
            ../../src/socialnetworkmodelinterface.cpp \
            ../../src/filterinterface.cpp \
            ../../src/contentitemtypefilterinterface.cpp \
            main.cpp
