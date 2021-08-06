#include "include/spriteRenderer.hpp"


spriteRenderer::spriteRenderer(class shader shader)
{
    this->shader = shader;
    this->initRenderData();
}

spriteRenderer::~spriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void spriteRenderer::drawSprite(texture2D texture, glm::vec2 position, glm::vec2 size, glm::vec2 texPos, glm::vec2 texSize, glm::vec2 imageSize, float rotate, glm::vec3 colour)
{

    this->shader.use();
    //size = glm::vec2(size.x * 3.0f / 4.0f, size.y);//防止贴图被拉伸为四比三。
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->shader.setMatrix4("model", model);

     glm::mat4 identity(1.0f);
     glm::mat4 texScale = glm::scale(identity,glm::vec3(1.0f/imageSize.x*texSize.x,1.0f/imageSize.y*texSize.y,1.0f));
    glm::mat4 texTrans = glm::translate(identity,glm::vec3(1.0f/imageSize.x*texPos.x,1.0f/imageSize.x*texPos.y,0.0f));
    this->shader.setMatrix4("texScale",texScale);
    this->shader.setMatrix4("texTrans",texTrans);


    // render textured quad
    this->shader.setVector3f("spriteColor", colour);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void spriteRenderer::initRenderData()
{
    // 设置VAO与VBO
    unsigned int VBO;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}