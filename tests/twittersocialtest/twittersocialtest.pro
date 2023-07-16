TARGET = twittersocialtest
PREFIX = /opt/tests/nemo-qml-plugins-qt$${QT_MAJOR_VERSION}/social/

QT = core gui network qml quick

target.path = $${PREFIX}

INCLUDEPATH += ../../src/
HEADERS += ../../src/twitter/twitterdatautil_p.h
SOURCES += main.cpp \
            ../../src/twitter/twitterdatautil.cpp

OTHER_FILES += $$system(./qt$${QT_MAJOR_VERSION}ify.sh) 5/Web.qml

DEFINES *= PLUGIN_PATH=\"\\\"\"$${DEFINES_PREFIX}/$$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH\"\\\"\"
DEFINES *= DEPLOYMENT_PATH=\"\\\"\"$${DEFINES_PREFIX}/$${PREFIX}share/\"\\\"\"

qml.files = $${OTHER_FILES}
qml.path = $${PREFIX}/share

INSTALLS += target qml
