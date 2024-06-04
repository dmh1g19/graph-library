#ifndef RENDERING_H 
#define RENDERING_H  

#include <glad/glad.h>
#include <string>

void initBuffers(unsigned int&, unsigned int&, float*, size_t);
unsigned int initShaders(std::string&, std::string&);

std::string readShaderFromFile(std::string&);
void drawShape(unsigned int, unsigned int, int, int, bool);
void useSpecificShader(unsigned int);
void checkCompileErrors(unsigned int, std::string);
const char* getGLErrorString(GLenum);

#endif