//
// Created by pokor on 30/12/2020.
//

#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent() {

}

void SpriteComponent::Draw(sf::RenderWindow &window, float timeDelta) {
    // check if the sprite is animated
    if (m_isAnimated)
    {
        // add the elapsed time since the last draw call to the aggregate
        m_timeDelta += timeDelta;

        // check if the frame should be updated
        if (m_timeDelta >= (1.f / m_animationSpeed))
        {
            NextFrame();
            m_timeDelta = 0;
        }
    }

    window.draw(m_sprite);
}

bool SpriteComponent::SetSprite(sf::Texture &texture, bool isSmooth, int frames, int frameSpeed) {
    // Create a sprite from the loaded texture.
    m_sprite.setTexture(texture);

    // Set animation speed.
    m_animationSpeed = frameSpeed;

    // Store the number of frames.
    m_frameCount = frames;

    // Calculate frame dimensions.
    sf::Vector2u texSize = m_sprite.getTexture()->getSize();
    m_frameWidth = texSize.x / m_frameCount;
    m_frameHeight = texSize.y;

    // Check if animated or static.
    if (frames > 1)
    {
        // Set sprite as animated.
        m_isAnimated = true;

        // Set the texture rect of the first frame.
        m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    }
    else
    {
        // Set sprite as non animated.
        m_isAnimated = false;
    }

    // Set the origin of the sprite.
    m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

    return true;
}

sf::Sprite &SpriteComponent::GetSprite() {
    return m_sprite;
}

int SpriteComponent::GetFrameCount() const {
    return m_frameCount;
}

bool SpriteComponent::IsAnimated() {
    return m_isAnimated;
}

void SpriteComponent::SetAnimated(bool isAnimated) {
    m_isAnimated = isAnimated;
    if (isAnimated)
    {
        m_currentFrame = 0;
    }
    else
    {
        // set the texture rect of the first frame
        m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    }
}

void SpriteComponent::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position.x,position.y);
}

void SpriteComponent::setOrigin(sf::Vector2f position) {
    m_sprite.setOrigin(position);
}

void SpriteComponent::setTexture(const sf::Texture &texture) {
    this->m_sprite.setTexture(texture);
}

sf::Vector2u SpriteComponent::getTextureSize() const {
    return this->m_sprite.getTexture()->getSize();
}

void SpriteComponent::NextFrame() {
    // check if we reached the last frame
    if (m_currentFrame == (m_frameCount - 1))
        m_currentFrame = 0;
    else
        m_currentFrame++;

    // update the texture rect
    m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}

void SpriteComponent::Draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

bool SpriteComponent::SetSprite(sf::Texture &texture) {
    // Create a sprite from the loaded texture.
    m_sprite.setTexture(texture);

    // Set the origin of the sprite.
    m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);

    return true;
}

void SpriteComponent::setPosition(sf::Vector2f position, float rotation) {
    m_sprite.setPosition(position.x,position.y);
    m_sprite.setRotation(rotation);
}

void SpriteComponent::SetColor(sf::Color color) {
    m_sprite.setColor(color);
}
