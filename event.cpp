#include "event.h"


QDate Event::getDate() {
	return this->date;
}

bool Event::magnitudeLessThan(Event &ev1, Event &ev2) {
	return ev1.getMagnitude() < ev2.getMagnitude();
}

bool Event::magnitudeGreaterThan(Event &ev1, Event &ev2) {
	return ev1.getMagnitude() > ev2.getMagnitude();
}

bool Event::dateLessThan(Event &ev1, Event &ev2) {
	return ev1.getDate() < ev2.getDate();
}

bool Event::dateGreaterThan(Event &ev1, Event &ev2) {
	return ev1.getDate() > ev2.getDate();
}

Event::Event(float magnitude, float latitude, float longitude, float depth, string date) {
	int year, month, day;
	const char *str = date.c_str();

	sscanf(str, "%d-%d-%d", &year, &month, &day);

	QDate *parsedDate = new QDate(year, month, day);

	this->magnitude = magnitude;
	this->latitude = latitude;
	this->longitude = longitude;
	this->depth = depth;
	this->date = *parsedDate;
}

Event::Event(float magnitude, float latitude, float longitude, float depth, QDate date) {
	this->magnitude = magnitude;
	this->latitude = latitude;
	this->longitude = longitude;
	this->depth = depth;
	this->date = date;
}

Event::Event() {
	Event(0, 0, 0, 0, "2000-01-01");
}

Event::~Event() {
	//delete &(this->date);
}

float Event::getMagnitude() {
	return this->magnitude;
}

float Event::getLongitude() {
	return this->longitude;
}

float Event::getLatitude() {
	return this->latitude;
}
