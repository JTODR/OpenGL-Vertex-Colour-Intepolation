#include <GL\glew.h>
#include <GL\freeglut.h>
#include "MyGLWindow.h"
#include <Windows.h>


#include <iostream>

extern const char* vertexShaderCode;	//Extern tells it to get vertexShaderCode elsewhere
extern const char* fragmentShaderCode;


void sendDataToOpenGL() {
	GLfloat verts[] =
	{
	

		+0.0f, +1.0f,				//
		+1.0f, +0.0f, +0.0f,		//VERTEX 

		-1.0f, -1.0f,
		+0.0f, +1.0f, +0.0f,

		+1.0f, -1.0f,
		+0.0f, +0.0f, +1.0f,
	};
	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);		//1: all we want is 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);	//Which buffer? The one bound to GL_ARRAY_BUFFER
							//Size of buffer? sizeof(verts)
							//Whats the data? verts
							//Usage? GL_STATIC_DRAW, this sends the data to an area of the graphics card where it can be read from but never changed again
	glEnableVertexAttribArray(0);		//Set the position as the 0th attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);		//0: is the position attribute 
							//2: No of elements per element in verts[] array
							//GL_FLOAT: type of these elements
							//GL_FALSE: OpenGl don't touch my data
							//sizeof(GLfloat) * 5: Stride, dist. from start of current vertex to start of next vertex
							//0: Pointer (leave 0 for now), it is a byte offset from the beginning of the buffer
	glEnableVertexAttribArray(1);		//Attribute 1 = Colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (char*)(sizeof(GLfloat) * 2));	//1: is attribute 1 (ie. colour attribute)
							//3: is the no of floats per attribute (ie. RGB)
							//GL_FLOAT: type of these elements
							//GL_FALSE: OpenGl don't touch my data
							//sizeof(GLfloat) * 5: Stride, dist. from start of current vertex to start of next vertex
							//(char*)(sizeof(GLfloat) * 2): is the offset, attribute starts after 2 floats (ie. after 2 position floats
							//then we need to typecast it to a (char*) in order to keep old opengl happy :)

	GLushort indices[] = { 0,1,2};		//Two triangles where 0 = (0,0), 1 = (1,1), 2 = (-1, -1) etc...
	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void installShaders() {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	adapter[0] = vertexShaderCode;

	glShaderSource(vertexShaderID, 1, adapter, 0);	//vertexShaderID: object ID
								//1: length of adapter array is 1
								//adapter: array of pointer to our code
								//0: telling compiler, when you see a zero in string (null terminated string) you end the string!

	adapter[0] = fragmentShaderCode;
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);		//compile the shaders
	glCompileShader(fragmentShaderID);

	GLuint programID = glCreateProgram();	//instanciate a program object 
	glAttachShader(programID, vertexShaderID);		//Attach/ link both of these shaders to our created program
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glUseProgram(programID);	//This exact line installs our vertex shader and our fragment shader
}

void MyGLWindow::initializeGL() {
	glewInit();
	sendDataToOpenGL();
	installShaders();
}


void MyGLWindow::paintGL() {
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);		//GL_TRIANGLES: is the mode, ie. what we want to draw with the verticies
				  //6: the no. of coords
					//GL_UNSIGNED_SHORT: the type of the indices array, as this is whats in our element array
					//0: its an offset to the element array buffer, ours are at zero so leave it 0

	glEnd();	//ends the function
	glFlush();	//Redraws the window and completes in finite time

}
