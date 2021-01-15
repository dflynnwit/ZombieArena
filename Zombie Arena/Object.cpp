//
//  Object.cpp
//  AssetManagerv1
//
//  Created by Denis Flynn on 03/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#include "Object.h"


// Default constructor.
Object::Object() :
m_position{ 0.f, 0.f },
m_animationSpeed(0),
m_isAnimated(false),
m_frameCount(0),
m_currentFrame(0),
m_frameWidth(0),
m_frameHeight(0),
m_timeDelta(0),
m_influenceValue(1)
{
    // Add a transform component.
    AttachComponent<TransformComponent>();
    AttachComponent<SpriteComponent>();
}

// Gives the object the given sprite.
bool Object::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed)
{
    std::shared_ptr<SpriteComponent> spriteCmpt = GetComponent<SpriteComponent>();
    return spriteCmpt->SetSprite(texture, isSmooth, frames, frameSpeed);
}

// Returns the object's sprite.
sf::Sprite& Object::GetSprite()
{
    //TODO: Change to get sprite component sprite
    std::shared_ptr<SpriteComponent> sprite = GetComponent<SpriteComponent>();
    return sprite->GetSprite();
//    return m_sprite;
}

// Sets the position of the object.
void Object::SetPosition(sf::Vector2f position)
{
    std::shared_ptr<TransformComponent> transformCmpt = GetComponent<TransformComponent>();
//    std::cout << "(Object.cpp)(SetPosition)Transform:" << transformCmpt << std::endl;
    transformCmpt->SetPosition(position);

    //TODO: Use sprite component after it's in
//    m_sprite.setPosition(transformCmpt->GetPosition().x, transformCmpt->GetPosition().y);
    std::shared_ptr<SpriteComponent> sprtCmpt = GetComponent<SpriteComponent>();
    sprtCmpt->setPosition(position);
}

// Returns the position of the object.
sf::Vector2f Object::GetPosition()
{
    std::shared_ptr<TransformComponent> transformCmpt = GetComponent<TransformComponent>();
    return transformCmpt->GetPosition();
}

// Gets the current animation state of the object.
bool Object::IsAnimated()
{
    std::shared_ptr<SpriteComponent> sprite = GetComponent<SpriteComponent>();
    return sprite->IsAnimated();
}

// Sets the animation state of the object.
void Object::SetAnimated(bool isAnimated)
{
    std::shared_ptr<SpriteComponent> sprite = GetComponent<SpriteComponent>();
    sprite->SetAnimated(isAnimated);
}

// Draws the object to the given render window.
void Object::Draw(sf::RenderWindow &window, float timeDelta)
{
    std::shared_ptr<SpriteComponent> sprite = GetComponent<SpriteComponent>();
    sprite->Draw(window, timeDelta);
}