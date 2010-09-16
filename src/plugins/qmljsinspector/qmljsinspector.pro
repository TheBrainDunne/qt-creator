TEMPLATE = lib
TARGET = QmlJSInspector
INCLUDEPATH += .
DEPENDPATH += .
QT += declarative network

DEFINES += QMLJSINSPECTOR_LIBRARY

HEADERS += \
qmljsprivateapi.h \
qmljsinspector_global.h \
qmljsinspectorconstants.h \
qmljsinspectorplugin.h \
qmljsclientproxy.h \
qmljsinspector.h \
qmlinspectortoolbar.h \
qmljslivetextpreview.h \
qmljstoolbarcolorbox.h \
qmljsobserverclient.h \
qmljscontextcrumblepath.h \
qmljsinspectorsettings.h \
qmljsobjecttree.h

SOURCES += \
qmljsinspectorplugin.cpp \
qmljsclientproxy.cpp \
qmljsinspector.cpp \
qmlinspectortoolbar.cpp \
qmljslivetextpreview.cpp \
qmljstoolbarcolorbox.cpp \
qmljsobserverclient.cpp \
qmljscontextcrumblepath.cpp \
qmljsinspectorsettings.cpp \
qmljsobjecttree.cpp

include(../../libs/qmljsdebugclient/qmljsdebugclient-lib.pri)

OTHER_FILES += QmlJSInspector.pluginspec
RESOURCES += qmljsinspector.qrc

include(../../qtcreatorplugin.pri)
include(../../plugins/projectexplorer/projectexplorer.pri)
include(../../plugins/qmlprojectmanager/qmlprojectmanager.pri)
include(../../plugins/coreplugin/coreplugin.pri)
include(../../plugins/texteditor/texteditor.pri)
include(../../plugins/debugger/debugger.pri)
include(../../libs/utils/utils.pri)
