
#ifndef Object_h
#define Object_h

#include "Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.hpp"
#include <iostream>
#include <memory>

class Object
{
public:
    /**
     * Default constructor.
     */
    Object();

    /**
    * Attaches a component to the object.
    */
    template <typename T>
    std::shared_ptr<T> AttachComponent();

    /**
   * Gets a component from the object.
   */
    template <typename T>
    std::shared_ptr<T> GetComponent();
    
private:
    /**

    * A collection of all components the object has attached.
    */
    std::vector<std::shared_ptr<Component>> m_components;
};

#endif
