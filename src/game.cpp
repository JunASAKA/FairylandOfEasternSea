#include "include/game.hpp"
#include "include/gameObject.hpp"
#include "include/playableCharacter.hpp"
#include "include/onmyouDama.hpp"
#include "include/resourceManager.hpp"
#include "include/spriteRenderer.hpp"
#include "include/physics.hpp"

spriteRenderer *SpriteRenderer;
playableCharacter *PlayableCharacter; //自机，非判定点
onmyouDama *OnmyouDama;

// game objects
// 自机初始位置
glm::vec2 playerPos = glm::vec2(320.0f, 448.0f);
// 自机模型大小
glm::vec2 playerSize = glm::vec2(28.0f, 32.0f);
// 阴阳玉速度
const glm::vec2 damaVelocity(100.0f, -350.0f);
// 阴阳玉半径
const float damaRadius = 12.5f;

glm::vec2 damaPos = playerPos + glm::vec2(playerSize.x / 2.0f - damaRadius,
                                          -damaRadius * 2.0f);

/* 建构函数，指定信息*/
game::game(uint32_t width, uint32_t height, uint32_t playable_zone_x, uint32_t playable_zone_y, uint32_t playable_width, uint32_t playable_hight)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), Playable_Zone_X(playable_zone_x), Playable_Zone_Y(playable_zone_y), Playable_Width(playable_width), Playable_Hight(playable_hight)
{
}

game::~game()
{

    delete SpriteRenderer;
    delete PlayableCharacter;
}

void game::init()
{
    /*加载着色器*/
    resourceManager::loadShader("../src/GLSL/vertexSource.glsl", "../src/GLSL/fragmentSource.glsl", nullptr, "sprite");
    /*配置Iro iro no Trans or scale矩阵与着色器*/
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                      static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

    resourceManager::getShader("sprite").use().setInteger32("image", 0);
    resourceManager::getShader("sprite").setMatrix4("projection", projection);
    /*加载纹理*/
    resourceManager::loadTexture("../src/assets/playable.png", true, "playable");
    resourceManager::loadTexture("../src/assets/background.png", true, "background");
    resourceManager::loadTexture("../src/assets/texture.png", true, "texture");
    /*渲染*/
    SpriteRenderer = new spriteRenderer(resourceManager::getShader("sprite"));

    PlayableCharacter = new playableCharacter(playerPos, playerSize, resourceManager::getTexture("playable"), glm::vec2(4.0f, 3.0f), glm::vec2(28.0f, 32.0f), glm::vec2(312.0f, 244.0f));

    // load stages
    gameStage one;
    one.load("../src/assets/stage1", this->Width, this->Height / 2);
    // gameStage two; two.load("levels/two.lvl", this->Width, this->Height / 2);
    // gameStage three; three.load("levels/three.lvl", this->Width, this->Height / 2);
    // gameStage four; four.load("levels/four.lvl", this->Width, this->Height / 2);
    this->stages.push_back(one);
    // this->stages.push_back(two);
    // this->stages.push_back(three);
    // this->stages.push_back(four);
    this->stage = 0;

    OnmyouDama = new onmyouDama(damaPos, glm::vec2(130.0f, 212.0f), glm::vec2(27.0f, 27.0f), glm::vec2(312.0f, 244.0f), damaRadius, damaVelocity, resourceManager::getTexture("playable"));

    return;
}

void game::update(float deltaT)
{
    OnmyouDama->move(deltaT, this->Width);
    this->doCollisionCheck();

    return;
}

void game::processInput(float deltaT)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = playableCharacterVelocity * deltaT;
        // 控制

        if (this->Keys[GLFW_KEY_LEFT_SHIFT] || this->Keys[GLFW_KEY_RIGHT_SHIFT])
        {
            velocity = velocity * 0.5f;
        }
        if (this->Keys[GLFW_KEY_LEFT])
        {
            if (PlayableCharacter->position.x >= this->Playable_Zone_X)
            {
                // std::cout << PlayableCharacter->position.x << std::endl;
                PlayableCharacter->texPos.x = 37;
                PlayableCharacter->mirror = true;
                PlayableCharacter->status = 1;
                PlayableCharacter->position.x -= velocity;

                if (OnmyouDama->stuck)
                {
                    OnmyouDama->position.x -= velocity;
                }
            }
        }
        if (this->Keys[GLFW_KEY_RIGHT])
        {
            if (PlayableCharacter->position.x <= this->Playable_Zone_X + Playable_Width - PlayableCharacter->size.x)
            { // 边界控制：似乎自机左上角一点为自机座标。
                // std::cout << PlayableCharacter->position.x << std::endl;
                PlayableCharacter->texPos.x = 37;
                PlayableCharacter->mirror = false;
                PlayableCharacter->status = 1;
                PlayableCharacter->position.x += velocity;

                if (OnmyouDama->stuck)
                {
                    OnmyouDama->position.x += velocity;
                }
            }
        }
        if (!this->Keys[GLFW_KEY_LEFT] && !this->Keys[GLFW_KEY_RIGHT])
        {
            PlayableCharacter->texPos.x = 4;
            PlayableCharacter->mirror = false;
            PlayableCharacter->status = 0;
        }
        if (this->Keys[GLFW_KEY_SPACE])
        {
            OnmyouDama->stuck = false;
        }
        /*
        if (this->Keys[GLFW_KEY_UP])
        {
            if (PlayableCharacter->position.y >= this->Playable_Zone_Y)
            PlayableCharacter->position.y -= velocity;
        }
        if (this->Keys[GLFW_KEY_DOWN])
        {
            if (PlayableCharacter->position.y <= this->Playable_Zone_Y + Playable_Hight - PlayableCharacter->size.y)
            PlayableCharacter->position.y += velocity;
        }
        */
    }

    return;
}

void game::render()
{
    //参数：texture 位置坐标 大小 贴图坐标 贴图大小 贴图原图大小 【旋转】【颜色】
    // SpriteRenderer->drawSprite(resourceManager::getTexture("PlayableCharacter"), glm::vec2(320, 32), glm::vec2(static_cast<float>(this->Width)/20,
    //                                  static_cast<float>(this->Height)/10), glm::vec2(0.0f, 0.0f), glm::vec2(32.0f, 48.0f), glm::vec2(256.0f, 256.0f));

    if (this->State == GAME_ACTIVE)
    {
        // background
        SpriteRenderer->drawSprite(resourceManager::getTexture("background"), glm::vec2(0, 0), glm::vec2(static_cast<float>(this->Width), static_cast<float>(this->Height)), glm::vec2(0, 0), glm::vec2(640.0f, 480.0f), glm::vec2(640.0f, 480.0f), 0, glm::vec3(0, 0, 0));

        // player
        PlayableCharacter->draw(*SpriteRenderer);

        // stage
        this->stages[this->stage].draw(*SpriteRenderer);

        // OnmyouDama
        OnmyouDama->draw(*SpriteRenderer);
    }

    return;
}

void game::doCollisionCheck()
{
    for (gameObject &obj : this->stages[this->stage].bricks)
    {
        if (!obj.destroyed)
        {
            collision Collision = physics::collisionCheck(*OnmyouDama, obj);
            if (std::get<0>(Collision)) // bool值：是否碰撞
            {
                if (!obj.isSolid)
                {
                    obj.destroyed = true;
                }
                // 碰撞相关
                direction direc = std::get<1>(Collision);
                glm::vec2 diffVec = std::get<2>(Collision);
                if (direc == LEFT || direc == RIGHT) // 水平碰撞
                {
                    OnmyouDama->velocity.x = -OnmyouDama->velocity.x; // 反向水平速度
                    float penetration = OnmyouDama->radius - std::abs(diffVec.x);
                    if (direc == LEFT)
                    {
                        OnmyouDama->position.x += penetration; // 恢复阴阳玉位置
                    }
                    else
                    {
                        OnmyouDama->position.x -= penetration;
                    }
                }
                else // 竖直碰撞
                {
                    OnmyouDama->velocity.y = -OnmyouDama->velocity.y; // 反向竖直速度
                    float penetration = OnmyouDama->radius - std::abs(diffVec.y);
                    if (direc == UP)
                    {

                        OnmyouDama->position.y -= penetration;
                    }
                    else
                    {
                        OnmyouDama->position.y += penetration;
                    }
                }
            }
        }
    }

    collision result = physics::collisionCheck(*OnmyouDama, *PlayableCharacter);
    if (!OnmyouDama->stuck && std::get<0>(result))
    {
        // 碰撞力度与碰撞点与自机中心点之间的距离有关。
        float PCcentre = PlayableCharacter->position.x + PlayableCharacter->size.x / 2.0f; // 自机水平中心
        float distance = (OnmyouDama->position.x + OnmyouDama->radius) - PCcentre;         // 碰撞距离
        float percentage = distance / (PlayableCharacter->size.x / 2.0f);                  // 碰撞力度系数
        // 碰撞力度
        float strength = 2.0f;
        glm::vec2 oldVelocity = OnmyouDama->velocity;
        OnmyouDama->velocity.x = damaVelocity.x * percentage * strength;
        OnmyouDama->velocity.y = -OnmyouDama->velocity.y;
        OnmyouDama->velocity = glm::normalize(OnmyouDama->velocity) * glm::length(oldVelocity);
    }

    return;
}