#version 330

//
//Author: Doron Nussbaum (C) 2023 All Rights Reserved.
//-----------------------------------------------------
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


in vec4 vtxPos;				// the vertex position (in the local space) from VBO

out  vec3 rVector;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;


void main()
{ 

   rVector = normalize(vtxPos.xyz);
   //rVector = normalize((viewMat* modelMat  * vtxPos).xyz);
   //rVector = normalize((modelMat  * vtxPos).xyz);
   gl_Position = projMat* viewMat* modelMat  * vtxPos;

}


