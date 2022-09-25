#include <iostream>
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

void spriteRenderer::drawSprite(texture2D texture, glm::vec2 position, glm::vec2 size, glm::vec2 texPos, glm::vec2 texSize, glm::vec2 imageSize, float rotate, glm::vec3 colour, bool mirror)
{

    this->shader.use();
    // size = glm::vec2(size.x * 3.0f / 4.0f, size.y);//防止贴图被拉伸为四比三。
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));                     // 位移（先缩放、再旋转、最后位移，此处应逆序操作）
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // 将原点移至中心

    if (mirror)
    {
        // std::cout << "******************************************:" << std::endl;
        // std::cout << model[0][0] << "\t" << model[0][1] << "\t" << model[0][2] << "\t" << model[0][3] << std::endl
        //           << model[1][0] << "\t" << model[1][1] << "\t" << model[1][2] << "\t" << model[1][3] << std::endl
        //           << model[2][0] << "\t" << model[2][1] << "\t" << model[2][2] << "\t" << model[2][3] << std::endl
        //           << model[3][0] << "\t" << model[3][1] << "\t" << model[3][2] << "\t" << model[3][3] << std::endl;

        // 将对象水平镜像翻转（轴对称）

        model[0][0] *= -1;

        // std::cout << "###########" << std::endl;
        // // glm::mat3 model2 = glm::transpose(glm::mat3(model[0], model[1], model[2]));

        // std::cout << model[0][0] << "\t" << model[0][1] << "\t" << model[0][2] << "\t" << model[0][3] << std::endl
        //           << model[1][0] << "\t" << model[1][1] << "\t" << model[1][2] << "\t" << model[1][3] << std::endl
        //           << model[2][0] << "\t" << model[2][1] << "\t" << model[2][2] << "\t" << model[2][3] << std::endl
        //           << model[3][0] << "\t" << model[3][1] << "\t" << model[3][2] << "\t" << model[3][3] << std::endl;
        // std::cout << "******************************************:" << std::endl;
    }

    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // 旋转
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // 将原点移回
    model = glm::scale(model, glm::vec3(size, 1.0f));                               // 缩放

    this->shader.setMatrix4("model", model);

    glm::mat4 identity(1.0f);
    glm::mat4 texScale = glm::scale(identity, glm::vec3(1.0f / imageSize.x * texSize.x, 1.0f / imageSize.y * texSize.y, 1.0f));
    glm::mat4 texTrans = glm::translate(identity, glm::vec3(1.0f / imageSize.x * texPos.x, 1.0f / imageSize.y * texPos.y, 0.0f));
    this->shader.setMatrix4("texScale", texScale);
    this->shader.setMatrix4("texTrans", texTrans);

    // 渲染
    this->shader.setVector3f("spriteColor", colour);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    return;
}

void spriteRenderer::initRenderData()
{
    // 设置VAO与VBO
    uint32_t VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return;
}