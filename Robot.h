//
// Created by Intel on 27/11/2019.
//

#ifndef UNTITLED5_ROBOT_H
#define UNTITLED5_ROBOT_H

#include "tipes.h"
#include "Container.h"
class Container;
#include "Room.h"
class Room;

class Robot {
private:
    Container *     m_place;
    Container *     m_destination;
    Container *     m_spawn;
    Texto          m_name;
    vector<Texto>  m_heldItems;
    vector<N>       m_instructions;
    char            m_identifier;
public:
    pair<N, N> myRoomSize;

    /** constructor y destructor */
    Robot ();

    ~Robot() ;

    /** acceso a variables */
    char            identifier ()    const  ;

    Texto          name ()          const  ;

    Container*      place ()         const  ;

    pair<N, N>      position ()      const  ;

    vector<Texto>  items ()         const  ;

    vector<N> &     instructions ()         ;

    bool            inDestination () const  ;

    /** hace aparecer un robot en un container */
    void            spawnAt (Container * &container)             ;

    /** le asigna un container de destino al robot */
    void            assignDestination (Container * &dContainer)  ;

    /** le da nombre xd */
    void            rename (Texto name)                         ;

    /** le da un item // nada de los items esta implementado //*/
    void            giveItem (Texto item)                       ;

    void            dropItem (const Texto& item)                ;

    /** mueve al robot a la siguiente posición en la dirección de su siguiente instrucción */
    void            movetoNextPlace ()                           ;
    void            genPath ();

    friend class Container;
    friend class Room;
};

#endif //UNTITLED5_ROBOT_H
