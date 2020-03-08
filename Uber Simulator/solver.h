// Copyright 2019 SD_Homework_Team
// Copyright[2019] <Livadaru Alexandru-Valentin 313CA>

#ifndef SOLVER_H_
#define SOLVER_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <queue>
#include <iomanip>
#include "./graph.h"
#include "./hashtable.h"

class Driver {
public:
	float rating;
	int distance;
	std::string name;
	int races;
	std::string currLoc;
	bool online;
	
	Driver(std::string name) {
		this->rating = 0;
		this->distance = 0;
		this->name = name;
		this->races = 0;
		this->online = 0;
	}

	Driver() {
		this->rating = 0;
		this->distance = 0;
		this->races = 0;
		this->online = 0;
	}

	~Driver() { }
};

class solver {
	private:
		int N, M;
		Dictionary<std::string, int> uber_hashtable;
		Graph<int> uber_graph;

	public:
		void task1_solver(std::ifstream& fin, std::ofstream& fout) {
			int Q1;
			int index1, index2, location, destination;
			fin >> N >> M;
			uber_hashtable.alloc_memory(N);
			uber_graph.set_size(N);
			std::string pair1, pair2, start, end;
			std::string text;
			for (int i = 0; i < N; ++i){
				fin >> text;
				uber_hashtable.insert(text, i);
			}
			for (int i = 0; i < M; ++i) {
				fin >> pair1 >> pair2;
				index1 = uber_hashtable.get(pair1);
				index2 = uber_hashtable.get(pair2);
				uber_graph.addEdge(index1, index2);
			}
			fin >> Q1;
			for (int i = 0; i < Q1; ++i) {
				fin >> start >> end;
				location = uber_hashtable.get(start);
				destination = uber_hashtable.get(end);
				if (uber_graph.BFS(location, destination, N, fout) != -1) {
					fout << "y" << "\n";
				} else {
					fout << "n" << "\n";
				}
			}
		}

		void task2_solver(std::ifstream& fin, std::ofstream& fout) {
			int Q2, coord1, coord2;
			std::string location1, location2;
			fin >> Q2;
			for (int i = 0; i < Q2; ++i) {
				fin >> location1 >> location2;
				coord1 = uber_hashtable.get(location1);
				coord2 = uber_hashtable.get(location2);
				fout << uber_graph.BFS(coord1, coord2, N, fout) << "\n";
			}
		}

		void task3_solver(std::ifstream& fin, std::ofstream& fout) {
			int Q3, index1, index2, grade;
			char type;
			std::string loc1, loc2, loc3;
			fin >> Q3;
			for (int i = 0; i < Q3; ++i) {
				fin >> type >> loc1 >> loc2 >> grade;
				index1 = uber_hashtable.get(loc1);
				index2 = uber_hashtable.get(loc2);
				if (type == 'c') {
					if (grade == 0) {
						uber_graph.addEdge(index1, index2);
					}
					if (grade == 1) {
						uber_graph.removeEdge(index1, index2);
						uber_graph.removeEdge(index2, index1);
					}
					if (grade == 2) {
						uber_graph.addEdge(index1, index2);
						uber_graph.addEdge(index2, index1);
					}
					if (grade == 3) {
						bool modification = 0;
						if (uber_graph.hasEdge(index1, index2) == 1 &&
						uber_graph.hasEdge(index2, index1) == 0) {
							uber_graph.removeEdge(index1, index2);
							uber_graph.addEdge(index2, index1);
							modification = 1;
						}
						if (uber_graph.hasEdge(index2, index1) == 1 &&
						uber_graph.hasEdge(index1, index2) == 0 && modification == 0) {
							uber_graph.removeEdge(index2, index1);
							uber_graph.addEdge(index1, index2);
						}
					}
				}
				if (type == 'q') {
					if (grade == 0) {
						if (uber_graph.BFS(index1, index2, N, fout) != -1) {
							fout << "y" << "\n";
						} else {
							fout << "n" << "\n";
						}
					}
					if (grade == 1) {
						fout << uber_graph.BFS(index1, index2, N, fout) << "\n";
					}
					if (grade == 2) {
						int a, index3, b;
						fin >> loc3;
						index3 = uber_hashtable.get(loc3);
						a = uber_graph.BFS(index1, index3, N, fout);
						b = uber_graph.BFS(index3, index2, N, fout);
						if (a == -1 || b == -1) {
							fout << "-1\n";
						} else {
							fout << (a + b) << "\n";
						}
					}
				}
			}
		}


		void task4_solver(std::ifstream& fin, std::ofstream& fout) {
			int Q4, nr_drivers, nr_riders = 0;
			std::vector<Driver> rider;
			std::string driver, currInter, operation;
			fin >> Q4;
			for (int i = 0; i < Q4; ++i) {
				fin >> operation;
				if (operation.length() == 1) {
					if (operation[0] == 'd') {
						fin >> driver >> currInter;
						auto j = rider.begin();
						bool flag = 0;
						for (j = rider.begin(); j != rider.end(); ++j) {
							if (j->name == driver) {
								flag = 1;
								rider[i].online = 1;
								rider[i].currLoc = currInter;
							}
						}
						if (flag == 0) {
							Driver variable(driver);
							rider.push_back(variable);
							rider[i].online = 1;
							rider[i].currLoc = currInter;
							++nr_riders;
						}
					}
					if (operation[0] == 'b') {
						fin >> driver;
						auto j = rider.begin();
						for (j = rider.begin(); j != rider.end(); ++j) {
							if (j->name == driver) {
								rider[i].online = 0;
							}
						}
					}
					if (operation[0] == 'r') {
						int rate;
						std::string start, end;
						fin >> start >> end >> rate;
						index1 = hashtable.get(start);
						index2 = hashtable.get(end);
						
					}
				}
				if (operation.compare("top_rating") == 0) {
					fin >> nr_drivers;
					if (nr_drivers > nr_riders) {
						nr_drivers = nr_riders;
					}
					for (int i = 0; i < nr_drivers; ++i) {
						for (int j = (i + 1); j < nr_drivers - 1; ++j) {
							if (rider[i].rating < rider[j].rating) {
								Driver aux = rider[i];
								rider[i] = rider[j];
								rider[j] = aux;
							}
							if (rider[i].rating == rider[j].rating && rider[i].name.compare(rider[j].name) < 0) {
								Driver aux = rider[i];
								rider[i] = rider[j];
								rider[j] = aux;
							}
						}
					}
					for (int i = 0; i < nr_drivers; ++i) {
						fout << rider[i].name << ":"; 
						fout << std::fixed << std::setprecision(3) << rider[i].rating << " "; 
					}
					fout << "\n";
				}
				if (operation.compare("top_dist") == 0) {
					fin >> nr_drivers;
					if (nr_drivers > nr_riders) {
						nr_drivers = nr_riders;
					}
					for (int i = 0; i < nr_drivers; ++i) {
						for (int j = (i + 1); j < nr_drivers - 1; ++j) {
							if (rider[i].distance < rider[j].distance) {
								Driver aux = rider[i];
								rider[i] = rider[j];
								rider[j] = aux;
							}
							if (rider[i].distance == rider[j].distance && rider[i].name.compare(rider[j].name) < 0) {
								Driver aux = rider[i];
								rider[i] = rider[j];
								rider[j] = aux;
							}
						}
					}
					for (int i = 0; i < nr_drivers; ++i) {
						fout << rider[i].name << ":" << rider[i].distance << " "; 
					}
					fout << "\n";
				}
				if (operation.compare("top_rides") == 0) {
					fin >> nr_drivers;
					if (nr_drivers > nr_riders) {
						nr_drivers = nr_riders;
					}
					for (int i = 0; i < nr_drivers; ++i) {
						for (int j = (i + 1); j < nr_drivers - 1; ++j) {
							if (rider[i].races < rider[j].races) {
								Driver aux = rider[i];
								rider[i] = rider[j];
								rider[j] = aux;
							}
							if (rider[i].races == rider[j].races && rider[i].name.compare(rider[j].name) < 0) {
								Driver aux = rider[i];
								rider[i] = rider[j];
								rider[j] = aux;
							}
						}
					}
					for (int i = 0; i < nr_drivers; ++i) {
						fout << rider[i].name << ":" << rider[i].races << " "; 
					}
					fout << "\n";
				}
				if (operation.compare("info") == 0) {
					fin >> driver;
					for (int i = 0; i < nr_riders; ++i) {
						if (rider[i].name == driver) {
							if (rider[i].online == 1) {
								fout << rider[i].name << ":" << " " << rider[i].currLoc << " " << rider[i].rating
								<< " " << rider[i].races << " " << rider[i].distance << " " << "online" << "\n";
							} else {
								fout << rider[i].name << ":" << " " << rider[i].currLoc << " " << rider[i].rating
								<< " " << rider[i].races << " " << rider[i].distance << " " << "offline" << "\n";
							}
						}
					}
				}
			}
		}

		void task5_solver(std::ifstream& fin, std::ofstream& fout) { }
};
#endif  // SOLVER_H_
