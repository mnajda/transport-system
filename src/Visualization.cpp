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
constexpr auto offsetX = 12;
constexpr auto offsetY = 40;
} // namespace

Visualization::Visualization(std::vector<Train>& trains, std::vector<TrainStation>& trainStations, Map& map)
    : map(map)
    , trains(trains)
    , trainStations(trainStations)
{
    startCurses();
    createWindows();
}

Visualization::~Visualization()
{
    delwin(mapWindow);
    delwin(trainsWindow);
    delwin(stationsWindow);

    endwin();
}

void Visualization::start(bool& isRunning)
{
    while (isRunning)
    {
        displayMap();
        displayTrains();
        displayTrainStations();
        displaySingleRailway();
        displayTrainsCargo();
        displayStationsCargo();
    }
}

void Visualization::stopOnButtonPress(bool& isRunning)
{
    while (true)
    {
        if (getch())
        {
            isRunning = false;
            notifyStation({0, 0});
            notifyStation({0, 7});
            notifyStation({7, 0});
            notifyStation({7, 7});
            return;
        }
    }
}

void Visualization::startCurses()
{
    initscr();
    start_color();
    curs_set(0);
    refresh();
}

void Visualization::createWindows()
{
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    getmaxyx(stdscr, columns, lines);
    mapWindow = newwin(columns, lines / 2, 0, 50);
    trainsWindow = newwin(columns, (lines / 4) + 3, 0, 0);
    stationsWindow = newwin(columns, lines / 4, 0, lines - 46);

    wbkgd(mapWindow, COLOR_PAIR(1));
    wbkgd(trainsWindow, COLOR_PAIR(1));
    wbkgd(stationsWindow, COLOR_PAIR(1));

    box(mapWindow, 0, 0);
    box(trainsWindow, 0, 0);
    box(stationsWindow, 0, 0);
}

void Visualization::displayMap()
{
    auto size = map.fields.size();

    for (auto i = 0; i < size; ++i)
    {
        for (auto k = 0; k < map.fields[i].size(); ++k)
        {
            if (map[i][k].id == -1)
            {
                mvwaddch(mapWindow, i + offsetX, k + offsetY, ' ');
            }
        }
    }

    wrefresh(mapWindow);
}

void Visualization::displayTrains()
{
    for (const auto& train : trains)
    {
        const auto[x, y] = train.getTrainPosition();

        mvwaddch(mapWindow, x + offsetX, y + offsetY, train.getTrainChar());
    }

    wrefresh(mapWindow);
}

void Visualization::displayTrainStations()
{
    for (const auto& station : trainStations)
    {
        const auto[x, y] = station.getStationPosition();

        mvwaddch(mapWindow, x + offsetX, y + offsetY, '#');
    }

    wrefresh(mapWindow);
}

void Visualization::displaySingleRailway()
{
    auto size = map.fields.size();

    for (auto i = 0; i < size; ++i)
    {
        for (auto k = 0; k < map.fields[i].size(); ++k)
        {
            if (map[i][k].id == -3)
            {
                mvwaddch(mapWindow, i + offsetX, k + offsetY, '|');
            }
        }
    }

    wrefresh(mapWindow);
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

    wrefresh(trainsWindow);
}

void Visualization::displayStationsCargo()
{
    auto size = trainStations.size();
    auto j = 1;
    for (decltype(size) i = 0; i < size; ++i, j += 5)
    {
        auto& currentCargo = trainStations[i].getCurrentCargo();
        const auto[loaded, unloaded] = trainStations[i].getAvailableCargo();
        auto loadedCargoAmount = std::to_string(currentCargo[loaded]);
        auto unloadedCargoAmount = std::to_string(currentCargo[unloaded]);

        mvwaddstr(stationsWindow, j, 2, (station + std::to_string(i)).c_str());
        mvwaddstr(stationsWindow, j + 1, 2, (loaded + ": " + loadedCargoAmount).c_str());
        mvwaddstr(stationsWindow, j + 2, 2, (unloaded + ": " + unloadedCargoAmount).c_str());
        mvwaddstr(stationsWindow, j + 3, 2, "--------------------------------------");
        mvwaddstr(stationsWindow, j + 4, 2, "");
    }

    wrefresh(stationsWindow);
}

void Visualization::notifyStation(Position pos)
{
    std::unique_lock<std::mutex> lock(map[pos.x][pos.y].mutex);
    map[pos.x][pos.y].cv.notify_one();
}
