//
//  Object.cpp
//  AssetManagerv1
//
//  Created by Denis Flynn on 03/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#include "Object.h"


// Default constructor.
Object::Object()
{
    //TODO: Move to elements that actually use it
//    // Add a transform component.
//    AttachComponent<TransformComponent>();
//    AttachComponent<SpriteComponent>();
}

template<typename T>
std::shared_ptr<T> Object::AttachComponent() {
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
std::shared_ptr<T> Object::GetComponent() {
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

