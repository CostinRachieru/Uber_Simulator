// Copyright 2019 SD_Homework_Team

#ifndef SOLVER_H_
#define SOLVER_H_

#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include "Hashtable.h"
#include "HashFunctions.h"
#include "ListGraph.h"
#include "Driver.h"

class solver {
	Hashtable<std::string, int> *Table;
	ListGraph<int> *Graph;
	Hashtable<std::string, int> *DriversTable;
	Driver *Drivers_info;
	int size;
	int N;
	int M;
	int nr_drivers;

	public:
		solver() {
			Table = new Hashtable<std::string, int>(500, &hash);
			Graph = new ListGraph<int>(500);
			DriversTable = new Hashtable<std::string, int>(500, &hash);
			nr_drivers = 0;
		}
		~solver() {
			delete Table;
			delete Graph;
			delete DriversTable;
			delete[] Drivers_info;
		}
		void task1_solver(std::ifstream& fin, std::ofstream& fout) {
			int i, NR;
			std::string intersection_name1, intersection_name2;
			fin >> N >> M;

			// Puts every intersection in a Hashtable. The value it's the ID.
			for (i = 0; i < N; i++) {
				fin >> intersection_name1;
				Table->put(intersection_name1, i);
			}

			// Puts the Edges in the Graph class.
			for (i = 0; i < M; i++) {
				fin >> intersection_name1 >> intersection_name2;
				Graph->addEdge(Table->get(intersection_name1),
				 Table->get(intersection_name2));
				Graph->addName(Table->get(intersection_name1),
				 intersection_name1);
				Graph->addName(Table->get(intersection_name2),
					intersection_name2);
			}

			fin >> NR;
			// Shows if there is any path between the given nodes.
			for (i = 0; i < NR; i++) {
				fin >> intersection_name1 >> intersection_name2;
				if (Graph->isPath(Table->get(intersection_name1),
				 Table->get(intersection_name2))) {
					fout << "y" << std::endl;
				} else {
					fout<< "n" << std::endl;
				}
			}
		}

		void task2_solver(std::ifstream& fin, std::ofstream& fout) {
			int NR;
			std::string intersection_name1, intersection_name2;

			fin >> NR;
			// Prints the distance between the 2 given nodes.
			for (int i = 0; i < NR; i++) {
				fin >> intersection_name1 >> intersection_name2;
				fout << Graph->Distance(Table->get(intersection_name1),
				 Table->get(intersection_name2)) << std::endl;
			}
		}

		void task3_solver(std::ifstream& fin, std::ofstream& fout) {
			int NR, node1, node2, node3, dist1, OPTION, dist2;
			std::string int_name1, int_name2, int_name3;
			char c;

			fin >> NR;

			for (int i = 0; i < NR; i++) {
				fin >> c;
				fin >> int_name1 >> int_name2;
				node1 = Table->get(int_name1);
				node2 = Table->get(int_name2);
				fin >> OPTION;

				// Adds Edge.
				if (c == 'c' && OPTION == 0) {
					if (!Graph->hasEdge(node1, node2)){
						Graph->addEdge(node1, node2);
					}
				}

				// Removes Edge.
				if (c == 'c' && OPTION == 1) {
					Graph->removeEdge(node1, node2);
					Graph->removeEdge(node2, node1);
				}

				// Makes an one-way road into a two-way road.
				if (c == 'c' && OPTION == 2) {
					if (!Graph->hasEdge(node1, node2)) {
						Graph->addEdge(node1, node2);
					}
					if (!Graph->hasEdge(node2, node1)) {
						Graph->addEdge(node2, node1);
					}
				}

				// Inverts road's way.
				if (c == 'c' && OPTION == 3) {
					if (Graph->hasEdge(node1, node2)) {
						if (!Graph->hasEdge(node2, node1)) {
							Graph->removeEdge(node1, node2);
							Graph->addEdge(node2, node1);
						}
					} else {
						if (Graph->hasEdge(node2, node1)) {
							Graph->removeEdge(node2, node1);
							Graph->addEdge(node1, node2);
						}
					}
				}

				// Prints if there is any path between the 2 given nodes.
				if (c == 'q' && OPTION == 0) {
					if (Graph->isPath(node1, node2)) {
						fout << "y" << std::endl;
					} else {
						fout << "n" << std::endl;
					}
				}

				// Prints the distance between the 2 given nodes.
				if (c == 'q' && OPTION == 1) {
					fout << Graph->Distance(node1, node2) << std::endl;
				}

				//  Prints the distance between the 2 given nodes going through
				// a third node.
				if (c == 'q' && OPTION == 2) {
					fin >> int_name3;
					node3 = Table->get(int_name3);
					dist1 = Graph->Distance(node1, node3);
					if (dist1 == -1) {
						fout << "-1" << std::endl;
					} else {
						dist2 = Graph->Distance(node3, node2);
						if (dist2 == -1) {
							fout << "-1" << std::endl;
						} else {
							fout << dist1 + dist2 << std::endl;
						}
					}
				}
			}
		}

		void task4_solver(std::ifstream& fin, std::ofstream& fout) {
			int NR, i;
			int number;
			std::string arg1, arg2;
			std::string c;
			fin >> NR;
			Drivers_info = new Driver[500];

			for (int w = 0; w < NR; w++) {
				fin >> c;

				// The drives goes online on the app.
				if (c == "d") {
					int is_already = 0;
					fin >> arg1 >> arg2;
					//   Checks if it is the first time for this driver and
					// makes changes accordingly.
					for (int i = 0; i < nr_drivers; i++) {
						if (Drivers_info[i].get_name() == arg1) {
							is_already = 1;
							Drivers_info[i].set_on(1);
							Drivers_info[i].set_locationname(arg2);
							Drivers_info[i].set_location(Table->get(arg2));
						}
					}

					// This case if it s the first time for this driver.
					if (is_already == 0) {
						DriversTable->put(arg1, nr_drivers);
						Drivers_info[nr_drivers] = Driver(Table->get(arg2));
						Drivers_info[nr_drivers].set_name(arg1);
						Drivers_info[nr_drivers].set_id(nr_drivers);
						Drivers_info[nr_drivers].set_locationname(arg2);
						nr_drivers++;
					}
				}

				// The driver goes offline.
				if (c == "b") {
					fin >> arg1;
					for (int i = 0; i < nr_drivers; i++) {
						if (Drivers_info[i].get_name() == arg1){
							Drivers_info[i].set_on(0);
							break;
						}
					}
				}

				// There is a ride request.
				if (c == "r") {
					int i, start_node, end_node, min_dist = 500, ok = 0,
					closest_driver, closest_location, driver_location, distance;
					float rating;
					fin >> arg1 >> arg2 >> rating;
					start_node = Table->get(arg1);
					end_node = Table->get(arg2);

					//     Checks which driver is the most apropiate one
					// to take this ride
					for (i = 0; i < nr_drivers; i++) {
						driver_location = Drivers_info[i].get_location();
						distance = Graph->Distance(driver_location, start_node);
						// Driver must be online.
						if (Drivers_info[i].get_on() == 1) {
							if (distance >= 0 && distance < min_dist) {
								ok = 1;
								closest_driver = i;
								closest_location = driver_location;
								min_dist = distance;
							} else if (distance == min_dist) {  // Sort them
								// by their ratings
								if (Drivers_info[closest_driver].get_rating() <
								Drivers_info[i].get_rating()) {
									closest_driver = i;
									closest_location = driver_location;
									min_dist = distance;
								} else {
								// or by their names.
									if (Drivers_info[i].get_name() <
									Drivers_info[closest_driver].get_name()) {
										closest_driver = i;
										closest_location = driver_location;
										min_dist = distance;
									}
								}
							}
						}
					}

					//     The case when there is a driver able to get to the
					// starting point.
					if (ok == 1) {
						int dist2 = Graph->Distance(start_node, end_node);
						// The driver can get to the destination.
						if (dist2 >= 0) {
							int dist1 = Graph->Distance(closest_location, start_node);
							Drivers_info[closest_driver].add_race(rating, dist1 + dist2, end_node);
							Drivers_info[closest_driver].set_locationname(arg2);
						} else {  // The driver can't get the destination.
							int do_smth = 0;
							//     Finds a neighbour of the destination where the driver
							// can get it's passenger.
							for (int i = 0;
							i < (int)Graph->nodes[end_node].neighbors.size(); i++) {
								int neigh = Graph->nodes[end_node].neighbors[i];
								int neigh_dist = Graph->Distance(start_node, neigh);
								int dist = Graph->Distance(closest_location, start_node);
								if (neigh_dist >= 0) {
									do_smth = 1;
									Drivers_info[closest_driver].add_race
									 (rating, dist + neigh_dist, neigh);
									Drivers_info[closest_driver].set_locationname
									 (Graph->nodes[neigh].name);
									break;
								}
							}

							// Case when there is no accesible neighbour.
							if (do_smth == 0) {
								fout << "Destinatie inaccesibila" << std::endl;
							}
						}
					} else {  //   Case when there are no drivers that can get
							  // to the starting point of the ride.
						fout << "Soferi indisponibili" << std::endl;
					}
				}

				//     Displays the top of drivers sorted by
				// their distance driven.
				if (c == "top_dist") {
					Driver aux;
					int max_dist = -1, max_id;
					fin >> number;
					//     If the number requested of drivers is more than the
					// actual number of drivers the program doesn t care.
					if (number > nr_drivers) {
						number = nr_drivers;
					}
					//     Finds the first "number" drivers of the top and
					// puts them first in Drivers_info.
					for (i = 0; i < number; i++) {
						max_dist = -1;
						for (int j = i; j < nr_drivers; j++) {
							if (Drivers_info[j].get_distance() > max_dist) {
								max_dist = Drivers_info[j].get_distance();
								max_id = j;
							}
							if (Drivers_info[j].get_distance() == max_dist) {
								// Second sort by their name.
								if (Drivers_info[j].get_name() <
								Drivers_info[max_id].get_name()) {
									max_id = j;
								}
							}
						}
						aux = Drivers_info[max_id];
						Drivers_info[max_id] = Drivers_info[i];
						Drivers_info[i] = aux;
					}
					for (i = 0; i < number; i++) {
						fout << Drivers_info[i].get_name() << ":" <<
						Drivers_info[i].get_distance() << " ";
					}
					fout << std::endl;
				}

				//     Displays the top of drivers sorted by
				// their distance driven.
				if (c == "top_rating") {
					Driver aux;
					float max_rating = -1;
					int max_id = 0;
					fin >> number;
					//     If the number requested of drivers is more than the
					// actual number of drivers the program doesn t care.
					if (number > nr_drivers) {
						number = nr_drivers;
					}
					//     Finds the first "number" drivers of the top and
					// puts them first in Drivers_info.
					for (i = 0; i < number; i++) {
						max_rating = -1;
						for (int j = i; j < nr_drivers; j++) {
							if (Drivers_info[j].get_rating() == max_rating) {
								// Second sort by their name.
								if (Drivers_info[j].get_name() <
								Drivers_info[max_id].get_name()) {
									max_id = j;
								}
							}
							if (Drivers_info[j].get_rating() > max_rating) {
								max_rating = Drivers_info[j].get_rating();
								max_id = j;
							}
						}
						aux = Drivers_info[max_id];
						Drivers_info[max_id] = Drivers_info[i];
						Drivers_info[i] = aux;
					}
					for (i = 0; i < number; i++) {
						fout << Drivers_info[i].get_name() << ":";
						fout << std::fixed;
						fout << std::setprecision(3);
						fout << Drivers_info[i].get_rating() << " ";
						fout << std::setprecision(1);
					}
					fout << std::endl;
				}

				//     Displays the top of drivers sorted by
				// their number of rides completed.
				if (c == "top_rides") {
					Driver aux;
					int max_rides = -1, max_id = 0;
					fin >> number;
					//     If the number requested of drivers is more than the
					// actual number of drivers the program doesn t care.
					if (number > nr_drivers) {
						number = nr_drivers;
					}
					//     Finds the first "number" drivers of the top and
					// puts them first in Drivers_info.
					for (i = 0; i < number; i++) {
						max_rides = -1;
						for (int j = i; j < nr_drivers; j++) {
							if (Drivers_info[j].get_races() == max_rides) {
								// Second sort by their name.
								if (Drivers_info[j].get_name() <
								Drivers_info[max_id].get_name()) {
									max_id = j;
								}
							}
							if (Drivers_info[j].get_races() > max_rides) {
								max_rides = Drivers_info[j].get_races();
								max_id = j;
							}
						}
						aux = Drivers_info[max_id];
						Drivers_info[max_id] = Drivers_info[i];
						Drivers_info[i] = aux;
					}
					for (i = 0; i < number; i++) {
						fout << Drivers_info[i].get_name() << ":" <<
						Drivers_info[i].get_races() << " ";
					}
					fout << std::endl;
				}

				// Prints the information requested about a driver.
				if (c == "info") {
					std::string name;
					fin >> name;
					int id = DriversTable->get(name);
					for (int i = 0; i < nr_drivers; i++) {
						if (Drivers_info[i].get_id() == id) {
							fout << Drivers_info[i].get_name() << ": " <<
							Drivers_info[i].get_locationname() << " ";
							fout << std::fixed;
							fout << std::setprecision(3);
							fout << Drivers_info[i].get_rating() << " ";
							fout << std::setprecision(1);
							fout << Drivers_info[i].get_races() << " " <<
							Drivers_info[i].get_distance();
							if (Drivers_info[i].get_on() == 1) {
								fout << " online" << std::endl;
							} else {
								fout << " offline" << std::endl;
							}
						}
					}
				}
			}
		}

		void task5_solver(std::ifstream& fin, std::ofstream& fout) {
			int fuel, NR, is_already, auxx;
			std::string driver, aux;
			fin >> fuel >> driver;
			int start_node;
			// Finds the location of the driver.
			for (int k = 0; k < nr_drivers; k++) {
				if (Drivers_info[k].get_name() == driver) {
					start_node = Drivers_info[k].get_location();
				}
			}
			fin >> NR;
			std::string intersections[NR];
			int fuel_needed[NR];
			for (int i = 0; i < NR; i++) {
				fin >> aux;
				is_already = 0;
				// The program makes sure that there are no duplicates.
				for (int j = 0; j < i; j++) {
					if (aux == intersections[j]) {
						i--;
						NR--;
						is_already = 1;
					}
				}
				//     Makes an array which contains the amount of fuel needed
				// to get to each intersection.
				if (is_already == 0) {
					intersections[i] = aux;
					int end_node = Table->get(aux);
					fuel_needed[i] = Graph->Distance(start_node, end_node);
				}
			}
		// Sorts the intersections by the amount of fuel needed to get there.
			for (int i = 0; i < NR - 1; i++) {
				for (int j = i + 1; j < NR; j++) {
					if (fuel_needed[i] == fuel_needed[j]) {
						if (intersections[j] < intersections[i]) {
							auxx = fuel_needed[i];
							aux = intersections[i];
							fuel_needed[i] = fuel_needed[j];
							intersections[i] = intersections[j];
							fuel_needed[j] = auxx;
							intersections[j] = aux;
						}
					}
					if (fuel_needed[j] < fuel_needed[i]) {
						auxx = fuel_needed[i];
						aux = intersections[i];
						fuel_needed[i] = fuel_needed[j];
						intersections[i] = intersections[j];
						fuel_needed[j] = auxx;
						intersections[j] = aux;
					}
				}
			}
			for (int i = 0; i < NR; i++) {
				if (fuel_needed[i] > -1) {
					if (fuel < fuel_needed[i]) {
						break;
					}
					fout << intersections[i] << " ";
				}
			}
		}
};
#endif  // SOLVER_H_
