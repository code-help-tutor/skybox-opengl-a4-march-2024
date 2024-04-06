WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#version 330

in vec3 fragment_position;		// The fragment position interpolated from the vertex shader
in vec4 fragment_normal;		// The fragment normal interpolated from the vertex shader
in vec2 texCoord1;

uniform int time; 

 uniform sampler2D tex;
 vec2 tc; 

void main() 
{ 

    
	tc = texCoord1;	
	// scroll the texture
	tc.x -= time/1500.0;
	tc.y += time/1500.0;
	gl_FragColor = texture(tex, tc); 
	//gl_FragColor = vec4(1.0,1.0,0,0);
 } 
