#include<iostream>

#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

/*事件处理函数之声明*/
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){//判定ESCAPE键是否按下
        glfwSetWindowShouldClose(window, true);//标记窗体window应该关闭
    }
}


/*程式入口*/
int main(){

    /*初始化ＧＬＦＷ*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//ＧＬＦＷ主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//ＧＬＦＷ亚版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*创建一个窗体window*/
    GLFWwindow* window = glfwCreateWindow(1280, 960, "東方瀛洲誌 ~ Firyland of Eastern Sea ~", NULL, NULL);//创建窗体
    if(window == NULL){
        printf("窗体创建失败");
        glfwTerminate();//终止ＧＬＦＷ
        return -1;//返回－１暂且代表出错。
    }
    glfwMakeContextCurrent(window);//将ｗｉｎｄｏｗ作为当前进程的主要上下文。

    /*初始化ＧＬＥＷ*/
    glewExperimental = true;//启用ＧＬＥＷ实验性功能
    if(glewInit() != GLEW_OK){
        printf("ＧＬＥＷ初始化失败");
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 1280, 960);//指定渲染范围（起始点与范围）。
    
    /*窗体window的任务*/
    while(!glfwWindowShouldClose(window)){
        /*处理输入事件*/
        processInput(window);//处理输入（声明于上文）

        /*渲染*/
        glClearColor(1.0f, 0, 0, 1.0f);//指定清屏用颜色（RGBA）
        glClear(GL_COLOR_BUFFER_BIT);//指定清理的暂存区

        /*接收事件与交换暂存区*/
        glfwSwapBuffers(window);//交换双暂存区
        glfwPollEvents();//接收事件
    }

    return 0;//返回值０代表正常退出。
}
