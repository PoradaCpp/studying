#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskswidget.h"

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();

private:
    void createMenus();

    Ui::MainWindow *ui;
    QAction *editAct;
    QAction *removeAct;
};

#endif // MAINWINDOW_H

