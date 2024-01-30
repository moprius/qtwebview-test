#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include "QContextMenuEvent"
#include <QWebEngineSettings>


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots: // Declaração de membros privados de slots
    void openHome();
    void exitApplication();
    void selectAll();
    void copy();
    void cut();
    void paste();
    void zoomIn();
    void zoomOut();
    void openAbout();
    void openCreator();
    void openInExternalBrowser();


private:
    QWebEngineView *view;

    // Ações do menu de contexto como membros privados
    QAction *copyAction;
    QAction *pasteAction;
    QAction *reloadAction;
    QAction *openInExternalBrowserAction;

    // Função na qual declara a manipulação do menu de contexto
    void contextMenuEvent(QContextMenuEvent *event) override;

};


#endif // MAINWINDOW_H
