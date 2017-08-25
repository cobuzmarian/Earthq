#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDomDocument>
#include <vector>
#include "datahandler.h"
#include <iostream>
#include <QDate>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	this->dataHandler = new DataHandler();
	int parsingSuccess = 0;
	parsingSuccess = dataHandler->parseXML("events.xml");

	//qDebug(to_string(parsingSuccess).c_str());

	dataHandler->sortByDateAsc();

	QVector<double> *y = dataHandler->getTimeSeries();
	QVector<double> x;

	int i;
	for (i = 0; i < y->length(); i++) {
		x.append(i);
		//qDebug(to_string((*y)[i]).c_str());
	}

	QLinearGradient gradient(0, 0, 0, 400);
	gradient.setColorAt(0, QColor(0, 0, 0));
	gradient.setColorAt(1, QColor(0, 0, 0));
	ui->centralWidget->setBackground(QBrush(gradient));

	ui->centralWidget->addGraph();
	QPen yellowPen;
	yellowPen.setColor(QColor(255, 255, 255));
	QPen gridPen;
	gridPen.setColor(QColor(255, 255, 255, 20));
	gridPen.setStyle(Qt::DotLine);
	gridPen.setWidth(1);
	ui->centralWidget->graph(0)->setPen(yellowPen);
	ui->centralWidget->graph(0)->setData(x, *y);
	ui->centralWidget->xAxis->setRange(0, y->length());
	ui->centralWidget->yAxis->setRange(0, 7);
	ui->centralWidget->xAxis->grid()->setPen(gridPen);
	ui->centralWidget->yAxis->grid()->setPen(gridPen);
	ui->centralWidget->xAxis->setLabelColor(QColor(255, 255, 255));
	ui->centralWidget->yAxis->setLabelColor(QColor(255, 255, 255));

	ui->centralWidget->addGraph();
	QPen blueDotPen;
	blueDotPen.setColor(QColor(255, 255, 150, 200));
	blueDotPen.setStyle(Qt::DotLine);
	blueDotPen.setWidthF(3);
	ui->centralWidget->graph(1)->setPen(blueDotPen);
	QVector<double> x2, y2;
	x2.append(0);
	x2.append(10000);
	y2.append(2);
	y2.append(3);
	ui->centralWidget->graph(1)->setData(x2, y2);

	ui->dateEdit->setMinimumDate(this->dataHandler->getFirstDate());
	ui->dateEdit->setMaximumDate(this->dataHandler->getLastDate());
	ui->dateEdit->setDate(this->dataHandler->getFirstDate());

	ui->dateEdit_2->setMinimumDate(this->dataHandler->getFirstDate());
	ui->dateEdit_2->setMaximumDate(this->dataHandler->getLastDate());
	ui->dateEdit_2->setDate(this->dataHandler->getLastDate());

	connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(date1Changed(QDate)));
	connect(ui->dateEdit_2, SIGNAL(dateChanged(QDate)), this, SLOT(date2Changed(QDate)));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::date1Changed(QDate date) {
	ui->centralWidget->xAxis->setRangeLower(this->dataHandler->getFirstDate().daysTo(date));
	ui->centralWidget->replot();
}

void MainWindow::date2Changed(QDate date) {
	ui->centralWidget->xAxis->setRangeUpper(this->dataHandler->getFirstDate().daysTo(date));
	ui->centralWidget->replot();
}
