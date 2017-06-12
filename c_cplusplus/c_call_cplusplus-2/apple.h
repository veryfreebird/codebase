#ifndef __APPLE_H__  
#define __APPLE_H__  
class Apple  
{  
public:  
enum  
{  
APPLE_COLOR_RED,  
APPLE_COLOR_BLUE,  
APPLE_COLOR_GREEN,  
};  

Apple();  
int GetColor(void);  
void SetColor(int color);  
private:  
int m_nColor;  
};  
#endif   
