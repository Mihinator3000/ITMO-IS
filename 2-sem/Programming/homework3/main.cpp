#include "analytics.h"

int main()
{
    system("chcp 65001");
    Info analysis = Info("data.xml");
    analysis.max_station_route();
    analysis.max_length_route();
    analysis.street_max();
    return 0;
}
