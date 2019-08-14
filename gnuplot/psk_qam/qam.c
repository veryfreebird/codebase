//QPSK信号星座图QAMconst.c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14159265

double randn()//标准高斯噪声产生（0均值，方差1）
{
  double r1,r2;
  r1=(double)rand()/RAND_MAX;
  r2=(double)rand()/RAND_MAX;
  return sqrt(-2*log(r1+1e-100))*cos(2*PI*r2);
}

int main(int argc, char *argv[])
{
  double x,y,x1,y1,s=0;//s相位旋转角(度)
  int i;
  int M=sqrt(64);
  double a=0.05;
  srand(1234);//随机数种子
  if(argc!=4)
    { //如果输入参数不足或多了则按默认参数计算
      printf("#Usage: a.exe att angle\n");
	  printf("#Default: 64QAM  a.exe 0.05 0 64\n");
    }
  else
    {
      a=atof(argv[1]);
      s=atof(argv[2]);
	  M=sqrt(atoi(argv[3]));
    }
	s=s/180.0*PI;//角度制转弧度
  for(i=0; i<1000; i++)
    {
      //标准QAM解调信号
      x=(rand()%M)*2-M+1;
      y=(rand()%M)*2-M+1;
      x=x+a*randn();//加复高斯噪声
      y=y+a*randn();
      x1=x*cos(s)-y*sin(s);//相位旋转
      y1=x*sin(s)+y*cos(s);
      printf("%f\t%f\n",x1,y1);//输出星座图数据
    }
    return 0;
}
