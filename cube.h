WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once
#include "geometry_common.h"
#include "GL/nuss_math.h"





class Cube 
{
public:
	Cube();
	~Cube();

	int render();
	void setInitialRotations(float rollAngle, float pitchAngle, float yawAngle);
	void setInitialPosition(float x, float y, float z);
	void incrementRotations(float rollAngle, float pitchAngle, float yawAngle);
	void incrementPosition(float deltaX, float deltaY, float deltaZ);
	void setScale(float sx, float sy, float sz);


private:
	Vertex vtx[36];
	float rollAngle;	// rotation around the z-axis
	float pitchAngle;	// rotation around the x-axis
	float yawAngle;		// rotation around the y-axis
	Vector3f position;
	Vector3f scale;
	int numIndices;

	void initGeom();

};





