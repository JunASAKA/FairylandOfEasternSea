#include "include/fairyland_of_eastern_sea.hpp"

/*程式入口*/
int main()
{

    /* 初始化ＧＬＦＷ */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ＧＬＦＷ主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // ＧＬＦＷ亚版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, false); // 不允许调整窗体大小

    /* 创建一个窗体 */
    GLFWwindow *window = glfwCreateWindow(
        SCREEN_WIDTH, SCREEN_HEIGHT, "東方瀛洲誌 ~ Fairyland of Eastern Sea ~",
        nullptr, nullptr);          // 创建窗体
    glfwMakeContextCurrent(window); // 将ｗｉｎｄｏｗ作为当前进程的主要上下文。
    if (window == NULL)
    {
        std::cout << "[ERROR]:Failed to setup the window." << std::endl;
        glfwTerminate(); // 终止ＧＬＦＷ
        return -1;       // 返回－１暂且代表出错。
    }
    else
    {
        std::cout << "[Info]:Window has been setup successfully." << std::endl;
    }

    /* 初始化ＧＬＥＷ */
    glewExperimental = true; // 启用ＧＬＥＷ实验性功能
    if (glewInit() != GLEW_OK)
    {
        std::cout << "[ERROR]:Failed to initilize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    else
    {
        std::cout << "[Info]:GLEW has been inited successfully." << std::endl;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, SCREEN_WIDTH,
               SCREEN_HEIGHT);                         // 指定渲染范围（起始点与范围）。
    glEnable(GL_BLEND);                                // 启用混合功能
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 混合因子

    fairyland_of_eastern_sea.init();
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    fairyland_of_eastern_sea.state = GAME_ACTIVE;

    /*窗体window的任务*/
    while (!glfwWindowShouldClose(window))
    {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        glfwPollEvents(); // 接收事件

        /* 处理输入事件 */
        fairyland_of_eastern_sea.process_input(delta_time);

        fairyland_of_eastern_sea.update(delta_time);

        /* 渲染 */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 指定清屏用颜色（RGBA）
        glClear(GL_COLOR_BUFFER_BIT);         // 指定清理的暂存区

        fairyland_of_eastern_sea.render();

        glfwSwapBuffers(window); // 交换双暂存区
    }

    resource_manager::clear();

    glfwTerminate();

    return 0; // 返回值０代表正常退出。
}

void key_callback(GLFWwindow *window, int32_t key, int32_t scancode, int32_t action,
                  int32_t mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        std::cout << "Escape received!" << std::endl;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // if(key==GLFW_KEY_R&&action == GLFW_PRESS){
        
    // }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            fairyland_of_eastern_sea.keys[key] = GL_TRUE;
        }
        else if (action == GLFW_RELEASE)
        {
            fairyland_of_eastern_sea.keys[key] = GL_FALSE;
        }
    }

    return;
}
void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height)
{
    /* 保证ｖｉｅｗ　ｐｏｉｎｔ与窗体大小吻合 */
    glViewport(0, 0, width, height);

    return;
}
