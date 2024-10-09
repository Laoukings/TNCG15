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
    Scene scene;

    //massor testobject
    Sphere red(1.0, glm::vec3(10.0, 0, -4.0), glm::vec3(1, 0, 0));
    Sphere secondSphere(1.0, glm::vec3(10.0, 0, 2.0), glm::vec3(0, 0.5, 1));

    glm::vec3 v1(0, 6, -5);
    glm::vec3 v2(10, 6, -5);
    glm::vec3 v3(0, 6, 5);
    glm::vec3 v4(10, 6, 5);

    //normalerna är motsatta
    Rectangle colltest(v1, v2, v3, v4, glm::vec3(0, 1.0, 0));
    Triangle tricolltest(v1, v2, v3, glm::vec3(0, 1.0, 0));
    Triangle tricolltest2(v4, v3, v2, glm::vec3(0, 0, 1.0));

    scene.addSphere(red);
    scene.addSphere(secondSphere);
    scene.addRectangle(colltest);
    scene.addTriangle(tricolltest);
    scene.addTriangle(tricolltest2);

    //storlek på antal kolumner och rader i bilden
    camera.camerasize = 600;

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

            glm::vec3 pixelPos = glm::vec3(0.0, (2.0 / camera.camerasize) * (Pixelx - (camera.camerasize / 2.0)), (2.0 / camera.camerasize) * (Pixely - (camera.camerasize / 2.0)));


            pixelPos -= camera.eye;
            
            //std::cout << pixelPos.x << pixelPos.y << pixelPos.z;

            ray sceneray(camera.eye,pixelPos,glm::vec3(0,0,0),nullptr,nullptr);
            camera.Picture[Pixelx][Pixely] = glm::vec3(sceneray.Raycolorcalc(4, scene).x * 255.999, sceneray.Raycolorcalc(4, scene).y * 255.999, sceneray.Raycolorcalc(4, scene).z * 255.999);

            //Färglägger pixlar där r,g,b komponenter går från 0-255.
            //auto r = double(Pixelx) / (camera.camerasize -1);
            //auto g = double(Pixely) / (camera.camerasize -1);
            //auto b = 0.0;

            //int ir = int(255.999 * r);
            //int ig = int(255.999 * g);
            //int ib = int(255.999 * b);

            //Testar att skriva ut till ppm fil
            std::cout << int(camera.Picture[Pixelx][Pixely].x) << ' ' << int(camera.Picture[Pixelx][Pixely].y) << ' ' << int(camera.Picture[Pixelx][Pixely].z) << '\n';
        }
    }

    return 0;
}