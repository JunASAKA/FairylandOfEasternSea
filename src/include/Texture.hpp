
#ifndef TEXTURE_H
#define TEXTURE_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture2D {
   public:
    unsigned int ID;
    unsigned int Width, Height;
    unsigned int Internal_Format;  //贴图格式
    unsigned int Image_Format;	   //图像格式
    unsigned int Wrap_S;	   //Ｓ轴环绕方式
    unsigned int Wrap_T;	   //Ｔ轴环绕方式
    unsigned int Filter_Min;	   //缩小时过滤方式
    unsigned int Filter_Max;	   //放大时过滤方式
    Texture2D();		   //建构函数
    void Generate(unsigned int width, unsigned int height,
		  unsigned char *data);	 //生成贴图
    void Bind() const;			 //绑定贴图
};

#endif
