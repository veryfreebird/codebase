// mid.cpp

#include <iostream>

void world();
class test{
    public: 
      int showhello();
};
#ifdef __cplusplus
extern "C" {  // 即使这是一个C++程序，下列这个函数的实现也要以C约定的风格来搞！
#endif
int call_showhello(test *p)
{
    return p->showhello();
    //return 0; 
}
void m_world()
{
    world();
    test tobject;
    //call_showhello(&tobject);
}

#ifdef __cplusplus
}
#endif
