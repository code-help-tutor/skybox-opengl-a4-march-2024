WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#version 330

//

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

uniform samplerCube texCube;

in vec3 rVector;

out vec4 colour;


void main() 
{ 
	gl_FragColor = texture(texCube, rVector);
 } 
