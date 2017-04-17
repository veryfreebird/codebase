#include <stdio.h>  
#include <time.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
  
#include <iostream>  
#include <sstream>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

#include <vector>

#include <stdint.h>

  
#include "hiredis.h"  
using namespace std;



#define CPU_FREQ 2494 //MHz
uint64_t rdtsc(void)
{
        unsigned int low, high;

        asm volatile("rdtsc" : "=a" (low), "=d" (high));

        return low | ((uint64_t)high) << 32;
}

#define INIT_CLOCK(name) uint64_t clock##name

#define START_CLOCK(name) \
do \
{  \
clock##name = rdtsc() ; \
}while(0)


#define STOP_CLOCK(name) \
        do \
{ \
        uint64_t time_spent = rdtsc() - clock##name ; \
        printf("Time taken in microseconds %lu in cycles %lu\n", time_spent/CPU_FREQ, time_spent) ; \
}while(0)

/*
CREATE TABLE "Connection" (
  "id" int NOT NULL PRIMARY KEY,
  "streamId" SMALLINT NOT NULL,
  "contextId" INTEGER NOT NULL,
  "recvAddr" INTEGER NOT NULL,
  "mmeUeId" BIGINT NULL,
  "neighbourUeENBId" INTEGER NULL,
  "status" INTEGER NOT NULL);
*/

class Connection
{
        public:
                unsigned long id ;
                unsigned long streamId ;
                unsigned long contextId ;
                unsigned long recvAddr ;
                unsigned long mmeUeId ;
                unsigned long neighbourUeENBId ;
                unsigned long status ;

        Connection(unsigned long id , unsigned long streamId,unsigned long contextId,unsigned long recvAddr,
                        unsigned long mmeUeId ,unsigned long neighbourUeENBId,unsigned long status)
        {
                this->id = id ;
                this->streamId = streamId ;
                this->contextId = contextId ;
                this->recvAddr = recvAddr ;
                this->mmeUeId = mmeUeId ;
                this->neighbourUeENBId = neighbourUeENBId ;
                this->status = status ;
        }

        Connection() {}
} ;

typedef vector<Connection *> Connections;

redisContext *c;
Connections connections ;

void add_to_connection_list(Connection *conn)
{
        connections.push_back(conn) ;
}

#ifdef DEBUG_BENCHMARK
void print_connection_list_size()
{
        printf("connection list size %lu\n", connections.size() ) ;
}
#endif

void clear_connection_list()
{
        connections.clear() ;
}

int offeset = 0; 
void set(int i)  
{  
	Connection t (i+offeset,i+offeset, i+offeset, i+offeset, i+offeset, i+offeset, i+offeset) ;

	const char *v[4];  
	size_t vlen[4];  
	char field[1000] ;
	v[0] = "hset";  
	vlen[0] = strlen("hset");  

	v[1] = "h";  
	vlen[1] = strlen("h");  
	sprintf(field, "f%d", i) ;
	v[2] = (const char *)field;  
	vlen[2] = strlen(field);  

	v[3] = (const char *)&t;  
	vlen[3] = sizeof(Connection);  

	redisReply *r = (redisReply *)redisCommandArgv(c, sizeof(v) / sizeof(v[0]), v, vlen);  
	if (!r) {  
		printf("empty reply because (%d)%s\n", c->err, c->errstr);  
		exit(1);  
	}  


#ifdef DEBUG_BENCHMARK
	printf("reply: %s\n", r->str);  
#endif

	freeReplyObject(r);  
}  

void get(int i)  
{  

	char field[1000] ;
	sprintf(field, "f%d", i) ;
	redisReply *r = (redisReply *)redisCommand(c, "hget h f%d", i);  
	if (!r) {  
		printf("empty reply because (%d)%s\n", c->err, c->errstr);  
		exit(1);  
	}  
#ifdef DEBUG_BENCHMARK
	printf("reply length: %d\n", r->len);  
#endif
	if (r->len != sizeof(Connection)) {  
		printf("reply len error\n");  
		exit(-1);  
	}  

	Connection  *p = (Connection *)malloc(sizeof(Connection));  
	if (!p) {  
		printf("malloc fail\n");  
		exit(-1);  
	}  
	memcpy(p, r->str, r->len); 
	add_to_connection_list(p) ;	
	freeReplyObject(r);  
}  

void del(int i)  
{  

	char field[1000] ;
	sprintf(field, "f%d", i) ;
	redisReply *r = (redisReply *)redisCommand(c, "hdel h f%d", i);  
	if (!r) {  
		printf("empty reply because (%d)%s\n", c->err, c->errstr);  
		exit(1);  
	}  
#ifdef DEBUG_BENCHMARK
	printf("reply: %s\n", r->str);  
#endif
	freeReplyObject(r);  
}  
int entris_in_db = 0 ;

void hgetall(void)  
{  
   redisReply *r = (redisReply *)redisCommand(c, "hgetall h");  
    if (!r) {  
        printf("empty reply because (%d)%s\n", c->err, c->errstr);  
        exit(1);  
    } 
	entris_in_db = 0; 
#ifdef DEBUG_BENCHMARK 
    printf("reply length: %lu(elements: %d)\n", r->len, r->elements);  
#endif

 
    for (size_t i = 0; i < r->elements; i++) {  

#ifdef DEBUG_BENCHMARK
	    printf("element length: %u\n", r->element[i]->len);  
#endif
	    if( (i & 0x1) == 1 )
	    {
		    if (r->element[i]->len != sizeof(Connection)) {  
			    printf(" getall reply len error\n");  
			    exit(-1);  
		    } 
		    Connection *p = (Connection *)malloc(sizeof(Connection));  
		    if (!p) {  
			    printf("malloc fail\n");  
			    exit(-1);  
		    }  

		    memcpy(p, r->element[i]->str, r->element[i]->len);  
		    add_to_connection_list(p) ;	
		    entris_in_db ++ ;
	    }
#ifdef DEBUG_BENCHMARK
	    else
	    {

		    printf ("feilds: %s\n", r->element[i]->str);
	    }
#endif
    }  

    freeReplyObject(r);  
}  

INIT_CLOCK(benchmark) ;
int main(int argc, char **argv)  
{
	int num_entry = (argc > 1)?  atoi(argv[1]) : 100000;
	const char *hostname = (argc > 2) ? argv[2] : "127.0.0.1";
	int port = (argc > 3) ? atoi(argv[3]) : 6379;
	int itr = 0 ;
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout(hostname, port, timeout);
	if (c == NULL || c->err)
	{
		if (c)
		{
			printf("Connection error: %s\n", c->errstr);
			redisFree(c);
		} else
		{
			printf("Connection error: can't allocate redis context\n");
		}
		exit(1);
	}


	printf("set\n") ;
	START_CLOCK(benchmark) ;
	for (int  itr = 0 ; itr < num_entry; itr ++ )
	{

		set(itr);  
	}
	STOP_CLOCK(benchmark) ;

	printf("update\n") ;
	offeset = 1 ;
	START_CLOCK(benchmark) ;
	for (int  itr = 0 ; itr < num_entry; itr ++ )
	{

		set(itr);  
	}
	STOP_CLOCK(benchmark) ;
	offeset = 0 ;

	printf("get\n") ;
	START_CLOCK(benchmark) ;
	for (int  itr = 0 ; itr < num_entry; itr ++ )
	{

		get(itr);
	}
	STOP_CLOCK(benchmark) ;
	printf("getall\n") ;
	START_CLOCK(benchmark) ;
	for (int  itr = 0 ; itr < 100; itr ++ )
	{
		hgetall() ;
	}
	STOP_CLOCK(benchmark) ;

	printf("entris_in_db %d\n", entris_in_db) ;

	printf("del\n") ;
	START_CLOCK(benchmark) ;
	for (int  itr = 0 ; itr < num_entry; itr ++ )
	{
		del(itr);
	}
	STOP_CLOCK(benchmark) ;

	return 0 ; 
}  

