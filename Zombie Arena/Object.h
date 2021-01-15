
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
    
    void setInfluence(float influence){m_influenceValue=influence;};
    float getInfluence(){ return(m_influenceValue);};
    
    virtual void Update(float timeDelta) {};
    virtual void Draw(sf::RenderWindow &window, float timeDelta);
    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition();
    bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);
    sf::Sprite& GetSprite();
    int GetFrameCount() const;
    bool IsAnimated();
    void SetAnimated(bool isAnimated);

    /**
    * Attaches a component to the object.
    */
    template <typename T>
    std::shared_ptr<T> AttachComponent()
    {
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
    };

    /**
   * Gets a component from the object.
   */
    template <typename T>
    std::shared_ptr<T> GetComponent()
    {
        // Check that we don't already have a component of this type.
        for (std::shared_ptr<Component> exisitingComponent : m_components)
        {
//            std::cout << "(Object.h)(GetComponent loop)Component being checked: " << exisitingComponent << std::endl;
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
//                std::cout << "(Object.h)(GetComponent loop)Component found: " << exisitingComponent << std::endl;
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }

//        std::cout << "(Object.h)(GetComponent)Component not found(returns null)" << std::endl;
        return nullptr;
    };
    
protected:
    
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    
private:
    /**

    * A collection of all components the object has attached.
    */
    std::vector<std::shared_ptr<Component>> m_components;
   
    void NextFrame();
    
private:
    
    float m_influenceValue;
    int m_animationSpeed;
    bool m_isAnimated;
    int m_frameCount;
    int m_currentFrame;
    int m_frameWidth;
    int m_frameHeight;
public:
    float m_timeDelta;
};

#endif
