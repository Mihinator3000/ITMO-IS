#include "analytics.h"

#define INT32_MAX 2147483647

Coordinate::Coordinate(std::string s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == ',')
            s[i] = ' ';
        i++;
    }
    std::stringstream s_(s);
    s_ >> x;
    s_ >> y;
    check = false;
}

double distance(const Coordinate& a, const Coordinate& b)
{
	return sqrt(
           pow(a.getX() - b.getX(), 2) +
           pow(a.getY() - b.getY(), 2));
}

double route_len(std::vector<Coordinate>& v)
{
    double length = 0;
    int b = 0;
    int e = 0;
    v[b].check = true;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        double minlen = INT32_MAX;
        int minlen_id = 0;
        bool b_e;
        //0 - b, 1 - e
        bool cycle_check = false;
        for (unsigned int j = 0; j < v.size(); j++)
        {
            if (!v[j].check)
            {
                cycle_check = true;
                //std::cout << minlen << std::endl;
                double b_len = distance(v[b], v[j]);
                double e_len = distance(v[e], v[j]);
                if (b_len < minlen)
                {
                    minlen = b_len;
                    minlen_id = j;
                    b_e = 0;
                }
                if (e_len < minlen)
                {
                    minlen = e_len;
                    minlen_id = j;
                    b_e = 1;
                }
            }
        }
        if (!cycle_check)
            break;
        if (b_e)
        {
            e = minlen_id;
        }
        else
        {
            b = minlen_id;
        }
        v[minlen_id].check = true;
        length += minlen;
    }
    return length;
}

void Station::routes_fill(std::string s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == ',' || s[i] == '.')
            s[i] = ' ';
        i++;
    }
    std::stringstream s_(s);
    int route;
    while (s_ >> route)
    {
        routes.push_back(route);
    }
}


void Station::location_fill(std::string s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == ' ')
            if (s[i - 1] != ' ')
                s[i] = '|';
        if (s[i] == ',')
            s[i] = ' ';
        i++;
    }
    std::stringstream s_(s);
    std::string street;
    while (s_ >> street)
    {
        i = 0;
        while (street[i])
        {
            if (street[i] == '|')
            street[i] = ' ';
            i++;
        }
        location.push_back(street);
    }
}

Station::Station(std::vector<std::string>& input)
{
    number = stoi(input[0]);
    type_of_vehicle = input[1];
    object_type = input[2];
    name_stopping = input[3];
    the_official_name = input[4];
    location_fill(input[5]);
    routes_fill(input[6]);
    coordinates = Coordinate(input[7]);
};

void Info::file_reading(const char *filename)
{
    pugi::xml_document doc;
    doc.load_file(filename);
    pugi::xml_node dataset = doc.first_child();
    for (pugi::xml_node station = dataset.first_child(); station; station = station.next_sibling())
    {
        std::vector<std::string> input;
        for (pugi::xml_node info = station.first_child(); info; info = info.next_sibling())
        {
            input.push_back(info.first_child().value());
        }
        arr.push_back(Station(input));
    }
}

void Info::create_itinerary()
{
    for (unsigned int i = 0; i < arr.size(); i++)
    {
        for (unsigned int j = 0; j < arr[i].routes.size(); j++)
        {
            itinerary[arr[i].type_of_vehicle].m[arr[i].routes[j]].push_back(arr[i].coordinates);
        }
    }

    //fixed no firsts and seconds use auto& [key, value]
    for (auto& [key, value] : itinerary)
    {
        for (auto& [station_key, station_value] : value.m)
        {
            if ((int)station_value.size() > value.quantity)
            {
                value.quantity = station_value.size();
                value.quantity_id = station_key;
            }
            double length = route_len(station_value);
            if (value.len < length)
            {
                value.len = length;
                value.len_id = station_key;
            }
        }
    }
}

void Info::create_streets()
{
    for (unsigned int i = 0; i < arr.size(); i++)
    {
        for (unsigned int j = 0; j < arr[i].location.size(); j++)
        {
            streets[arr[i].location[j]]++;
        }
    }

    for (auto& [key, value] : streets)
    {
        if (value > street_count)
        {
            street_count = value;
            street = key;
        }
    }
}

Info::Info(const char *filename)
{
    street_count = 0;
    file_reading(filename);
    create_itinerary();
    create_streets();
}

void Info::max_station_route()
{
    for (auto& [key, value] : itinerary)
    {
        std::cout << key << " " << value.quantity_id << " (" << value.quantity << " stations)" << std::endl;
    }
}

void Info::max_length_route()
{
    for (auto& [key, value] : itinerary)
    {
        std::cout << key << " " << value.len_id << " (" << (int)(value.len * 100) << " km)" << std::endl;
    }
}

void Info::street_max()
{
    std::cout << street << " (with " << street_count << " stations)" << std::endl;
}
