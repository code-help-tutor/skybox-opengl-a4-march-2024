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



attribute vec4 vtxPos;		// the vertex position (in the local space) from VBO
attribute vec4 vtxNormal;		// the vertex normal (in the local space) from VBO
attribute vec2 texCoord;			// coordiantes of the texture

out vec3 fragment_position;		// The fragment position output into the fragment shader
out vec4 fragment_normal;		// The fragment normal output into the fragment shader
out vec2 texCoord1;


uniform int time;	// time step of the wave				
uniform int drawWave;		// == 1 render a wave  == 0 no wave
uniform int renderCircularWave;	// == 1 render a ciruclar wave == 0 render linear wave
//out float texMotionTime;		// 

const float speed = 0.1;

uniform mat4 modelViewProjMat;

//*****************************************************************************
// function returns the height of the points of a linear wave along the xz plane
// the wave linear line is perpendicular to the waveVector

float linearWave(vec3 p, vec3 waveRefPoint, vec3 waveVector, float waveLength, 
					float amplitude,float frequency, float displacement, float time)
{

	float height ,d;
	vec2 dir;
	vec3  q;
	float dz, dx;

	
	// direction
	dir.x = waveVector.x;
	dir.y = waveVector.z;
	dir = normalize(dir);


	// create a vector from the points

	q = p - waveRefPoint;
	
	d = dot(dir	,vec2(q.xz));
	if (d <0.0) d*=-1.0;
	height = amplitude*sin(waveLength*d + frequency*time+displacement);

	return(height);
}

//******************************************************************


// function returns the height of the points of a circular wave centred at waveCentre long the xz plane
// input
// p - the point to be computed
// waveCentre - the origin of the wave
// waveLength
// amplitiude - amplitude of wave
// frequency - frequency of wave
// displacement - displacement of wave from the origin
// time - the current time
// output:
// computed ciruclar height at p

float circularWave(vec3 p, vec3 waveCentre,	float waveLength, float amplitude,float frequency,float displacement, float time)
{

	float height,d;
	float dz, dx;
	
	dz = p.z - waveCentre.z;
	dx = p.x - waveCentre.x;
	d = sqrt(dz*dz + dx*dx);
	
	 height = amplitude*sin(waveLength*d+frequency*time+displacement);
	 
	return(height);
}

//************************************************************************
void main()
{ 
	
	float waveLength = 5.61;
	float amplitude = 40;
	float frequency = 0.01;
	float displacement = -50;
	vec4 vtx = vtxPos;
	if (drawWave == 1) {
		if (renderCircularWave == 1) vtx.y += circularWave(vec3(vtx.xyz), vec3(0,0,0), waveLength, amplitude, frequency,displacement, time);
		else vtx.y = linearWave(vec3(vtx.xyz), vec3(100,0,100), vec3(40.0,0,77.5),	waveLength,amplitude, frequency, displacement,time);

	}

	fragment_position = vec3(vtx);
	fragment_normal   = vtxNormal;
	
	gl_Position = modelViewProjMat * vtx; 
	fragment_position = vec3(gl_Position);

	fragment_normal   = modelViewProjMat * vtxNormal;
	//gl_Position.y = height(gl_Position.x, gl_Position.z);
	texCoord1 = texCoord;
}