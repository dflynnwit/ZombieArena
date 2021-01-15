//
// Created by pokor on 29/12/2020.
//

#ifndef ZOMBIEARENA_SPRITECOMPONENT_HPP
#define ZOMBIEARENA_SPRITECOMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "Component.h"

class SpriteComponent : public Component{

public:
    SpriteComponent();
    virtual void Draw(sf::RenderWindow &window, float timeDelta);
    virtual void Draw(sf::RenderWindow &window);
    bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);
    bool SetSprite(sf::Texture& texture);
    sf::Sprite& GetSprite();
    int GetFrameCount() const;
    bool IsAnimated();
    void SetAnimated(bool isAnimated);
    void setPosition(sf::Vector2f position);
    void setPosition(sf::Vector2f position, float rotation);
    void setOrigin(sf::Vector2f position);
    void setTexture(const sf::Texture &texture);
    void SetColor(sf::Color color);
    sf::Vector2u getTextureSize() const;
private:
    void NextFrame();
private:
    //ToDo add in attributes from main object's graphics.
    float m_timeDelta;
    int m_animationSpeed;
    bool m_isAnimated;
    int m_frameCount;
    int m_currentFrame;
    int m_frameWidth;
    int m_frameHeight;
    sf::Sprite m_sprite;
};

#endif
