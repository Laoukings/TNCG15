#include <iostream>

//simpel kamera structur
struct Camera
{   
    //2d array som lagrar alla pixlar. Just nu 500x500
    //ska ändras till vec3
    int Picture[500][500];
};

int main()
{

    //Kameran som kommer rendreras
    Camera camera;

    //storlek på antal kolumner och rader i bilden
    int cols = sizeof(camera.Picture[0]) / sizeof(camera.Picture[0][0]);
    int rows = sizeof(camera.Picture) / sizeof(camera.Picture[0]);

    //for-loop som går genom alla pixlar
    //ska sedan användas för att skjuta rays
    for (int Pixelx = 0; Pixelx < cols; Pixelx++)
    {
        for (int Pixely = 0; Pixely < rows; Pixely++)
        {   
            //Temporärt test för att se att den fungerade som det ska
            std::cout << "Hello World \n" << Pixelx;
        }
    }

    return 0;
}