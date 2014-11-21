#include "Renderer.h"
#include "Camera.h"
#include "FboHandler.h"
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>

enum WindowSize {
    WIDTH = 800,
    HEIGHT = 600
};

int main(void)
{
    Window window = Window(WIDTH, HEIGHT, "Screen Space Ambient Occlusion");
    Camera camera = Camera();

    // Create shaders.
    Shader* phongVert = new Shader("shaders/phong.vert", GL_VERTEX_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);

    // Initalize renderer.
    Renderer renderer = Renderer();

    // Initalize FBO:s
    FboHandler fboHandler = FboHandler();
    fboHandler.initFBO(WIDTH, HEIGHT);

    // Draw to window.
    fboHandler.useFBO(0);

    // Create shader program with the two current shaders and make it the current program.
    ShaderProgram* phongProgram = renderer.buildShaderProgram(phongVert, phongFrag);
    renderer.useProgram(phongProgram);

    delete phongVert;
    delete phongFrag;

    // Load in model.
    ModelImporter importer = ModelImporter();
    Model model = importer.importModel("models/teapot.obj");

    // Setup VAO, VBO and Uniforms.
    renderer.initBuffers(model);
    renderer.initUniforms();


    glm::mat4 M, V, P;

    LightSource lightSource = LightSource::PointLightSource(glm::vec3(0.0, 11.0, 18.0), glm::vec3(1.0, 0.5, 0.0));
    //LightSource* lightSource = LightSource::DirectionalLightSource(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.7, 0.2f, 0.0));
    renderer.initLightSource(lightSource);


    while(!window.isClosed()) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // GLfloat time = glfwGetTime();
        M = glm::mat4();//glm::rotate( glm::mat4(), time, glm::vec3(0.0, 1.0, 0.0));
        V = camera.getMatrix();

        renderer.update(M, V);

        glViewport(0, 0, window.getFramebufferWidth(), window.getFramebufferHeight());
        glDrawArrays(GL_TRIANGLES, 0, model.numVerts);

        window.update();
        camera.update(window);
    }

    // Cleanup
    delete phongProgram;

    glfwTerminate();

    return 0;
}
