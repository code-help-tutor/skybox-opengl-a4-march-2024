WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "Texture.h"
#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"




/**************************************************************************************/


Texture::Texture() :texId(-1)
{
}


/**************************************************************************************/




Texture::~Texture()
{
}



/**************************************************************************************/
//  load a texture


int  Texture::loadTextureImage( char *imageFileName, GLuint texTarget)
{

	int width, height;
	int numChannels;
	unsigned char* image = NULL;
	GLenum format;

	// generate the texture
	glGenTextures(1, &texId);
	glBindTexture(texTarget, texId);
	this->texTarget = texTarget;

	// load the image 

	image = stbi_load(imageFileName, &width, &height, &numChannels, 0);
	if (image != NULL)
	{
		if (numChannels == 1)
			format = GL_RED;
		else if (numChannels == 3)
			format = GL_RGB;
		else if (numChannels == 4)
			format = GL_RGBA;

	}
	else
	{
		printf("Error: texture %s did not load \n", imageFileName);
		if (image != NULL) stbi_image_free(image);
	}



	// connect the image to the texture
	glTexImage2D(texTarget, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

	// image stored with the shader -> can delete the image
	stbi_image_free(image);
	image = NULL;

	// set the repeat behaviour
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// set the sampling behaviour
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	return(0);
}


/**************************************************************************************/

/*loads the skybox images

order of images is
GL_TEXTURE_CUBE_MAP_POSITIVE_X
GL_TEXTURE_CUBE_MAP_NEGATIVE_X
GL_TEXTURE_CUBE_MAP_POSITIVE_Y
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
GL_TEXTURE_CUBE_MAP_POSITIVE_Z
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z

*/


int Texture::loadTextureImages(char ** texFileName)
{

	int i;
	int rc = 0;
	int width = 1, height = 1;
	unsigned char* image;
	int numChannels;
	GLenum format;


	if (texFileName == NULL) return(-1);
	else for (i = 0; i < 6; i++) {
		if (texFileName[i] == NULL) return(-1);
	}



	//glEnable(GL_TEXTURE_CUBE_MAP);
	//glActiveTexture(GL_TEXTURE3);

	// Create texture object
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
	this->texTarget = GL_TEXTURE_CUBE_MAP;


	for (i = 0; i < 6; i++) {
		
		image = stbi_load(texFileName[i], &width, &height, &numChannels, 0);
		if (image != NULL)
		{
			if (numChannels == 1)
				format = GL_RED;
			else if (numChannels == 3)
				format = GL_RGB;
			else if (numChannels == 4)
				format = GL_RGBA;

		}
		else
		{
			fprintf(stderr, "error loading cube textures - %s \n", texFileName[i]);
			if (image != NULL) stbi_image_free(image);
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	}

	// set up the behaviour
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);

	return (0);
}



/*******************************************************************************************/
// loads a colour textures
// front (posZ) is purple (magenta), 
// back (negZ) is yellow, 
// left (negX) is green
// right (posX) is red
// top (posY) is blue)
// bottom (negY) is cyan



int Texture::loadColourTexture(void)
{


	int width = 1, height = 1;
	GLubyte posX[4] = { 255, 0, 0, 1 };
	GLubyte negX[4] = { 0, 255, 0, 1 };
	GLubyte posY[4] = { 0, 0, 255, 1 };
	GLubyte negY[4] = { 0, 255, 255, 1 };
	GLubyte posZ[4] = { 255, 0, 255, 1 };
	GLubyte negZ[4] = { 255, 255, 0, 1 };


	// Create texture object
	glGenTextures(1, &texId);
	//glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
	this->texTarget = GL_TEXTURE_CUBE_MAP;


	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, posX);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, negX);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, posY);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, negY);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, posZ);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, negZ);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);


	return 0;
}

/**********************************************************************************/

void Texture::bindToTextureUnit(GLuint textureType, int textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(textureType, texId);
	this->textureUnit = textureUnit;
}


/**********************************************************************************/

GLuint Texture::getTexId()
{
	return(texId);
}
/**********************************************************************************/

// the sampler id should correspond to the textureUnit

GLuint Texture::setTextureSampler(Shader shader, char *sampleName, GLuint textureUnit)
{
	int location;
	int rc = 0;

	// bind the texture to the texture unit
	bindToTextureUnit(texTarget, textureUnit);

	//copy the vertex position
	location = glGetUniformLocation(shader.getProgId(), sampleName);
	if (location == -1) {
		rc = -1;
		goto err;
	}
	glUniform1i(location, textureUnit - GL_TEXTURE0);
	//glUniform1i(location, GL_TEXTURE0);

	err:
	return(rc);
}