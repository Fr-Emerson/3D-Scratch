#include "olcConsoleGameEngine.h"
#include <iostream>
using namespace std;
struct Vector3
{
    float x = 0;
    float y = 0;
    float z = 0;
};
struct Triangle
{
    Vector3 p[3];
};

struct mesh
{
    vector<Triangle> triangles;
};
class Engine3D : public olcConsoleGameEngine
{
private:
    mesh _cube;
public:

    Engine3D()
    {
        m_sAppName = L"3D Scratch";

    }
    bool OnUserCreate() override
    {
        _cube.triangles = {
            //SOUTH

            {0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f},

            //EAST
            {1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f},

            //NORTH
            {1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f},
			{1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f},
            //WEST
            {0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f},
            //TOP
			{0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f},
			//BOTTOM
            {1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f}
        };
        return true;

    }
    bool OnUserUpdate(float fElapsedTime) override
    {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID,FG_BLACK);
        for (auto triangles: _cube.triangles) 
        {
        }
        return true;    
	}
};

int main()
{
	Engine3D demo;
    if (demo.ConstructConsole(256,240,4,4)) 
    {
		demo.Start();
    }
}

