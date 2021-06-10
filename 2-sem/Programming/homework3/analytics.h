#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include "pugixml-1.11/src/pugixml.hpp"
#include <map>
#include <algorithm>

class Coordinate
{
private:
    double x;
    double y;
public:
    bool check;
    Coordinate() {x = 0; y = 0; check = false;}
    Coordinate(std::string);
    double getX() const {return x;}
    double getY() const {return y;}
};

double distance(const Coordinate&, const Coordinate&);

double route_len(std::vector<Coordinate>&);

class Station
{
private:
    void routes_fill(std::string);
    void location_fill(std::string);
public:
    int number;
    std::string type_of_vehicle;
    std::string object_type;
    std::string name_stopping;
    std::string the_official_name;
    std::vector<std::string> location;
    std::vector<int> routes;
    Coordinate coordinates;
    Station(std::vector<std::string>&);
};

class Route
{
public:
    std::map<int, std::vector<Coordinate>> m;
    double len;
    int len_id;
    int quantity;
    int quantity_id;
    Route() {len = 0; len_id = 0; quantity = 0; quantity_id = 0;}
};

class Info
{
private:
    std::vector<Station> arr;
    std::map<std::string, Route> itinerary;
    std::map<std::string, int> streets;
    void file_reading(const char*);
    void create_itinerary();
    void create_streets();
    std::string street;
    int street_count;
public:
    Info(const char*);
    void max_station_route();
    void max_length_route();
    void street_max();
};

#endif // ANALYTICS_H
