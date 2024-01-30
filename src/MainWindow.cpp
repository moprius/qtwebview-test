#include <QApplication>
#include <QMessageBox>
#include "MainWindow.h"
#include "QContextMenuEvent"
#include <QWebEngineSettings>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setMinimumSize(800, 800);
    view = new QWebEngineView(this);
    setCentralWidget(view);
    view->load(QUrl("https://moprius.blogspot.com")); // A URL do Website

    view->setContextMenuPolicy(Qt::NoContextMenu); //Bloqueando o Menu de contexto padrão


    // Acessando a barra de Menu
    QMenuBar *myMenuBar = menuBar();

    // Menu "Arquivo"
    QMenu *fileMenu = myMenuBar->addMenu(tr("&Arquivo"));

    // Submenu "Início"
    QAction *homeAction = new QAction(tr("Início"), this);
    connect(homeAction, &QAction::triggered, this, &MainWindow::openHome);
    fileMenu->addAction(homeAction);

    // Submenu "Sair"
    QAction *exitAction = new QAction(tr("Sair"), this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitApplication);
    fileMenu->addAction(exitAction);

    // Menu "Editar"
    QMenu *editMenu = myMenuBar->addMenu(tr("&Editar"));

    // Submenu "Selecionar tudo"
    QAction *selectAllAction = new QAction(tr("Selecionar tudo"), this);
    connect(selectAllAction, &QAction::triggered, this, &MainWindow::selectAll);
    editMenu->addAction(selectAllAction);

    // Submenu "Copiar"
    QAction *copyAction = new QAction(tr("Copiar"), this);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copy);
    editMenu->addAction(copyAction);

    // Submenu "Recortar"
    QAction *cutAction = new QAction(tr("Recortar"), this);
    connect(cutAction, &QAction::triggered, this, &MainWindow::cut);
    editMenu->addAction(cutAction);

    // Submenu "Colar"
    QAction *pasteAction = new QAction(tr("Colar"), this);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);
    editMenu->addAction(pasteAction);

    // Menu "Exibir"
    QMenu *viewMenu = myMenuBar->addMenu(tr("&Exibir"));

    // Submenu "Zoom in" aumenta a visualização do Website
    QAction *zoomInAction = new QAction(tr("Zoom in"), this);
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);
    viewMenu->addAction(zoomInAction);

    // Submenu "Zoom out" diminuí a visualização do Website
    QAction *zoomOutAction = new QAction(tr("Zoom out"), this);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
    viewMenu->addAction(zoomOutAction);

    // Menu "Ajuda"
    QMenu *helpMenu = menuBar()->addMenu(tr("&Ajuda"));

    // Submenu "Sobre"
    QAction *aboutAction = new QAction(tr("Sobre"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::openAbout);
    helpMenu->addAction(aboutAction);

    // Submenu "Criador" mensagem que exibe na tela
    QAction *creatorAction = new QAction(tr("Criador"), this);
    connect(creatorAction, &QAction::triggered, this, &MainWindow::openCreator);
    helpMenu->addAction(creatorAction);

}

// Menu de contexto com os Menus: Copiar, Colar, Recarregar e Abrir em um navegador externo
void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    QMenu contextMenu(this);
    QAction *copyAction = contextMenu.addAction(tr("Copiar"));
    QAction *pasteAction = contextMenu.addAction(tr("Colar"));
    QAction *reloadAction = contextMenu.addAction(tr("Recarregar"));

    QAction *openInExtBrowserAction = contextMenu.addAction(tr("Abrir em um navegador externo"));

    QAction *selectedAction = contextMenu.exec(event->globalPos());

    if (selectedAction == copyAction) {

        view->triggerPageAction(QWebEnginePage::Copy);
    } else if (selectedAction == pasteAction) {

        view->triggerPageAction(QWebEnginePage::Paste);
    } else if (selectedAction == reloadAction) {

        view->reload();
    } else if (selectedAction == openInExtBrowserAction) {
        openInExternalBrowser();
    }

}

void MainWindow::openHome() {
    view->load(QUrl("https://moprius.blogspot.com"));
}

void MainWindow::exitApplication() {
    QApplication::quit();
}

void MainWindow::selectAll() {
    view->triggerPageAction(QWebEnginePage::SelectAll);
}

void MainWindow::copy() {
    view->triggerPageAction(QWebEnginePage::Copy);
}

void MainWindow::cut() {
    view->triggerPageAction(QWebEnginePage::Cut);
}

void MainWindow::paste() {
    view->triggerPageAction(QWebEnginePage::Paste);
}

void MainWindow::zoomIn() {
    view->setZoomFactor(view->zoomFactor() + 0.1);
}

void MainWindow::zoomOut() {
    view->setZoomFactor(view->zoomFactor() - 0.1);
}

void MainWindow::openAbout() {
    view->load(QUrl("https://moprius.blogspot.com/2013/04/blog.html"));
}

void MainWindow::openCreator() {
    QMessageBox::information(this, tr("Criador"), tr("Criado por Moprius, usando C++ e QT6. Isso é um teste do QT WebView"));
}

void MainWindow::openInExternalBrowser() {
    QUrl url = view->url();
    if (!url.isEmpty()) {
        QDesktopServices::openUrl(url);
    }
}
