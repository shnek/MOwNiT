# Add more folders to ship with the application, here
folder_01.source = qml/projekt1
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =
QMAKE_CXXFLAGS += `pkg-config --cflags --libs gsl` -lgsl
QMAKE_CFLAGS += `pkg-config --cflags --libs gsl` -lgsl
LIBS += -L/usr/include/gsl -lgsl -lgslcblas -lm

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()
