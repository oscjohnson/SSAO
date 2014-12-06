#ifndef SSAO_SHADER_PROGRAM_H
#define SSAO_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"

class SSAOShaderProgram : public BaseShaderProgram {
  public:
    SSAOShaderProgram(Shader* vert, Shader* frag) : BaseShaderProgram(vert, frag) {};
    ~SSAOShaderProgram();
    
    void update();
    void use();
    void initUniforms();
    void initBuffers(std::vector<Model*> *models = nullptr); 

  private:
    GLuint vbo[3];
};

#endif // SSAO_SHADER_PROGRAM_H