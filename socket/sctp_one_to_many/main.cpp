#include "server.h"

int main(int argc,char **argv)
{
  SctpServer server;
  server.start();
  return 0;
}

