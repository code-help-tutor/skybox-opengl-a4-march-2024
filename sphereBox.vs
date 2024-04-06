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




const float inRefractFactor = 1.0;			// refracting ray factor of the in material
const float outRefractFactor = 1.0;		// refracting ray factor of the out material
	
in vec4 vtxPos;					// the vertex position (in the local space) from VBO
in vec3 vtxNormal;				// the vertex normal (in the local space) from VBO

out vec3 fragmentPosition;		// The fragment position output into the fragment shader
out vec3 fragmentNormal;		// The fragment normal output into the fragment shader
out vec3 reflectionVector;
out vec3 refractVector;

uniform mat4 modelViewProjMat;
uniform mat4 modelViewMat;
uniform mat4 modelMat;
uniform vec3 camPos;


//*****************************************************************************

void main()
{ 
	
	vec4 vtx;
	vec3 viewVec;
	float eta;


	// set the ratio between the ouside material and the inside material for refracting a vector
	eta = inRefractFactor/outRefractFactor;

	vtx = modelMat * vtxPos;
	//vtx = modelViewMat * vtxPos;
	fragmentPosition = vtx.xyz;

	// compute the normal
	vtx = transpose(inverse(modelMat)) * vec4(vtxNormal,1.0);
	fragmentNormal   = vtx.xyz;
	//fragmentNormal   = vtxNormal;
	fragmentNormal = normalize(fragmentNormal);


	// position of fragment with projection matrix
	gl_Position = modelViewProjMat * vtxPos; 

	// get the view vector (from the eye to the fragment
	viewVec = fragmentPosition - camPos;
	viewVec = vtxPos.xyz - camPos;
	viewVec = normalize(viewVec);

	// compute the reflection and the refractding vectors

	// this computation is important for using the skybox for texturing a shiny object
	reflectionVector = reflect(viewVec, fragmentNormal);		

	refractVector = refract(viewVec,fragmentNormal,eta);



}
