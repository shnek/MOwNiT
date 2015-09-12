#include "mainwindow.h"

#include <QtWidgets>

#include "svgview.h"

MainWindow::MainWindow()
    : QMainWindow()
    , m_view(new SvgView)
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    QAction *openAction = fileMenu->addAction(tr("&Open..."));
    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcuts(QKeySequence::Quit);

    menuBar()->addMenu(fileMenu);

    QMenu *viewMenu = new QMenu(tr("&View"), this);
    m_backgroundAction = viewMenu->addAction(tr("&Background"));
    m_backgroundAction->setEnabled(false);
    m_backgroundAction->setCheckable(true);
    m_backgroundAction->setChecked(false);
    connect(m_backgroundAction, SIGNAL(toggled(bool)), m_view, SLOT(setViewBackground(bool)));

    m_outlineAction = viewMenu->addAction(tr("&Outline"));
    m_outlineAction->setEnabled(false);
    m_outlineAction->setCheckable(true);
    m_outlineAction->setChecked(true);
    connect(m_outlineAction, SIGNAL(toggled(bool)), m_view, SLOT(setViewOutline(bool)));

    menuBar()->addMenu(viewMenu);

    QMenu *rendererMenu = new QMenu(tr("&Renderer"), this);
    m_nativeAction = rendererMenu->addAction(tr("&Native"));
    m_nativeAction->setCheckable(true);
    m_nativeAction->setChecked(true);
#ifndef QT_NO_OPENGL
    m_glAction = rendererMenu->addAction(tr("&OpenGL"));
    m_glAction->setCheckable(true);
#endif
    m_imageAction = rendererMenu->addAction(tr("&Image"));
    m_imageAction->setCheckable(true);

#ifndef QT_NO_OPENGL
    rendererMenu->addSeparator();
    m_highQualityAntialiasingAction = rendererMenu->addAction(tr("&High Quality Antialiasing"));
    m_highQualityAntialiasingAction->setEnabled(false);
    m_highQualityAntialiasingAction->setCheckable(true);
    m_highQualityAntialiasingAction->setChecked(false);
    connect(m_highQualityAntialiasingAction, SIGNAL(toggled(bool)), m_view, SLOT(setHighQualityAntialiasing(bool)));
#endif

    QActionGroup *rendererGroup = new QActionGroup(this);
    rendererGroup->addAction(m_nativeAction);
#ifndef QT_NO_OPENGL
    rendererGroup->addAction(m_glAction);
#endif
    rendererGroup->addAction(m_imageAction);

    menuBar()->addMenu(rendererMenu);

    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(rendererGroup, SIGNAL(triggered(QAction*)),
            this, SLOT(setRenderer(QAction*)));

    setCentralWidget(m_view);
    setWindowTitle(tr("SVG Viewer"));
}

void MainWindow::openFile(const QString &path)
{
    QString fileName;
    if (path.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open SVG File"),
                m_currentPath, "SVG files (*.svg *.svgz *.svg.gz)");
    else
        fileName = path;

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.exists()) {
            QMessageBox::critical(this, tr("Open SVG File"),
                           QString("Could not open file '%1'.").arg(fileName));

            m_outlineAction->setEnabled(false);
            m_backgroundAction->setEnabled(false);
            return;
        }

        m_view->openFile(file);

        if (!fileName.startsWith(":/")) {
            m_currentPath = fileName;
            setWindowTitle(tr("%1 - SVGViewer").arg(m_currentPath));
        }

        m_outlineAction->setEnabled(true);
        m_backgroundAction->setEnabled(true);

        resize(m_view->sizeHint() + QSize(80, 80 + menuBar()->height()));
    }
}

void MainWindow::setRenderer(QAction *action)
{
#ifndef QT_NO_OPENGL
    m_highQualityAntialiasingAction->setEnabled(false);
#endif

    if (action == m_nativeAction)
        m_view->setRenderer(SvgView::Native);
#ifndef QT_NO_OPENGL
    else if (action == m_glAction) {
        m_highQualityAntialiasingAction->setEnabled(true);
        m_view->setRenderer(SvgView::OpenGL);
    }
#endif
    else if (action == m_imageAction) {
        m_view->setRenderer(SvgView::Image);
    }
}