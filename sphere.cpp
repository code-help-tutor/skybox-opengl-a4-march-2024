WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com

//=============================================================================
// sphere.c
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


#include "sphere.h"
#include <iostream>
using namespace std;



Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}




/************************************************************************************************************/
/*
// Function creates a sphere geometry

input:
numLong - number of longitudes
numLat - number of latituudes.  Note that the number of latitudes is defined only for the northern hemishphere
u0, u1 - range of texture u coordinates
v0, v1 - range of texture v coordinates

*/

int Sphere::createSphere(int numLong, int numLat, float u0, float u1, float v0, float v1, Vertices &vtx, Indices &ind)

{
	int i, j, k;
	int numRows;
	int numCols;
	int numVtx;
	int numTriangles;
	Vector4f pos;
	Vector4f col;
	Vector3f normal;
	Vector2f texCoord;
	float alpha;
	float beta;
	float deltaAlpha;
	float deltaBeta;
	float deltaU, deltaV;
	float u, v;		// texture coordinates

	numRows = numLat * 2;  // number of horizonal slabs
	numCols = numLong;	// number of vertical slabs

	numVtx = (numRows + 1) * (numCols + 1);
	vtx.resize(0);
	//cout << "   the vector's size is: " << vtx.size() << endl;
	//cout << "   the vector's capacity is: " << vtx.capacity() << endl;
	//cout << "   the vector's maximum size is: " << vtx.max_size() << endl;


	numTriangles = numRows * numCols * 2;
	ind.resize(0);

	// Fill the vertex buffer with positions
	k = 0;
	alpha = 0.0f;  // angle of latitude starting from the "south pole"
	deltaAlpha = (float)90.0 / numLat; // increment of alpha
	beta = 0;   // angle of the longtidute 
	deltaBeta = (float)360.0 / (numLong);	// increment of beta

	// texture coordinates deltas
	deltaU = (u1 - u0) / numCols;
	deltaV = (v1 - v0) / numRows;


	
	for (i = 0, alpha = -90, v = v0; i <= numRows; i++, alpha += deltaAlpha, v += deltaV) {
		for (j = 0, beta = 0, u = u0; j <= numCols; j++, beta += deltaBeta, u += deltaU) {
			pos.x = cos(DegreeToRadians(alpha))*cos(DegreeToRadians(beta));
			pos.z = cos(DegreeToRadians(alpha))*sin(DegreeToRadians(beta));
			pos.y = sin(DegreeToRadians(alpha));
			pos.w = 1.0;

			texCoord.x = u;
			texCoord.y = v;

			col = pos;
			col.x = fabs(col.x); col.y = fabs(col.y); col.z = fabs(col.z);
			col.x = 1; col.y = 0.5; col.z = 0;
			normal = Vector3f(pos.x, pos.y, pos.z);
			vtx.push_back(Vertex(pos, normal, col, texCoord));

		}
	}




	// fill the index buffer

	k = 0;
	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			// fill indices for the quad
			// change by making a quad function
			ind.push_back(i * (numCols + 1) + j);
			ind.push_back(i * (numCols + 1) + j + 1);
			ind.push_back((i + 1) * (numCols + 1) + j + 1);

			ind.push_back(i * (numCols + 1) + j);
			ind.push_back((i + 1) * (numCols + 1) + j + 1);
			ind.push_back((i + 1) * (numCols + 1) + j);
		}
	}


	return(0);

}




/************************************************************************************************************/
/*
// Function creates a sphere geometry

input:
numLong - number of longitudes
numLat - number of latituudes.  Note that the number of latitudes is defined only for the northern hemishphere


*/

int Sphere::createSphere(int numLong, int numLat, Vertices &vtx, Indices &ind)

{
	int i, j, k;
	int numRows;
	int numCols;
	int numVtx;
	int numTriangles;
	Vector4f pos;
	Vector4f col;
	float alpha;
	float beta;
	float deltaAlpha;
	float deltaBeta;

	numRows = numLat * 2;  // number of horizonal slabs
	numCols = numLong;	// number of vertical slabs

	numVtx = (numRows + 1) * (numCols + 1);
	vtx.resize(0);
	cout << "   the vector's size is: " << vtx.size() << endl;
	cout << "   the vector's capacity is: " << vtx.capacity() << endl;
	cout << "   the vector's maximum size is: " << vtx.max_size() << endl;


	numTriangles = numRows * numCols * 2;
	ind.resize(0);

	// Fill the vertex buffer with positions
	k = 0;
	alpha = 0.0f;  // angle of latitude starting from the "south pole"
	deltaAlpha = (float)90.0 / numLat; // increment of alpha
	beta = 0;   // angle of the longtidute 
	deltaBeta = (float)360.0 / (numLong);	// increment of beta



	for (i = 0, alpha = -90; i <= numRows; i++, alpha += deltaAlpha) {
		for (j = 0, beta = 0; j <= numCols; j++, beta += deltaBeta) {
			pos.x = cos(DegreeToRadians(alpha))*cos(DegreeToRadians(beta));
			pos.z = cos(DegreeToRadians(alpha))*sin(DegreeToRadians(beta));
			pos.y = sin(DegreeToRadians(alpha));
			pos.w = 1.0;

			col = pos;
			col.x = fabs(col.x); col.y = fabs(col.y); col.z = fabs(col.z);
			col.x = 1; col.y = 0.5; col.z = 0;
			//vtx[k] = Vertex(pos, pos);
			vtx.push_back(Vertex(pos, Vector3f(pos.x, pos.y, pos.z), col));

		}
	}




	// fill the index buffer

	k = 0;
	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			// fill indices for the quad
			// change by making a quad function
			ind.push_back(i * (numCols + 1) + j);
			ind.push_back(i * (numCols + 1) + j + 1);
			ind.push_back((i + 1) * (numCols + 1) + j + 1);

			ind.push_back(i * (numCols + 1) + j);
			ind.push_back((i + 1) * (numCols + 1) + j + 1);
			ind.push_back((i + 1) * (numCols + 1) + j);
		}
	}


	return(0);

}





/*********************************************************************************/


int Sphere::render(Shader shader, Camera cam, int time, GLuint texUnit)
{
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix
	Matrix4f modelMat;	// final model matrix
	Matrix4f modelViewMat;	// view matrix
	Matrix4f modelViewProjMat;	// projection matrix

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// use the created shader
	shader.useProgram(1);


	shader.copyIntVectorToShader((int *)&texUnit, 1, 1, "texCube");

	shader.copyIntVectorToShader(&time, 1, 1, "time");


	// set the transformation matrix - the model transfomration
	modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	modelMat = scaleMat * modelMat;

	// set the rotation  - this is model space to model space transformation 
	rotMat = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;

	// set the orientation  - this is model space to model space transformation 
	// Add code here
	rotMat = Matrix4f::rotateRollPitchYaw(0, 0, 0, 1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;


	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(position);
	modelMat = transMat * modelMat;


	// move matrix to shader
	shader.copyMatrixToShader(modelMat, "modelMat");


	// set the camera matrix
	modelViewMat = cam.getViewMatrix(NULL) * modelMat;	// get the camera view transformation
#if 0	// move matrix to shader
	shader.copyMatrixToShader(modelViewMat, "modelViewMat");
#endif

	// set the projection matrix
	modelViewProjMat = cam.getProjectionMatrix(NULL) * modelViewMat;
	// move matrix to shader
	shader.copyMatrixToShader(modelViewProjMat, "modelViewProjMat");

	// transfer the camera position
	Vector3f pos = cam.getPosition();
	shader.copyFloatVectorToShader((float *)&pos, 1, 3, "camPos");


	// bind the vao
	glBindVertexArray(vao);

	// draw using indices
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);
	//glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);

	// unbind the vao
	glBindVertexArray(0);

	return 0;
}



/*********************************************************************************/


int Sphere::render(Shader shader)
{
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix
	Matrix4f modelMat;	// final model matrix

	// set the transformation matrix - the model transfomration
	modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	modelMat = scaleMat * modelMat;

	// set the rotation  - this is model space to model space transformation 
	rotMat = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;

	// set the orientation  - this is model space to model space transformation 
	// Add code here
	rotMat = Matrix4f::rotateRollPitchYaw(0, 0, 0, 1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;


	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(position);
	modelMat = transMat * modelMat;

	// move matrix to shader
	shader.copyMatrixToShader(modelMat, "modelMat");



	// bind the vao
	glBindVertexArray(vao);

	// draw using indices
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);
	//glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);

	// unbind the vao
	glBindVertexArray(0);

	return 0;
}





/*******************************************************************************/
// future funcdtion to create internal representation of a sphere

int Sphere::createGeom(int numLongs, int numLat)
{
//	int numLong, int numLat, float radius, struct sphereVertex **vtx, int *numVtx1, GLuint **ind, int *numInd1
	return 0;
}


