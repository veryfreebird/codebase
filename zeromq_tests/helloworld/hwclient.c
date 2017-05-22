//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char** argv)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");
    
    int request_nbr;
    char buffer[10];
    if(argc == 2)
        sprintf(buffer, "hello%s",argv[1]);
    else
        sprintf(buffer, "hello");
    for (request_nbr = 0; request_nbr != 10000; request_nbr++) {
        //char buffer [10];
        printf ("Sending %s %d…\n", buffer, request_nbr);
        zmq_send (requester, buffer, strlen(buffer)+1, 0);
        zmq_recv (requester, buffer, 10, 0);
        printf ("Received %s %d\n", buffer, request_nbr);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}
