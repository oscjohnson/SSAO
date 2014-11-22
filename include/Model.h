#include <string>
#include <assimp/scene.h>    

#include <glm/glm.hpp>

class Model {
	public:
	  Model(const std::string& filePath);
	  
	  void setOffset(long offs);
	  long getOffset();
	  
	  void setModelmatrix(glm::mat4 m);
	  glm::mat4 getModelmatrix();
	  
	  float* vertices;
	  float* normals;
	  int numVertices;
	private:
	  void processObject(const aiScene* object);
	  glm::mat4 modelmatrix;
	  long offset;
};