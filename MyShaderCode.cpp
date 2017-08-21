const char* vertexShaderCode =
"#version 440\r\n"
""
"in layout(location=0) vec2 position;"	//location 0 is position attribute,	vec2 is a 2 float coord, position is the position
"in layout(location = 1) vec3 vertexColor;" //location 1 is colour attribute,	vec3 is a 3 float coord, vertexColor is the variable where we store this color data 
""
"out vec3 theColor;"	//This gets sent out from vertex shader to the frag shader
""
"void main()"
"{"
"	gl_Position = vec4(position, 0.0, 1.0);"
"	theColor = vertexColor;"
"}"
"";



const char* fragmentShaderCode =
"#version 440\r\n"
""
"out vec4 daColor;"
""
"in vec3 theColor;"
""
"void main()"
"{"
"	daColor = vec4(theColor, 1.0);"
"}";
