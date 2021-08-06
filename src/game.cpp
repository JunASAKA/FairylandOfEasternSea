#include "include/game.hpp"
#include "include/resourceManager.hpp"
#include "include/spriteRenderer.hpp"

spriteRenderer *Renderer;

/*建构函数，指定信息*/
game::game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

game::~game() {

    delete Renderer;

}

void game::init() {
     /*加载着色器*/
    resourceManager::loadShader("../src/GLSL/vertexSource.glsl", "../src/GLSL/fragmentSource.glsl", nullptr, "sprite");
    /*配置Iro iro no Trans or scale矩阵与着色器*/
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    glm::mat4 identity(1.0f);
    glm::mat4 texScale = glm::scale(identity,glm::vec3(0.00390625f*59.0f,0.00390625f*59.0f,1.0f));
    glm::mat4 texTrans = glm::translate(identity,glm::vec3(0.00390625f*2.0f,0.00390625f*194.0f,0.0f));
    
    resourceManager::getShader("sprite").use().setInteger("image", 0);
    resourceManager::getShader("sprite").setMatrix4("projection", projection);
    resourceManager::getShader("sprite").setMatrix4("texScale",texScale);
    resourceManager::getShader("sprite").setMatrix4("texTrans",texTrans);
    /*加载纹理*/
    resourceManager::loadTexture("../src/assets/reimu.png", true, "PlayableCharacter");
    /*渲染*/
    Renderer = new spriteRenderer(resourceManager::getShader("sprite"));

    
}

void game::update(float dt) {}

void game::processInput(float dt) {}

void game::render() {
    Renderer->drawSprite(resourceManager::getTexture("PlayableCharacter"), glm::vec2(1221,0), glm::vec2(59, 59), 0.0f, glm::vec3(1.0f));
}
