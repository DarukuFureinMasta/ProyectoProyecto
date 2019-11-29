//
// Created by Intel on 27/11/2019.
//
#include "Room.h"
#include "Robot.h"
#include "Container.h"

Room::Room(N cols, N rows)
: m_Containers(1, vector<Container*>(1, new Container(0, 0))),
m_ActiveRobots(0), m_currentTurn(0)                    {
for ( N i = 1; i < cols; ++i ) this->addColumn();
for ( N i = 1; i < rows; ++i ) this->addRow();
this->m_size = {cols, rows};
}


Room::~Room (){
    for (auto &vec : m_Containers) {
for (auto &container : vec)
container = nullptr; }
for(auto &robot : m_ActiveRobots)
robot = nullptr;}

vector<Robot *> &Room::robots() {
        return m_ActiveRobots;
}

vector<vector<Container *>> &Room::grid() {

        return m_Containers;

}

Container *&Room::atPosition(N x, N y) {

        return this->m_Containers.at(y).at(x);

}

void Room::addRow() {
        auto row = this->m_Containers.size();
        auto cols = m_Containers[0].size();
        this->m_Containers.emplace_back(cols, nullptr);

        for (N i = 0; i < cols; ++i) {
            m_Containers[row][i] = new Container(i, row);
            m_Containers[row][i]->linkNeighbor(m_Containers[row - 1][i], 0);

            if (i > 0)
                m_Containers[row][i]->linkNeighbor(m_Containers[row][i-1], 1);
        }
    }

void Room::addColumn() {


        auto col = m_Containers[0].size();
        for (auto &row : this->m_Containers)
            row.push_back(nullptr);

        for (N i = 0; i < m_Containers.size(); ++i)
        {
            m_Containers[i].back() = new Container(col, i);
            m_Containers[i][col]->linkNeighbor(m_Containers[i][col - 1], LEFT);

            if (i > 0) m_Containers[i][col]->linkNeighbor(m_Containers[i - 1][col], UP);
        }


}

void Room::printRoom() {
    std::cout << "****************************************\n****************************************\n";
    for (const auto &row : m_Containers)
    {
        for (const auto &cont : row)
        {
            auto links = cont->neighbors();
            std::cout << ((links[LEFT] != nullptr)? " -- ":"    ") << ((cont->isOccupied())?cont->robot()->identifier() : '*');
        }
        std::cout << '\n';
        for (const auto &cont : row)
        {
            auto links = cont->neighbors();
            std::cout << "    " << ((links[DOWN] != nullptr)?"|":" ");
        }
        std::cout << "\n";
    }
    std::cout << "****************************************\n****************************************\n";
}

void Room::placeRobot(N col, N row, Texto name) {
    auto nRobot = new Robot();
    auto & container = m_Containers[row][col];

    nRobot->rename(std::move(name));
    nRobot->spawnAt(container);
    nRobot->myRoomSize = this->m_size;

    m_ActiveRobots.push_back(nRobot);
}

void Room::controlRobots() {
    bool flag = false;
    do {
        flag = false;
        for ( m_currentTurn = 0; m_currentTurn < m_ActiveRobots.size(); m_currentTurn++ ) {
            auto & activeRobot = m_ActiveRobots[m_currentTurn];
            if (activeRobot->inDestination()) continue;
            else
            {
                if (!activeRobot->instructions().empty())
                    flag = true;
                else
                {
                    activeRobot->genPath();
                    if (!activeRobot->instructions().empty())
                    {
                        flag = true;
                    }
                    else continue;
                }
            }
            activeRobot->movetoNextPlace();
            printRoom();
        }
    } while ( flag );
}





