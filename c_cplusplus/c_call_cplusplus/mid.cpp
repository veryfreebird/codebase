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
struct hellotest
{
   test tobject;
};
int call_showhello(struct hellotest *p)
{
    return p->tobject.showhello();
    //return 0; 
}
void m_world()
{
    world();
    struct hellotest *ttobject = new struct hellotest;
    call_showhello(ttobject);
}

#ifdef __cplusplus
};
#endif
