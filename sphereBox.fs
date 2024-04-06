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


in vec3 fragmentPosition;		// The fragment position interpolated from the vertex shader
in vec3 reflectionVector;
in vec3 refractVector;

in float time; 

uniform samplerCube texCube;
uniform int refractFlag;
 
void main() 
{ 



	if (refractFlag == 1) 	{
		gl_FragColor = texture(texCube, refractVector);
	}
	else gl_FragColor = texture(texCube, reflectionVector); 	
	if (refractFlag == 1) 	gl_FragColor = texture(texCube, refractVector);
	else gl_FragColor = texture(texCube, reflectionVector); 	
	
 } 
