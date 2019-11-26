//
// Created by Pokora on 26/11/2019.
//

#ifndef ZOMBIEARENA_TEXTUREHOLDER_H
#define ZOMBIEARENA_TEXTUREHOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

class TextureHolder {
public:
    TextureHolder();
    static Texture& GetTexture(std::string const& filename);

private:
    //map of textures and corresponding filenames
    std::map<std::string, sf::Texture> m_Textures;

    //Pointer to the singleton
    static TextureHolder* m_s_Instance;
};


#endif //ZOMBIEARENA_TEXTUREHOLDER_H
