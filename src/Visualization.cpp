#include "Visualization.hpp"

#include <iostream>

namespace
{
constexpr auto station = "Station nr ";
constexpr auto train = "Train nr ";
constexpr auto fruits = "Fruits: ";
constexpr auto vegetables = "Vegetables: ";
constexpr auto beer = "Beer: ";
constexpr auto fruitsKey = "Fruits";
constexpr auto vegetablesKey = "Vegetables";
constexpr auto beerKey = "Beer";
} // namespace

Visualization::Visualization(std::vector<Train>& trains, std::vector<TrainStation>& trainStations)
    : trains(trains)
    , trainStations(trainStations)
{
    initscr();
    start_color();
    curs_set(0);
    refresh();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    getmaxyx(stdscr, columns, lines);
    mapWindow = newwin(columns, lines / 2, 0, 50);
    trainsWindow = newwin(columns, (lines / 4) + 3, 0, 0);
    stationsWindow = newwin(columns, lines / 4, 0, lines - 46);

    std::string test = "0";

    wbkgd(mapWindow, COLOR_PAIR(1));
    wbkgd(trainsWindow, COLOR_PAIR(1));
    wbkgd(stationsWindow, COLOR_PAIR(1));

    box(mapWindow, 0, 0);
    box(trainsWindow, 0, 0);
    box(stationsWindow, 0, 0);

    displayTrainsCargo();
    displayStationsCargo();

    wrefresh(mapWindow);
    wrefresh(trainsWindow);
    wrefresh(stationsWindow);

    getch();
}

Visualization::~Visualization()
{
    delwin(mapWindow);
    delwin(trainsWindow);
    delwin(stationsWindow);

    endwin();
}

void Visualization::displayTrainsCargo()
{
    auto size = trains.size();
    auto j = 1;
    for (decltype(size) i = 0; i < size; ++i, j += 6)
    {
        auto& cargo = trains[i].getTrainsCargo();

        mvwaddstr(trainsWindow, j, 2, (train + std::to_string(i)).c_str());
        mvwaddstr(trainsWindow, j + 1, 2, (fruits + std::to_string(cargo[fruitsKey])).c_str());
        mvwaddstr(trainsWindow, j + 2, 2, (vegetables + std::to_string(cargo[vegetablesKey])).c_str());
        mvwaddstr(trainsWindow, j + 3, 2, (beer + std::to_string(cargo[beerKey])).c_str());
        mvwaddstr(trainsWindow, j + 4, 2, "--------------------------------------");
        mvwaddstr(trainsWindow, j + 5, 2, "");
    }
}

void Visualization::displayStationsCargo()
{
    auto size = trainStations.size();
    auto j = 1;
    for (decltype(size) i = 0; i < size; ++i, j += 5)
    {
        auto& currentCargo = trainStations[i].getCurrectCargo();
        auto availableCargo = trainStations[i].getAvailableCargo();
        auto loadedCargoAmount = std::to_string(currentCargo[availableCargo.loaded]);
        auto unloadedCargoAmount = std::to_string(currentCargo[availableCargo.unloaded]);

        mvwaddstr(stationsWindow, j, 2, (station + std::to_string(i)).c_str());
        mvwaddstr(stationsWindow, j + 1, 2, (availableCargo.loaded + ": " + loadedCargoAmount).c_str());
        mvwaddstr(stationsWindow, j + 2, 2, (availableCargo.unloaded + ": " + unloadedCargoAmount).c_str());
        mvwaddstr(stationsWindow, j + 3, 2, "--------------------------------------");
        mvwaddstr(stationsWindow, j + 4, 2, "");
    }
}
