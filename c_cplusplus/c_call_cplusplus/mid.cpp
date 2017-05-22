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

void m_world()
{
    world();
    test tobject;
    //tobject.showhello();
}

#ifdef __cplusplus
}
#endif
