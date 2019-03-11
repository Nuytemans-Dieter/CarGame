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
    SDLTexture(SDL_Window*, SDL_Renderer*);
    ~SDLTexture();

    /**
     * Load an image from a given path
     * @param path relative to the resources folder (not "..//resources//etc/" but "etc/");
     * @return Returns whether loading was successful
     */
    bool loadImage(std::string path);

    //Deallocates image
    void free();

    void render(int x, int y);

    int getWidth();
    int getHeight();

    void close();

private:
    SDL_Texture* texture;
    int height;
    int width;

    SDL_Window* window;
    SDL_Renderer* renderer;
};


#endif //UNTITLED_SDLTEXTURE_H
