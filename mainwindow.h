#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <datahandler.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	DataHandler *dataHandler;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void date1Changed(QDate date);
	void date2Changed(QDate date);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
