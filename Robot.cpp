//
// Created by Intel on 27/11/2019.
//

#include "Robot.h"

void Robot::genPath () {
    if (m_destination == nullptr) return;

    auto cPlace = this->m_place;
    N currentLevel = 1;
    vector<N> answer(0);

    vector<vector<bool>> visited (myRoomSize.second, vector<bool> (myRoomSize.first, false));
    vector<vector<N>> Levels (myRoomSize.second, vector<N>(myRoomSize.first, 0));
    vector<Container *> Queue;

    Queue.push_back(cPlace);

    while (! Queue.empty() ) {
        vector<Container *> nextQueue;

        for ( auto & cont : Queue ) {
            try {
                cPlace = cont;

                if (Levels.at(cPlace->m_position.second).at(cPlace->m_position.first) == 0)
                    Levels[cPlace->m_position.second][cPlace->m_position.first] = currentLevel;

                if (cPlace == this->m_destination)
                    goto rebuild;

                for (auto & adjacent : cPlace->neighbors()) {
                    try
                    {
                        if (adjacent == nullptr) continue;
                        if (! visited.at(adjacent->m_position.second).at(adjacent->m_position.first) &&
                            (! adjacent->isOccupied() || currentLevel > 3) )
                        {
                            visited[adjacent->m_position.second][adjacent->m_position.first] = true;
                            nextQueue.push_back( adjacent );
                        }
                    } catch (exception &) { continue; }
                }
            } catch (exception &) { continue; }
        }
        currentLevel++;
        Queue = nextQueue;
    }
    this->m_instructions = {};
    return;

    rebuild:

    for ( N i = Levels[cPlace->position().second][cPlace->position().first]; i > 1; --i ) {
        for ( N j = 0; j < cPlace->m_neighbors.size(); ++j) {
            auto & adjacent = cPlace->m_neighbors[j];
            try {
                if (adjacent == nullptr) continue;
                if (Levels[adjacent->position().second][adjacent->position().first] == i - 1) {
                    cPlace = adjacent;
                    answer.push_back((j+2) % 4);
                    break;
                }
            } catch (out_of_range &) {continue;}
        }
    }
    this->m_instructions = answer;
}

Robot::Robot()
        : m_place(nullptr), m_spawn(nullptr), m_name(), m_identifier(),
          m_heldItems(), m_instructions(), m_destination(nullptr) {

}

Robot::~Robot() {
    m_place = m_spawn = m_destination = nullptr;
}

char Robot::identifier() const {
    return m_identifier;
}

Texto Robot::name() const {
    return m_name;
}

Container *Robot::place() const {
    return m_place;
}

pair<N, N> Robot::position() const {
    return m_place->position();
}

vector<Texto> Robot::items() const {
    return m_heldItems;}

vector<N> &Robot::instructions() {
    return m_instructions;
}

bool Robot::inDestination() const {
    return m_place == m_destination;
}

void Robot::spawnAt(Container *&container) {
    m_place = container;
    m_spawn = container;
    m_destination = container;
    container->robot() = this;
}

void Robot::assignDestination(Container *&dContainer) {
    this->m_destination = dContainer;
}

void Robot::rename(Texto name) {
    m_name = name;
    m_identifier = name[0];
}

void Robot::giveItem(Texto item) {
    m_heldItems.push_back(std::move(item));
}

void Robot::dropItem(const Texto &item) {
    auto it = std::find(m_heldItems.begin(), m_heldItems.end(), item);
    if (it != m_heldItems.end()) {
        m_heldItems.erase(std::remove(m_heldItems.begin(), m_heldItems.end(), item), m_heldItems.end());
        m_place->content().push_back(item);
    }
}

void Robot::movetoNextPlace() {
    auto & pNeighbors = m_place->neighbors();
    auto & pNext = pNeighbors[m_instructions.back()];
    if (pNext->isOccupied()) {
        genPath();
        pNext = pNeighbors[m_instructions.back()];
    }
    pNeighbors[m_instructions.back()]->robot() = this;
    m_place->robot() = nullptr;
    m_place = pNeighbors[m_instructions.back()];
    m_instructions.pop_back();
}




