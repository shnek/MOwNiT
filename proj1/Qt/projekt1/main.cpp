#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "proj.c"


#include <QApplication>
#include <QString>
#ifndef QT_NO_OPENGL
#include <QGLFormat>
#endif

#include "mainwindow.h"

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(svgviewer);

    QApplication app(argc, argv);

    MainWindow window;
    if (argc == 2)
        window.openFile(argv[1]);
    else
        window.openFile(":/files/bubbles.svg");
    window.show();
    return app.exec();
}
//int main(int argc, char *argv[])
//{
//    QGuiApplication app(argc, argv);

//    QtQuick2ApplicationViewer viewer;
//    viewer.setMainQmlFile(QStringLiteral("qml/projekt1/main.qml"));
//    viewer.showExpanded();
//    run(1, 10, 1);
//    return app.exec();
//}
