//
// Created by pokor on 14/12/2020.
//

#ifndef ZOMBIEARENA_COMPONENT_H
#define ZOMBIEARENA_COMPONENT_H


class Component {
public:
    /**
    * Default Constructor.
    */
    Component();
    /**
    * Create a virtual function so the class is polymorphic.
    */
    virtual void Update(float timeDelta) {};
};


#endif
