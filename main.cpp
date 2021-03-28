#include<iostream>

#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

int main(){

    /*初始化ＧＬＦＷ*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//ＧＬＦＷ主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//ＧＬＦＷ亚版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*创建一个窗口*/
    GLFWwindow* window = glfwCreateWindow(1280, 960, "東方瀛洲誌 ~ Firyland of Eastern Sea ~", NULL, NULL);//创建窗口
    if(window == NULL){
        printf("窗口创建失败");
        glfwTerminate();//终止ＧＬＦＷ
        return -1;//返回－１暂且代表出错。
    }
    glfwMakeContextCurrent(window);//将ｗｉｎｄｏｗ作为当前进程的主要上下文。

    /*初始化ＧＬＥＷ*/
    
    return 0;//返回值０代表正常退出。
}
