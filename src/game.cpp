#include "include/game.hpp"
#include "include/resourceManager.hpp"
#include "include/spriteRenderer.hpp"
#include "include/gameObject.hpp"

spriteRenderer *Renderer;
gameObject *PlayableCharacter; //自机，非判定点

/*建构函数，指定信息*/
game::game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

game::~game()
{

    delete Renderer;
    delete PlayableCharacter;
}

void game::init()
{
    /*加载着色器*/
    resourceManager::loadShader("../src/GLSL/vertexSource.glsl", "../src/GLSL/fragmentSource.glsl", nullptr, "sprite");
    /*配置Iro iro no Trans or scale矩阵与着色器*/
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                      static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

    resourceManager::getShader("sprite").use().setInteger("image", 0);
    resourceManager::getShader("sprite").setMatrix4("projection", projection);
    /*加载纹理*/
    resourceManager::loadTexture("../src/assets/reimu.png", true, "PlayableCharacter");
    resourceManager::loadTexture("../src/assets/ui_bg.png",true, "ui_bg");
    /*渲染*/
    Renderer = new spriteRenderer(resourceManager::getShader("sprite"));

    //game objects
    glm::vec2 playerPos = glm::vec2(320,32);

    PlayableCharacter = new gameObject(playerPos, glm::vec2(static_cast<float>(this->Width)/20,
                                      static_cast<float>(this->Height)/10),resourceManager::getTexture("PlayableCharacter"),glm::vec2(0,0),glm::vec2(32.0f,48.0f),glm::vec2(256.0f,256.0f));
}

void game::update(float dt) {}

void game::processInput(float dt) {
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PC_VELOCITY * dt;
        // 控制
        //TODO: 边界控制
        if (this->Keys[GLFW_KEY_LEFT_SHIFT]||this->Keys[GLFW_KEY_RIGHT_SHIFT]){
            velocity = velocity * 0.5f;
        }
        if (this->Keys[GLFW_KEY_LEFT])
        {
            if (PlayableCharacter->position.x >= 0.0f)
                PlayableCharacter->position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_RIGHT])
        {
            if (PlayableCharacter->position.x <= this->Width - PlayableCharacter->size.x)
                PlayableCharacter->position.x += velocity;
        }
        if (this->Keys[GLFW_KEY_UP])
        {
            if (PlayableCharacter->position.y >= 0.0f)
                PlayableCharacter->position.y -= velocity;
        }
        if (this->Keys[GLFW_KEY_DOWN])
        {
            if (PlayableCharacter->position.y <= this->Height - PlayableCharacter->size.y)
                PlayableCharacter->position.y += velocity;
        }
    }
}

void game::render()
{
    //参数：texture 位置坐标 大小 贴图坐标 贴图大小 贴图原图大小 【旋转】【颜色】
    //Renderer->drawSprite(resourceManager::getTexture("PlayableCharacter"), glm::vec2(320, 32), glm::vec2(static_cast<float>(this->Width)/20,
    //                                  static_cast<float>(this->Height)/10), glm::vec2(0.0f, 0.0f), glm::vec2(32.0f, 48.0f), glm::vec2(256.0f, 256.0f));
    
    if(this->State == GAME_ACTIVE)
    {
        // background
        Renderer->drawSprite(resourceManager::getTexture("ui_bg"),glm::vec2(0,0),glm::vec2(static_cast<float>(this->Width),
                                      static_cast<float>(this->Height)),glm::vec2(0,0),glm::vec2(640.0f,480.0f),glm::vec2(640.0f,480.0f));

        // player
        PlayableCharacter->draw(*Renderer);
    }
}
