//
// Created by Dieter on 18/03/2019.
//

#ifndef UNTITLED_GAMEOBJECT_H
#define UNTITLED_GAMEOBJECT_H


class GameObject {
public:
    GameObject();
    ~GameObject();

    //Get the x-position of this GameObject
    int getXPos();
    //Get the y-position of this GameObject
    int getYPos();

    //Set the x-position of this GameObject
    void setXPos(int x);
    //Set the y-position of this GameObject
    void setYPos(int y);

private:
    int xPos;
    int yPos;
};


#endif //UNTITLED_GAMEOBJECT_H
