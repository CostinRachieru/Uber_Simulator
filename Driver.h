// Copyright 2019 Rachieru Costin Tudor <<costinrch46@gmail.com>>

#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>

class Driver {
 private:
	std::string name;
	std::string location_name;
	float rating;
	int nr_races;
	int distance;
	int location;
	int on;
	int id;

 public:
	// Constructor - Default
	Driver() {
		this->name = "name";
		this->location_name = "name";
		this->rating = 0;
		this->nr_races = 0;
		this->distance = 0;
		this->location = -1;
		this->on = 0;
		this->id = -1;
	}

	// Other Constructor
	explicit Driver(int location) {
		this->name = "name";
		this->location_name = "name";
		this->rating = 0;
		this->nr_races = 0;
		this->distance = 0;
		this->location = location;
		this->on = 1;
		this->id = -1;
	}

	void set_name(std::string name) {
		this->name = name;
	}
	std::string get_name() {
		return name;
	}

	void set_locationname(std::string name) {
		this->location_name = name;
	}

	std::string get_locationname() {
		return location_name;
	}

	// Adds a finished ride for this driver and make changes accrodingly.
	void add_race(int rating, int distance, int end_node) {
		this->rating = (this->rating * nr_races + rating);
		nr_races++;
		this->rating = this->rating / nr_races;
		this->distance += distance;
		this->location = end_node;
	}

	float get_rating() {
		return rating;
	}

	void set_on(int on) {
		this->on = on;
	}

	int get_on() {
		return on;
	}

	void set_races(int nr_races) {
		this->nr_races = nr_races;
	}

	int get_races() {
		return nr_races;
	}

	int get_distance() {
		return distance;
	}

	void set_location(int location) {
		this->location = location;
	}

	int get_location() {
		return location;
	}

	void set_id(int id) {
		this->id = id;
	}

	int get_id() {
		return id;
	}

	void operator=(Driver other) {
		this->name = other.name;
		this->location_name = other.location_name;
		this->rating = other.rating;
		this->nr_races = other.nr_races;
		this->distance = other.distance;
		this->location = other.location;
		this->on = other.on;
		this->id = other.id;
	}
};

#endif  // DRIVER_H_
