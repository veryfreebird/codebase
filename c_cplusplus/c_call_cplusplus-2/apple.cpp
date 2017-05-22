#include "apple.h"  
Apple::Apple():m_nColor(APPLE_COLOR_RED)  
{  
}  

void Apple::SetColor(int color)  
{  
m_nColor = color;  
}  

int Apple::GetColor(void)  
{  
return m_nColor;  
}  
