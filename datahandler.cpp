#include "datahandler.h"
#include <QDomDocument>
#include <QFile>
#include <QtAlgorithms>
#include <string>
#include <cstdlib>

DataHandler::DataHandler() {
};

int DataHandler::parseXML(const string name) {
	QDomDocument doc;
	int i;
	Event *ev;

	this->events = new QVector<Event>();
	int x;

	QFile file(*(new QString(name.c_str())));
	if (x = !file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
		//qDebug(name.c_str());
		return 1;
	}

	QDomNodeList fileEvents = doc.elementsByTagName("event");
	//qDebug(to_string(fileEvents.size()).c_str());
	for (int i = 0; i < fileEvents.size(); i++) {
		QDomNode node = fileEvents.item(i);
		QDomElement magnitude = node.firstChildElement("magnitude").firstChildElement("mag");
		QDomElement origin = node.firstChildElement("origin");
		QDomElement latitude = origin.firstChildElement("latitude").firstChildElement("value");
		QDomElement longitude = origin.firstChildElement("longitude").firstChildElement("value");
		QDomElement depth = origin.firstChildElement("depth").firstChildElement("value");
		QDomElement time = origin.firstChildElement("time").firstChildElement("value");
		if (magnitude.isNull() || origin.isNull() || latitude.isNull() || longitude.isNull() ||
				depth.isNull() || time.isNull()) {
			continue;
		}

		ev = new Event(strtod(magnitude.text().toStdString().c_str(), NULL),
				strtod(latitude.text().toStdString().c_str(), NULL),
				strtod(longitude.text().toStdString().c_str(), NULL),
				strtod(depth.text().toStdString().c_str(), NULL), time.text().toStdString());
		this->events->append(*ev);
	}

	this->sortByDateAsc();
	this->firstDate = this->events->first().getDate();
	this->lastDate = this->events->last().getDate();

	return 0;
}

QVector<double>* DataHandler::getTimeSeries() {
	int i;
	QVector<Event> *evVector = new QVector<Event>(*this->events);
	QVector<double> *timeSeries = new QVector<double>;
	Event *ev, *evN;

	DataHandler::sortVectorByDateAsc(evVector);

	//qDebug(to_string(evVector->length()).c_str());
	//remove date duplicates and keep maximum magnitude
	for (i = 0; i < evVector->length() - 1; i++) {
		ev = &((*evVector)[i]);
		evN = &((*evVector)[i + 1]);
		if (ev->getDate() == evN->getDate()) {
			if (ev->getMagnitude() < evN->getMagnitude()) {
				evVector->remove(i);
				i--;
			}
			else {
				evVector->remove(i + 1);
				i--;
			}
		}
	}

	//qDebug(to_string(evVector->length()).c_str());
	QDate start = evVector->first().getDate();
	QDate end = evVector->last().getDate();

	int days = start.daysTo(end);
	int j = 0;
	//qDebug(to_string(days).c_str());

	for (i = 0; i < days; i++) {
		ev = &((*evVector)[j]);
		if (start.addDays(i) == ev->getDate()) {
			timeSeries->append(ev->getMagnitude());
			j++;
		}
		else {
			timeSeries->append(0);
		}
	}

	return timeSeries;
}

void DataHandler::sortByMagnitudeAsc() {
	DataHandler::sortVectorByMagnitudeAsc(this->events);
};
void DataHandler::sortByMagnitudeDesc() {
	qSort(this->events->begin(), this->events->end(), Event::magnitudeGreaterThan);
};

void DataHandler::sortByDateAsc() {
	qSort(this->events->begin(), this->events->end(), Event::dateLessThan);
};
void DataHandler::sortByDateDesc() {
	qSort(this->events->begin(), this->events->end(), Event::dateGreaterThan);
};

void DataHandler::sortVectorByMagnitudeAsc(QVector<Event> *vector) {
	qSort(vector->begin(), vector->end(), Event::magnitudeLessThan);
};
void DataHandler::sortVectorByMagnitudeDesc(QVector<Event> *vector) {
	qSort(vector->begin(), vector->end(), Event::magnitudeGreaterThan);
};

void DataHandler::sortVectorByDateAsc(QVector<Event> *vector) {
	qSort(vector->begin(), vector->end(), Event::dateLessThan);
};
void DataHandler::sortVectorByDateDesc(QVector<Event> *vector) {
	qSort(vector->begin(), vector->end(), Event::dateGreaterThan);
}

QDate DataHandler::getFirstDate() {
	return this->firstDate;
};

QDate DataHandler::getLastDate() {
	return this->lastDate;
};
