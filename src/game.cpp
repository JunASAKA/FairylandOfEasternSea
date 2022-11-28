#include "include/game.hpp"
#include "include/game_object.hpp"
#include "include/playable_character.hpp"
#include "include/onmyou_dama.hpp"
#include "include/resource_manager.hpp"
#include "include/sprite_renderer.hpp"
#include "include/physics.hpp"

sprite_renderer *sprite_renderer_obj;
playable_character *playable_character_obj; //自机，非判定点
onmyou_dama *onmyou_dama_obj;

// game objects
// 自机初始位置
glm::vec2 playable_character_pos = glm::vec2(320.0f, 448.0f);
// 自机模型大小
glm::vec2 playable_character_size = glm::vec2(28.0f, 32.0f);
// 阴阳玉速度
// const glm::vec2 dama_velocity(100.0f, -350.0f);
const glm::vec2 dama_velocity(80.0f, -275.0f);
// 阴阳玉半径
const float dama_radius = 12.5f;

glm::vec2 dama_pos = playable_character_pos + glm::vec2(playable_character_size.x / 2.0f - dama_radius,
                                                     -dama_radius * 2.0f);

/* 建构函数，指定信息*/
game::game(uint32_t width, uint32_t height, uint32_t playable_zone_x, uint32_t playable_zone_y, uint32_t playable_width, uint32_t playable_hight)
    : state(GAME_ACTIVE), keys(), width(width), height(height), playable_zone_x(playable_zone_x), playable_zone_y(playable_zone_y), playable_width(playable_width), playable_hight(playable_hight)
{
}

game::~game()
{

    delete sprite_renderer_obj;
    delete playable_character_obj;
    delete onmyou_dama_obj;
}

void game::init()
{
    /*加载着色器*/
    resource_manager::load_shader("../src/GLSL/vertex_source.glsl", "../src/GLSL/fragment_source.glsl", nullptr, "sprite");
    /*配置Iro iro no Trans or scale矩阵与着色器*/
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    resource_manager::get_shader("sprite").use().set_integer_32("image", 0);
    resource_manager::get_shader("sprite").set_matrix_4("projection", projection);
    /*加载纹理*/
    resource_manager::load_texture("../src/assets/playable.png", true, "playable");
    resource_manager::load_texture("../src/assets/background.png", true, "background");
    resource_manager::load_texture("../src/assets/texture.png", true, "texture");
    /*渲染*/
    sprite_renderer_obj = new sprite_renderer(resource_manager::get_shader("sprite"));

    playable_character_obj = new playable_character(playable_character_pos, playable_character_size, resource_manager::get_texture("playable"), glm::vec2(4.0f, 3.0f), glm::vec2(28.0f, 32.0f), glm::vec2(312.0f, 244.0f));

    // load stages
    game_stage one;
    one.load("../src/assets/stage0", this->width, this->height / 2);
    // game_stage two; two.load("../src/assets/stage1", this->width, this->height / 2);
    // game_stage three; three.load("../src/assets/stage2", this->width, this->height / 2);
    // game_stage four; four.load("../src/assets/stage3", this->width, this->height / 2);
    this->stages.push_back(one);
    // this->stages.push_back(two);
    // this->stages.push_back(three);
    // this->stages.push_back(four);
    this->stage = 0;

    onmyou_dama_obj = new onmyou_dama(dama_pos, glm::vec2(130.0f, 212.0f), glm::vec2(27.0f, 27.0f), glm::vec2(312.0f, 244.0f), dama_radius, dama_velocity, resource_manager::get_texture("playable"));

    return;
}

void game::update(float delta_t)
{
    onmyou_dama_obj->move(delta_t, this->width);
    if (!onmyou_dama_obj->stuck)
    {
        this->do_collision_check();
    }

    if (onmyou_dama_obj->position.y >= this->height) // did ball reach bottom edge?
    {
        std::cout << "Reset required!" << std::endl;
        this->rst_stage();
        this->rst_pc();
    }

    return;
}

void game::process_input(float delta_t)
{
    if (this->state == GAME_ACTIVE)
    {
        float velocity = playable_character_velocity * delta_t;
        // 控制

        if (this->keys[GLFW_KEY_LEFT_SHIFT] || this->keys[GLFW_KEY_RIGHT_SHIFT])
        {
            velocity = velocity * 0.5f;
        }
        if (this->keys[GLFW_KEY_LEFT])
        {
            if (playable_character_obj->position.x >= this->playable_zone_x)
            {
                // std::cout << playable_character_obj->position.x << std::endl;
                playable_character_obj->tex_pos.x = 37;
                playable_character_obj->mirror = true;
                playable_character_obj->status = 1;
                playable_character_obj->position.x -= velocity;

                if (onmyou_dama_obj->stuck)
                {
                    onmyou_dama_obj->position.x -= velocity;
                }
            }
        }
        if (this->keys[GLFW_KEY_RIGHT])
        {
            if (playable_character_obj->position.x <= this->playable_zone_x + playable_width - playable_character_obj->size.x)
            { // 边界控制：似乎自机左上角一点为自机座标。
                // std::cout << playable_character_obj->position.x << std::endl;
                playable_character_obj->tex_pos.x = 37;
                playable_character_obj->mirror = false;
                playable_character_obj->status = 1;
                playable_character_obj->position.x += velocity;

                if (onmyou_dama_obj->stuck)
                {
                    onmyou_dama_obj->position.x += velocity;
                }
            }
        }
        if (!this->keys[GLFW_KEY_LEFT] && !this->keys[GLFW_KEY_RIGHT])
        {
            playable_character_obj->tex_pos.x = 4;
            playable_character_obj->mirror = false;
            playable_character_obj->status = 0;
        }
        if (this->keys[GLFW_KEY_SPACE])
        {
            onmyou_dama_obj->stuck = false;
        }
        if (this->keys[GLFW_KEY_R])
        {
            std::cout << "Reset received!" << std::endl;
            this->rst_pc();
            this->rst_stage();
        }
        /*
        if (this->Keys[GLFW_KEY_UP])
        {
            if (playable_character_obj->position.y >= this->playable_zone_y)
            playable_character_obj->position.y -= velocity;
        }
        if (this->Keys[GLFW_KEY_DOWN])
        {
            if (playable_character_obj->position.y <= this->playable_zone_y + playable_hight - playable_character_obj->size.y)
            playable_character_obj->position.y += velocity;
        }
        */
    }

    return;
}

void game::render()
{
    //参数：texture 位置坐标 大小 贴图坐标 贴图大小 贴图原图大小 【旋转】【颜色】
    // sprite_renderer_obj->draw_sprite(resource_manager::get_texture("playable_character_obj"), glm::vec2(320, 32), glm::vec2(static_cast<float>(this->width)/20,
    //                                  static_cast<float>(this->height)/10), glm::vec2(0.0f, 0.0f), glm::vec2(32.0f, 48.0f), glm::vec2(256.0f, 256.0f));

    if (this->state == GAME_ACTIVE)
    {
        // background
        sprite_renderer_obj->draw_sprite(resource_manager::get_texture("background"), glm::vec2(0, 0), glm::vec2(static_cast<float>(this->width), static_cast<float>(this->height)), glm::vec2(0, 0), glm::vec2(640.0f, 480.0f), glm::vec2(640.0f, 480.0f), 0, glm::vec3(0, 0, 0));

        // playable_character
        playable_character_obj->draw(*sprite_renderer_obj);

        // stage
        this->stages[this->stage].draw(*sprite_renderer_obj);

        // onmyou_dama_obj
        onmyou_dama_obj->draw(*sprite_renderer_obj);
    }

    return;
}

void game::do_collision_check()
{
    for (game_object &obj : this->stages[this->stage].bricks)
    {
        if (!obj.destroyed)
        {
            collision collision_obj = physics::collision_check(*onmyou_dama_obj, obj);
            if (std::get<0>(collision_obj)) // bool值：是否碰撞
            {
                if (!obj.is_solid)
                {
                    obj.destroyed = true;
                }
                // 碰撞相关
                direction direc = std::get<1>(collision_obj);
                glm::vec2 diff_vec = std::get<2>(collision_obj);
                if (direc == LEFT || direc == RIGHT) // 水平碰撞
                {
                    onmyou_dama_obj->velocity.x *= -1; // 反向水平速度
                    float penetration = onmyou_dama_obj->radius - std::abs(diff_vec.x);
                    if (direc == LEFT)
                    {
                        onmyou_dama_obj->position.x += penetration; // 恢复阴阳玉位置
                    }
                    else
                    {
                        onmyou_dama_obj->position.x -= penetration;
                    }
                }
                else // 竖直碰撞
                {
                    onmyou_dama_obj->velocity.y *= -1; // 反向竖直速度
                    float penetration = onmyou_dama_obj->radius - std::abs(diff_vec.y);
                    if (direc == UP)
                    {

                        onmyou_dama_obj->position.y -= penetration;
                    }
                    else
                    {
                        onmyou_dama_obj->position.y += penetration;
                    }
                }
            }
        }
    }

    collision result = physics::collision_check(*onmyou_dama_obj, *playable_character_obj);
    if (!onmyou_dama_obj->stuck && std::get<0>(result))
    {
        // 碰撞力度与碰撞点与自机中心点之间的距离有关。
        float PCcentre = playable_character_obj->position.x + playable_character_obj->size.x / 2.0f; // 自机水平中心
        float distance = (onmyou_dama_obj->position.x + onmyou_dama_obj->radius) - PCcentre;         // 碰撞距离
        float percentage = distance / (playable_character_obj->size.x / 2.0f);                  // 碰撞力度系数
        // 碰撞力度
        float strength = 2.0f;
        glm::vec2 oldVelocity = onmyou_dama_obj->velocity;
        onmyou_dama_obj->velocity.x = dama_velocity.x * percentage * strength;
        onmyou_dama_obj->velocity.y *= -1;
        onmyou_dama_obj->velocity = glm::normalize(onmyou_dama_obj->velocity) * glm::length(oldVelocity);
    }

    return;
}

void game::rst_stage()
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

void game::rst_pc()
{
    // reset playable_character/ball stats
    playable_character_obj->size = playable_character_size;
    playable_character_obj->position = glm::vec2(this->width / 2.0f - playable_character_size.x / 2.0f, this->height - playable_character_size.y);
    onmyou_dama_obj->reset(playable_character_obj->position + glm::vec2(playable_character_size.x / 2.0f - dama_radius, -(dama_radius * 2.0f)), dama_velocity);
}
