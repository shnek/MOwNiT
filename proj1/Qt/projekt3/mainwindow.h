#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class SvgView;

class QAction;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsRectItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void openFile(const QString &path = QString());
    void setRenderer(QAction *action);

private:
    QAction *m_nativeAction;
    QAction *m_glAction;
    QAction *m_imageAction;
    QAction *m_highQualityAntialiasingAction;
    QAction *m_backgroundAction;
    QAction *m_outlineAction;

    SvgView *m_view;

    QString m_currentPath;
};

#endif
