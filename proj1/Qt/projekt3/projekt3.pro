#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T17:35:31
#
#-------------------------------------------------

HEADERS       = mainwindow.h \
                svgview.h
RESOURCES     = svgviewer.qrc
SOURCES       = main.cpp \
                mainwindow.cpp \
                svgview.cpp
QT           += widgets svg

qtHaveModule(opengl): QT += opengl

CONFIG += console

# install
target.path = $$[QT_INSTALL_EXAMPLES]/svg/svgviewer
INSTALLS += target

wince*: {
     addFiles.files = files\\*.svg
     addFiles.path = "\\My Documents"
     DEPLOYMENT += addFiles
}
