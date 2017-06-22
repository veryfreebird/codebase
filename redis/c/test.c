#include <stdio.h>
#include <hiredis/hiredis.h>
#define max_num 1000
int main()
{
    redisContext *conn = redisConnect("127.0.0.1", 6379); //redis server默认端口
    char cmd[1000]; redisReply *reply;
    if(conn->err){
        printf("connection error: %d", conn->err);
    }   

    for(int i = 0; i<max_num; i++)
    {
        sprintf(cmd, "set key%d %d", i, i);
        reply = redisCommand(conn, cmd);
        freeReplyObject(reply);
    }

    for(int j=0; j<max_num; j++) //pipeline
    {
        sprintf(cmd, "get key%d", j);
        redisAppendCommand(conn, cmd);
    }

    for(int k=0; k<max_num; k++)
    {
        redisGetReply(conn, (void **)&reply);
        printf("Get key%d: %s\n", k, reply->str);
        freeReplyObject(reply);
    }
    redisFree(conn);
}
