WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

//=============================================================================
// sphere.h
//
//Author: Doron Nussbaum (C) 2015 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. creates a sphere object. 
//
//
// Description:
//--------------
//  Creates sphere geometry.  Currently it is used only to create a geometry of a sphere. It can be converted to a stand alone function. 
//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

//=============================================================================



#ifndef SPHERE_HEADER
#define SPHERE_HEADER


#include "graphicsObject.h"
#include "camera.h"

class Sphere : public GraphicsObject
{
public:
	Sphere();
	~Sphere();
	static int Sphere::createSphere(int numLong, int numLat, Vertices &vtx, Indices &ind);
	static int Sphere::createSphere(int numLong, int numLat, float u0, float u1, float v0, float v1, Vertices &vtx, Indices &ind);

	int createGeom(int numLongs, int numLat);
	int render(Shader shader);
	int render(Shader shader, Camera cam, int time, GLuint texUnit);
};


#endif
