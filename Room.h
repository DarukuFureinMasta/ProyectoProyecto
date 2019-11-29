//
// Created by Intel on 27/11/2019.
//

#ifndef UNTITLED5_ROOM_H
#define UNTITLED5_ROOM_H

#include "tipes.h"

#include "Container.h"

class Container;

#include "Robot.h"

class Robot;

class Room {
private:
    vector<vector<Container*>>  m_Containers;
    vector<Robot*>              m_ActiveRobots;
    pair<N, N>                  m_size;
    N                           m_currentTurn;

public:
    /** constructor y destructor */
    explicit Room(N cols = 1, N rows = 1);

    ~Room ();

    /** acceso a variables */
    vector<Robot*> &robots ()               ;

    vector<vector<Container*>> &grid ()     ;

    Container * &   atPosition (N x, N y)   ;

    /** añadir filas y columnas */
    void            addRow ()               ;

    void            addColumn ()            ;

    /** printear */
    void            printRoom ()            ;

    /** genera un nuevo robot */
    void            placeRobot (N col, N row, Texto name = "") ;

    /** hace que todos los robots realicen las instrucciones que tengan */
    void            controlRobots ()        ;

    friend class Robot;
    friend class Container;
};



#endif //UNTITLED5_ROOM_H
