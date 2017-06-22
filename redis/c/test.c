#include <stdio.h>
#include <hiredis/hiredis.h>

int main()
{
    redisContext *conn = redisConnect("127.0.0.1", 6379); //redis server默认端口
    char cmd[1000]; redisReply *reply;
    if(conn->err){
        printf("connection error: %d", conn->err);
    }   

    for(int i = 0; i<1000; i++)
    {
        sprintf(cmd, "set key%d %d", i);
        reply = redisCommand(conn, cmd);
        freeReplyObject(reply);
    }


    redisFree(conn);
}
