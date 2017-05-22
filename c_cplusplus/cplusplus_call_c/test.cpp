// test.cpp
//
#include <stdio.h>
//
#ifdef __cplusplus
extern "C" {               // 告诉编译器下列代码要以C链接约定的模式进行链接
#endif

void hello();

#ifdef __cplusplus
}
#endif

int main()
{
  hello();
#ifdef __cplusplus
  printf("in c++ language\n");
#else
  printf("in c language\n");
#endif
  return 0;
}
