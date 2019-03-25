//
// Created by Dieter on 11/03/2019.
//

#ifndef UNTITLED_SDLTEXTURE_H
#define UNTITLED_SDLTEXTURE_H


#include <string>
#include <SDL2/SDL_image.h>

class SDLTexture {
public:
    /**
     * Creates a SDLTexture that can manage the loading of images
     */
    SDLTexture();
    ~SDLTexture();

    /**
     * Load an image from a given path
     * @param path relative to the resources folder (not "..//resources//etc/" but "etc/");
     * @param SDL_Renderer the SDL renderer being used
     * @return Returns whether loading was successful
     */
    bool loadImage(std::string path, SDL_Renderer*);

    //Deallocates image
    void free();

    int getWidth();
    int getHeight();

    SDL_Texture* getTexture();
    void setTexture(SDL_Texture*, int h, int w);

private:
    SDL_Texture* texture;
    int height;
    int width;
};


#endif //UNTITLED_SDLTEXTURE_H
