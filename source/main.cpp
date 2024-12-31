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
    //2d array för alla piclar
    std::vector<std::vector<glm::vec3>> Picture;
    //hur hög upplösning bilden kommer ha
    int camerasize = 0;
    //positionen av ögat
    glm::vec3 eye = glm::vec3(-1, 0, 0);
    //antalet samples
    int samples;

};

int main()
{
    //Kameran som scenen bygger på
    Camera camera;
    //scenen som ska rendreras
    Scene scene;

    //Sfärerna
    Sphere red(1.0, glm::vec3(10.0, 2.0, 0.0), glm::vec3(1, 0, 1), 0);
    Sphere secondSphere(1.0, glm::vec3(7.0, -2.0, 0.0), glm::vec3(0, 0.5, 1), 1);

    //vertices for trianglarna till 3d trianglarna
    glm::vec3 t1(4.0, 1.0, -3.0);
    glm::vec3 t2(6.0, 2.0, -3.0);
    glm::vec3 t3(6.0, -0.0, -3.0);
    glm::vec3 t4(5.0, 1.0, 0.0);

    //    t3      t2   
    //        t4 
    //        t1

    //De fyra trianglarna som gör upp 3d triangeln
    Triangle tr1(t1, t3, t2, glm::vec3(0.3, 0.4, 0.8), 0);
    Triangle tr2(t2, t1, t4, glm::vec3(0.3, 0.4, 0.8), 0);
    Triangle tr3(t3, t2, t4, glm::vec3(0.3, 0.4, 0.8), 0);
    Triangle tr4(t1, t3, t4, glm::vec3(0.3, 0.4, 0.8), 0);

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


    //vertices för rummet
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

    //vertices för ljusen
    glm::vec3 l1(4.0, 5.9, 2.0);
    glm::vec3 l2(4.0, 5.9, -2.0);
    glm::vec3 l3(6.0, 5.9, 2.0);
    glm::vec3 l4(6.0, 5.9, -2.0);
    glm::vec3 l5(6.0, -1.0, 4.9);
    glm::vec3 l6(4.0, -1.0, 4.9);
    glm::vec3 l7(6.0, 1.0, 4.9);
    glm::vec3 l8(4.0, 1.0, 4.9);

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

    scene.addTriangle(tr1);
    scene.addTriangle(tr2);
    scene.addTriangle(tr3);
    scene.addTriangle(tr4);

    //ljus i scenen
    Light light(l1, l2, l3, l4, glm::vec3(1.0, 1.0, 1.0));
    Light light2(l5, l6, l7, l8, glm::vec3(1.0, 1.0, 1.0));
    scene.addLight(light);
    scene.addLight(light2);

    //definerar kamerans värden
    camera.camerasize = 800;
    camera.samples = 1;

    //random position i pixeln
    double pixellowerbound = 0.0;
    double pixelupperbound = 2.0/camera.camerasize;
    std::uniform_real_distribution<double> pixelrand(pixellowerbound, pixelupperbound);
    std::default_random_engine re;

    //variabel som kommer hålla koll på största pixel värdet i scenen
    double largestcol = 1.0;

    //text för ppm filen
    std::cout << "P3\n" << camera.camerasize << ' ' << camera.camerasize << "\n255\n";

    //for-loop som rendrerar bilden
    for (int Pixelx = 0; Pixelx < camera.camerasize; Pixelx++)
    {   
        //Skapar en rad
        camera.Picture.push_back(std::vector<glm::vec3>());

        for (int Pixely = 0; Pixely < camera.camerasize; Pixely++)
        {   
            //skapar all kolumner
            camera.Picture[Pixelx].push_back(glm::vec3(0, 0, 0));

            //variabel som ska in i bilden
            glm::vec3 color(0.0, 0.0, 0.0);


            //En loop för varje sample
            for (int i = 0; i < camera.samples; i++)
            {   
                //Random punkter i pixeln
                double randomx = pixelrand(re) - 4.0 / camera.camerasize;
                double randomy = pixelrand(re) - 4.0 / camera.camerasize;
                
                //vart strålen skjuts
                double x = (2.0 / (double)camera.camerasize) * (Pixely - (double)(camera.camerasize / 2.0)) + randomx;
                double y = (2.0 / (double)camera.camerasize) * (Pixelx - (double)(camera.camerasize / 2.0)) + randomy;


                //bilden blir upp och ner om vi inte har -x och -y
                glm::vec3 pixelPos = glm::vec3(0.0, -x, -y) - camera.eye;
                //skicka strålen från eye till pixeln
                ray sceneray(camera.eye, pixelPos);

                //skjut strålen genom scenen och få rätt färg
                color += glm::vec3(255.99, 255.99, 255.99) * sceneray.Render(glm::vec3(1.0, 1.0, 1.0), scene);
            }


            //kolla om vi fått en ny största färg
            if (color.x > largestcol) {
                largestcol = color.x;
            }
            if (color.y > largestcol) {
                largestcol = color.y;
            }
            if (color.z > largestcol) {
                largestcol = color.z;
            }

            //sätt den nuvarande pixelns färg
            camera.Picture[Pixelx][Pixely] = color;

        }


    }

    //gå igenom hela bilden igen
    for (int Pixelx = 0; Pixelx < camera.camerasize; Pixelx++)
    {

        for (int Pixely = 0; Pixely < camera.camerasize; Pixely++)
        {   
            //dela med största färgvärdet så det blir normaliserat mellan 0-1 och multiplicera sedan med 255.9 så vi får rgb
            camera.Picture[Pixelx][Pixely] *= glm::vec3(1 / (largestcol / 255.999), 1 / (largestcol / 255.999), 1 / (largestcol / 255.999));

            //skriv en rad på ppm filen
            std::cout << int(camera.Picture[Pixelx][Pixely].x) << ' ' << int(camera.Picture[Pixelx][Pixely].y) << ' ' << int(camera.Picture[Pixelx][Pixely].z) << '\n';
        }
    }

    return 0;
}