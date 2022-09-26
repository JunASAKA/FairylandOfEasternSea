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
glm::vec2 playableCharacterPos = glm::vec2(320.0f, 448.0f);
// 自机模型大小
glm::vec2 playableCharacterSize = glm::vec2(28.0f, 32.0f);
// 阴阳玉速度
// const glm::vec2 damaVelocity(100.0f, -350.0f);
const glm::vec2 damaVelocity(80.0f, -275.0f);
// 阴阳玉半径
const float damaRadius = 12.5f;

glm::vec2 damaPos = playableCharacterPos + glm::vec2(playableCharacterSize.x / 2.0f - damaRadius,
                                                     -damaRadius * 2.0f);

/* 建构函数，指定信息*/
game::game(uint32_t width, uint32_t height, uint32_t playable_zone_x, uint32_t playable_zone_y, uint32_t playable_width, uint32_t playable_hight)
    : state(GAME_ACTIVE), keys(), width(width), height(height), playableZoneX(playable_zone_x), playableZoneY(playable_zone_y), playableWidth(playable_width), playableHight(playable_hight)
{
}

game::~game()
{

    delete SpriteRenderer;
    delete PlayableCharacter;
    delete OnmyouDama;
}

void game::init()
{
    /*加载着色器*/
    resourceManager::loadShader("../src/GLSL/vertexSource.glsl", "../src/GLSL/fragmentSource.glsl", nullptr, "sprite");
    /*配置Iro iro no Trans or scale矩阵与着色器*/
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    resourceManager::getShader("sprite").use().setInteger32("image", 0);
    resourceManager::getShader("sprite").setMatrix4("projection", projection);
    /*加载纹理*/
    resourceManager::loadTexture("../src/assets/playable.png", true, "playable");
    resourceManager::loadTexture("../src/assets/background.png", true, "background");
    resourceManager::loadTexture("../src/assets/texture.png", true, "texture");
    /*渲染*/
    SpriteRenderer = new spriteRenderer(resourceManager::getShader("sprite"));

    PlayableCharacter = new playableCharacter(playableCharacterPos, playableCharacterSize, resourceManager::getTexture("playable"), glm::vec2(4.0f, 3.0f), glm::vec2(28.0f, 32.0f), glm::vec2(312.0f, 244.0f));

    // load stages
    gameStage one;
    one.load("../src/assets/stage0", this->width, this->height / 2);
    // gameStage two; two.load("../src/assets/stage1", this->width, this->height / 2);
    // gameStage three; three.load("../src/assets/stage2", this->width, this->height / 2);
    // gameStage four; four.load("../src/assets/stage3", this->width, this->height / 2);
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
    OnmyouDama->move(deltaT, this->width);
    if (!OnmyouDama->stuck)
    {
        this->doCollisionCheck();
    }

    if (OnmyouDama->position.y >= this->height) // did ball reach bottom edge?
    {
        std::cout << "Reset required!" << std::endl;
        this->rstStage();
        this->rstPC();
    }

    return;
}

void game::processInput(float deltaT)
{
    if (this->state == GAME_ACTIVE)
    {
        float velocity = playableCharacterVelocity * deltaT;
        // 控制

        if (this->keys[GLFW_KEY_LEFT_SHIFT] || this->keys[GLFW_KEY_RIGHT_SHIFT])
        {
            velocity = velocity * 0.5f;
        }
        if (this->keys[GLFW_KEY_LEFT])
        {
            if (PlayableCharacter->position.x >= this->playableZoneX)
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
        if (this->keys[GLFW_KEY_RIGHT])
        {
            if (PlayableCharacter->position.x <= this->playableZoneX + playableWidth - PlayableCharacter->size.x)
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
        if (!this->keys[GLFW_KEY_LEFT] && !this->keys[GLFW_KEY_RIGHT])
        {
            PlayableCharacter->texPos.x = 4;
            PlayableCharacter->mirror = false;
            PlayableCharacter->status = 0;
        }
        if (this->keys[GLFW_KEY_SPACE])
        {
            OnmyouDama->stuck = false;
        }
        if (this->keys[GLFW_KEY_R])
        {
            std::cout << "Reset received!" << std::endl;
            this->rstPC();
            this->rstStage();
        }
        /*
        if (this->Keys[GLFW_KEY_UP])
        {
            if (PlayableCharacter->position.y >= this->playableZoneY)
            PlayableCharacter->position.y -= velocity;
        }
        if (this->Keys[GLFW_KEY_DOWN])
        {
            if (PlayableCharacter->position.y <= this->playableZoneY + playableHight - PlayableCharacter->size.y)
            PlayableCharacter->position.y += velocity;
        }
        */
    }

    return;
}

void game::render()
{
    //参数：texture 位置坐标 大小 贴图坐标 贴图大小 贴图原图大小 【旋转】【颜色】
    // SpriteRenderer->drawSprite(resourceManager::getTexture("PlayableCharacter"), glm::vec2(320, 32), glm::vec2(static_cast<float>(this->width)/20,
    //                                  static_cast<float>(this->height)/10), glm::vec2(0.0f, 0.0f), glm::vec2(32.0f, 48.0f), glm::vec2(256.0f, 256.0f));

    if (this->state == GAME_ACTIVE)
    {
        // background
        SpriteRenderer->drawSprite(resourceManager::getTexture("background"), glm::vec2(0, 0), glm::vec2(static_cast<float>(this->width), static_cast<float>(this->height)), glm::vec2(0, 0), glm::vec2(640.0f, 480.0f), glm::vec2(640.0f, 480.0f), 0, glm::vec3(0, 0, 0));

        // playableCharacter
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
                    OnmyouDama->velocity.x *= -1; // 反向水平速度
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
                    OnmyouDama->velocity.y *= -1; // 反向竖直速度
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
        OnmyouDama->velocity.y *= -1;
        OnmyouDama->velocity = glm::normalize(OnmyouDama->velocity) * glm::length(oldVelocity);
    }

    return;
}

void game::rstStage()
{
    if (this->stage == 0)
    {
        this->stages[0].load("../src/assets/stage0", this->width, this->height / 2);
    }

    else if (this->stage == 1)
    {
        this->stages[1].load("../src/assets/stage1", this->width, this->height / 2);
    }

    else if (this->stage == 2)
    {
        this->stages[2].load("../src/assets/stage2", this->width, this->height / 2);
    }

    else if (this->stage == 3)
    {
        this->stages[3].load("../src/assets/stage3", this->width, this->height / 2);
    }
}

void game::rstPC()
{
    // reset playableCharacter/ball stats
    PlayableCharacter->size = playableCharacterSize;
    PlayableCharacter->position = glm::vec2(this->width / 2.0f - playableCharacterSize.x / 2.0f, this->height - playableCharacterSize.y);
    OnmyouDama->reset(PlayableCharacter->position + glm::vec2(playableCharacterSize.x / 2.0f - damaRadius, -(damaRadius * 2.0f)), damaVelocity);
}
