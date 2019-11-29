//
// Created by Intel on 27/11/2019.
//

#include "Container.h"

Container::Container(N x, N y): m_neighbors(4, nullptr), m_myRobot(nullptr), m_containedItems(0)
{
m_position.first = x;
m_position.second = y;
}

Container::~Container() {
    m_myRobot = nullptr; for (auto & neighbor: neighbors()) neighbor = nullptr;
}

pair<N, N> &Container::position() {
    return this->m_position;
}

vector<Container *> &Container::neighbors() {
    return m_neighbors;
}

vector<string> &Container::content() {
    return m_containedItems;
}

Robot *&Container::robot() {
    return m_myRobot;
}

bool Container::isOccupied() {
    return m_myRobot != nullptr ;
}

void Container::linkNeighbor(Container *nNeighbor, N side) {
    this->m_neighbors[side] = nNeighbor;
    nNeighbor->m_neighbors[(side + 2) % 4] = this;
}

void Container::addItem(const Texto &item) {
    m_containedItems.push_back(item);
}









