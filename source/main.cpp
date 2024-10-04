#include <iostream>

#include "ray.h"
#include <glm.hpp>
#include <vector>
#include "Object.h"
#include "Light.h"
#include "Scene.h"

//C:\Users\simon\TNCG15\TNCG15\include;C:\Users\simon\TNCG15\TNCG15\include\glm

//simpel kamera structur

struct Camera
{   
    //2d array som lagrar alla pixlar. Just nu 500x500
    std::vector<std::vector<glm::vec3>> Picture;
    int camerasize = 0;
    glm::vec3 eye = glm::vec3(-1, 0, 0);

};

int main()
{
    //Kameran som kommer rendreras
    Camera camera;

    //storlek på antal kolumner och rader i bilden
    camera.camerasize = 256;

    std::cout << "P3\n" << camera.camerasize << ' ' << camera.camerasize << "\n255\n";
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

            glm::vec3 pixelPos = glm::vec3((2/camera.camerasize) * Pixelx,(2/camera.camerasize) * Pixely,0);

            pixelPos -= camera.eye;
            

            ray sceneray(camera.eye,pixelPos,glm::vec3(0,0,0),nullptr,nullptr);


            //Färglägger pixlar där r,g,b komponenter går från 0-255.
            auto r = double(Pixelx) / (camera.camerasize -1);
            auto g = double(Pixely) / (camera.camerasize -1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            //Testar att skriva ut till ppm fil
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}