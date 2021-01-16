
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

  
    template<typename T>
    std::shared_ptr<T> AttachComponent() {
        // First we'll create the component.
        std::shared_ptr<T> newComponent = std::make_shared<T>();
        // Check that we don't already have a component of this type.
        for (std::shared_ptr<Component>& exisitingComponent : m_components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                // If we do replace it.
                exisitingComponent = newComponent;
                return newComponent;
            } }
        
        // The component is the first of its type so add it.
        m_components.push_back(newComponent);
        // Return the new component.
        return newComponent;
    }
    
    template<typename T>
    std::shared_ptr<T> GetComponent() {
        // Check that we don't already have a component of this type.
        for (std::shared_ptr<Component> exisitingComponent : m_components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        
        return nullptr;
    }
    

    
private:
    /**

    * A collection of all components the object has attached.
    */
    std::vector<std::shared_ptr<Component>> m_components;
};

#endif
