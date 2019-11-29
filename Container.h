//
// Created by Intel on 27/11/2019.
//

#ifndef UNTITLED5_CONTAINER_H
#define UNTITLED5_CONTAINER_H

#include "tipes.h"

#include "Room.h"
class Room;
#include "Robot.h"
class Robot;
class Container {
private:
    pair<N, N>          m_position;
    vector<Container*>  m_neighbors;
    vector<Texto>      m_containedItems;
    Robot *             m_myRobot;
public:
    /** Constructor y destructor */
    Container(N x, N y);

    ~Container() ;

    /** referencias a var. privadas */
    pair<N, N>         &position ()                                  ;

    vector<Container*> &neighbors ()                                 ;

    vector<Texto>     &content ()                                   ;

    Robot *            &robot ()                                     ;

    bool                isOccupied ()                                ;

    /** enlaza dos containers */
    void                linkNeighbor (Container * nNeighbor, N side) ;

    /** agrega un item al container */
    void                addItem (const Texto& item)                 ;

    friend class Robot;
    friend class Room;
};

#endif //UNTITLED5_CONTAINER_H
