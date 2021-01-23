QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        source/const_values.cpp \
        source/meta_parser/file_download.cpp \
        source/meta_parser/handle_input.cpp \
        source/meta_parser/og_parser.cpp \
        source/model_input_line.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/const_values.h \
    source/meta_parser/file_download.h \
    source/meta_parser/handle_input.h \
    source/meta_parser/og_parser.h \
    source/model_input_line.h
