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
    int samples;

};

int main()
{
    //Kameran som kommer rendreras
    Camera camera;
    Scene scene;

    //massor testobject
    Sphere red(1.0, glm::vec3(10.0, 2.0, 0.0), glm::vec3(1, 0, 1), 0);
    Sphere secondSphere(1.0, glm::vec3(7.0, -2.0, 0.0), glm::vec3(0, 0.5, 1),0);

    //roof coordinates
             //glm::vec3(13,0,5)r1
    //glm::vec3(10,6,5)r6,glm::vec3(10,-6,5)r2
    //glm::vec3(0,6,5)r5,glm::vec3(0,-6,5)r3
             //glm::vec3(-3,0,5)r4

    //floor coordinates
             //glm::vec3(13,0,-5)f1
    //glm::vec3(10,6,-5)f6,glm::vec3(10,-6,-5)f2
    //glm::vec3(0,6,-5)f5,glm::vec3(0,-6,-5)f3
             //glm::vec3(-3,0,-5)f4


    //rummet
    glm::vec3 r1(13.0, 0.0, 5.0);
    glm::vec3 r2(10.0, -6.0, 5.0);
    glm::vec3 r3(0.0, -6.0, 5.0);
    glm::vec3 r4(-3.0, 0.0, 5.0);
    glm::vec3 r5(0.0, 6.0, 5.0);
    glm::vec3 r6(10.0, 6.0, 5.0);
    glm::vec3 f1(13.0, 0.0, -5.0);
    glm::vec3 f2(10.0, -6.0, -5.0);
    glm::vec3 f3(0.0, -6.0, -5.0);
    glm::vec3 f4(-3.0, 0.0, -5.0);
    glm::vec3 f5(0.0, 6.0, -5.0);
    glm::vec3 f6(10.0, 6.0, -5.0);

    glm::vec3 l1(4.0, 5.9, 2.0);
    glm::vec3 l2(4.0, 5.9, -2.0);
    glm::vec3 l3(6.0, 5.9, 2.0);
    glm::vec3 l4(6.0, 5.9, -2.0);

    Rectangle roof(r5,r6,r3,r2,glm::vec3(0,0,1.0),0);
    Triangle rooftri1(r2,r6,r1, glm::vec3(1.0, 0, 0),0);
    Triangle rooftri2(r5,r3,r4, glm::vec3(1.0, 0, 0),0);

    Rectangle floor(f2, f6, f3, f5, glm::vec3(0, 0, 1.0),0);
    Triangle floortri1(f6,f2,f1, glm::vec3(1.0, 0, 0),0);
    Triangle floortri2(f5,f4,f3, glm::vec3(1.0, 0, 0),0);
    
    Rectangle rwall(r2,f2,r3,f3, glm::vec3(0, 1.0, 0),0);
    Rectangle lwall(r5,f5,r6,f6, glm::vec3(0, 1.0, 0),0);
    Rectangle rfarwall(f1, f2, r1, r2, glm::vec3(1.0, 1.0, 0), 0);
    Rectangle lfarwall(f6, f1, r6, r1, glm::vec3(1.0, 0.5, 0), 1);
    Rectangle rclosewall(f3, f4, r3, r4, glm::vec3(1.0, 0.5, 0.0),0);
    Rectangle lclosewall(f4, f5, r4, r5, glm::vec3(1.0, 0.5, 0.0),0);

    //coll test
    //Rectangle test(f6, f2, r6, r2, glm::vec3(1.0, 1.0, 1.0), 3);
    //scene.addRectangle(test);

    scene.addRectangle(floor);
    scene.addTriangle(rooftri1);
    scene.addTriangle(rooftri2);

    scene.addRectangle(roof);
    scene.addTriangle(floortri1);
    scene.addTriangle(floortri2);

    scene.addRectangle(lwall);
    scene.addRectangle(rwall);
    scene.addRectangle(lfarwall);
    scene.addRectangle(rfarwall);
    scene.addRectangle(lclosewall);
    scene.addRectangle(rclosewall);

    scene.addSphere(secondSphere);
    scene.addSphere(red);
  

    //testa runt lite
    Light light(glm::vec3(6, -1, 4.8), glm::vec3(4, -1, 4.8), glm::vec3(6, 1, 4.8), glm::vec3(4, 1, 4.8), glm::vec3(1.0, 1.0, 1.0));
    //Light light2(l1, l2, l3, l4, glm::vec3(1.0, 1.0, 1.0));
    scene.addLight(light);
    //scene.addLight(light2);

    //normalerna är motsatta
    //Triangle tricolltest(v1, v2, v3, glm::vec3(0, 1.0, 0));
    //Triangle tricolltest2(v4, v3, v2, glm::vec3(0, 0, 1.0));

    //scene.addTriangle(tricolltest);
    //scene.addTriangle(tricolltest2);

    //storlek på antal kolumner och rader i bilden
    camera.camerasize = 256;
    camera.samples = 10;

    double pixellowerbound = 0.0;
    double pixelupperbound = 2.0/camera.camerasize;
    std::uniform_real_distribution<double> pixelrand(pixellowerbound, pixelupperbound);
    std::default_random_engine re;

    double largestcol = 1.0;

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
            glm::vec3 color(0.0, 0.0, 0.0);


            //skickar massor samples
            for (int i = 0; i < camera.samples; i++)
            {   
                //roterad av någon anledning
                double randomx = pixelrand(re) - 4.0 / camera.camerasize;
                double randomy = pixelrand(re) - 4.0 / camera.camerasize;

                double x = (2.0 / (double)camera.camerasize) * (Pixely - (double)(camera.camerasize / 2.0)) + randomx;
                double y = (2.0 / (double)camera.camerasize) * (Pixelx - (double)(camera.camerasize / 2.0)) + randomy;


                //-x och -y
                glm::vec3 pixelPos = glm::vec3(0.0, -x, -y) - camera.eye;
                ray sceneray(camera.eye, pixelPos);

                //ray recursray(camera.eye, pixelPos, scene, glm::vec3(1.0,1.0,1.0));
                //color += glm::vec3(255.99, 255.99, 255.99) * recursray.recursivecolor();

                color += glm::vec3(255.99, 255.99, 255.99) * sceneray.Render(glm::vec3(1.0, 1.0, 1.0), scene);
                //color += glm::vec3(255.99, 255.99, 255.99) * sceneray.Raycolorcalc(sceneray , 1, scene);
                //color += glm::vec3(255.99, 255.99, 255.99) * sceneray.Shootray(sceneray , 1, scene);
                //color += glm::vec3(255.99, 255.99, 255.99) * sceneray.Raylist(scene, glm::vec3(1.0,1.0,1.0), nullptr);
            }



            if (color.x > largestcol) {
                largestcol = color.x;
            }
            if (color.y > largestcol) {
                largestcol = color.y;
            }
            if (color.z > largestcol) {
                largestcol = color.z;
            }

            //camera.Picture[Pixelx][Pixely] = glm::vec3(sceneray.Raycolorcalc(4, scene).x * 255.999, sceneray.Raycolorcalc(4, scene).y * 255.999, sceneray.Raycolorcalc(4, scene).z * 255.999);

            //färgen dividerad med största färgen
            //camera.Picture[Pixelx][Pixely] = color * glm::vec3(1/(largestcol/255.999), 1 / (largestcol / 255.999), 1 / (largestcol / 255.999)) ;
            camera.Picture[Pixelx][Pixely] = color;
            //camera.Picture[Pixelx][Pixely] = color * glm::vec3(1.0 / camera.samples, 1.0 / camera.samples, 1.0 / camera.samples);


            //Testar att skriva ut till ppm fil
            //std::cout << int(camera.Picture[Pixelx][Pixely].x) << ' ' << int(camera.Picture[Pixelx][Pixely].y) << ' ' << int(camera.Picture[Pixelx][Pixely].z) << '\n';
        }


    }

    for (int Pixelx = 0; Pixelx < camera.camerasize; Pixelx++)
    {

        for (int Pixely = 0; Pixely < camera.camerasize; Pixely++)
        {
            camera.Picture[Pixelx][Pixely] *= glm::vec3(1 / (largestcol / 255.999), 1 / (largestcol / 255.999), 1 / (largestcol / 255.999));
            //camera.Picture[Pixelx][Pixely] *=  glm::vec3(1.0 / camera.samples, 1.0 / camera.samples, 1.0 / camera.samples);
            //Testar att skriva ut till ppm fil
            std::cout << int(camera.Picture[Pixelx][Pixely].x) << ' ' << int(camera.Picture[Pixelx][Pixely].y) << ' ' << int(camera.Picture[Pixelx][Pixely].z) << '\n';
        }
    }

    return 0;
}