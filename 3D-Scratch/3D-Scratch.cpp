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

struct matrix4x4 
{
	float m[4][4] = { 0 };
};
class Engine3D : public olcConsoleGameEngine
{
private:
    mesh _cube;
	matrix4x4 _projectionMatrix;

    void MultiplyMatrixVector(Vector3 &i, Vector3 &o, matrix4x4 &m)
    {
        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
        o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
        o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
        float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
        if (w != 0.0f)
        {
            o.x /= w; o.y /= w; o.z /= w;
        }
	}
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
		float fNear = 0.1f;
		float fFar = 1000.0f;
		float Fov = 90.0f;
		float AspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
		float FovRad = 1.0f / tanf(Fov * 0.5f / 180.0f * 3.14159f);
		_projectionMatrix.m[0][0] = AspectRatio * FovRad;
		_projectionMatrix.m[1][1] = FovRad;
		_projectionMatrix.m[2][2] = fFar / (fFar - fNear);
		_projectionMatrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		_projectionMatrix.m[2][3] = 1.0f;
		_projectionMatrix.m[3][3] = 0.0f;
        return true;

    }
    bool OnUserUpdate(float fElapsedTime) override
    {
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID,FG_BLACK);
        for (auto triangles: _cube.triangles) 
        {
			Triangle projectedTriangle, triangleTranslated;

			triangleTranslated = triangles;
			triangleTranslated.p[0].z += 3.0f;
			triangleTranslated.p[1].z += 3.0f;
			triangleTranslated.p[2].z += 3.0f;


            MultiplyMatrixVector(triangleTranslated.p[0], projectedTriangle.p[0], _projectionMatrix);
            MultiplyMatrixVector(triangleTranslated.p[1], projectedTriangle.p[1], _projectionMatrix);
            MultiplyMatrixVector(triangleTranslated.p[2], projectedTriangle.p[2], _projectionMatrix);
            
			projectedTriangle.p[0].x += 1.0f; projectedTriangle.p[0].y += 1.0f;
			projectedTriangle.p[1].x += 1.0f; projectedTriangle.p[1].y += 1.0f;
			projectedTriangle.p[2].x += 1.0f; projectedTriangle.p[2].y += 1.0f;

			projectedTriangle.p[0].x *= 0.5f *(float)ScreenWidth();
            projectedTriangle.p[0].y *= 0.5f *(float)ScreenHeight();
			projectedTriangle.p[1].x *= 0.5f *(float)ScreenWidth();
            projectedTriangle.p[1].y *= 0.5f *(float)ScreenHeight();
			projectedTriangle.p[2].x *= 0.5f *(float)ScreenWidth();
            projectedTriangle.p[2].y *= 0.5f * (float)ScreenHeight();

            DrawTriangle(
                (projectedTriangle.p[0].x ),
                (projectedTriangle.p[0].y ),
                (projectedTriangle.p[1].x ),
                (projectedTriangle.p[1].y ),
                (projectedTriangle.p[2].x ),
                (projectedTriangle.p[2].y ),
				PIXEL_SOLID, FG_WHITE);
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

