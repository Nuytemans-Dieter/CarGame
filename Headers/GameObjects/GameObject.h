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
    void setXPos( int x );
    //Set the y-position of this GameObject
    void setYPos( int y );

    //Set the dimensions of this GameObject
    void setWidth( int ); void setHeight( int );
    //get GameObject dimensions
    int getWidth(); int getHeight();

    //Update the current location, using the velocities
    void updateLocation();

    //Set the velocity in the Y direction
    void setYVelocity( int yVel );
    //Set the velocity in the X direction
    void setXVelocity( int xVel );

    //Set the boundaries of this GameObject, it will not be able to move outside of those!
    void setBoundaries( int minX, int minY, int maxX, int maxY );

    bool isColliding( GameObject* );

private:
    //Location of the GameObject
    int xPos;
    int yPos;

    //Dimensions of the GameObject
    int width;
    int height;

    //Current velocity of the GameObject
    int yVelocity;
    int xVelocity;

    //Max boundaries of the GameObject
    int xMax, yMax;
    //Min boundaries of the GameObject
    int xMin, yMin;
};


#endif //UNTITLED_GAMEOBJECT_H
