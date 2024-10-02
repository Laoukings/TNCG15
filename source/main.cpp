#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "color.h"
#include <glm.hpp>
#include <vector>
#include "Object.h"

//simpel kamera structur

struct Camera
{   
    //2d array som lagrar alla pixlar. Just nu 500x500
    //ska ändras till vec3
    std::vector<std::vector<glm::vec3>> Picture;
    int camerasize;

};

int main()
{
    //Kameran som kommer rendreras
    Camera camera;

    //storlek på antal kolumner och rader i bilden
    camera.camerasize = 500;

    //for-loop som skapar en blank bild
    for (int Pixelx = 0; Pixelx < camera.camerasize; Pixelx++)
    {   
        //Skapar en rad
        camera.Picture.push_back(std::vector<glm::vec3>());

        for (int Pixely = 0; Pixely < camera.camerasize; Pixely++)
        {   
            //skapar all kolumner
            camera.Picture[Pixelx].push_back(glm::vec3(0, 0, 0));
            //Temporärt test för att se att den fungerade som det ska
        }
    }

    return 0;
}