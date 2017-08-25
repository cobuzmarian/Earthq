#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "event.h"
#include <string>
#include <QVector>

using namespace std;

class DataHandler {
private:
	QVector<Event> *events;
	QDate firstDate, lastDate;

public:
	DataHandler();

	int parseXML(const string name);

	QVector<double>* getTimeSeries();

	void sortByMagnitudeAsc();
	void sortByMagnitudeDesc();
	void sortByDateAsc();
	void sortByDateDesc();

	static void sortVectorByMagnitudeAsc(QVector<Event> *vector);
	static void sortVectorByMagnitudeDesc(QVector<Event> *vector);
	static void sortVectorByDateAsc(QVector<Event> *vector);
	static void sortVectorByDateDesc(QVector<Event> *vector);

	QDate getFirstDate();
	QDate getLastDate();
};

#endif // DATAHANDLER_H
