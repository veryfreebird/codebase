#include <stdio.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#define KEY_ID 0x1234
int main () 
{
    int segment_id; 
    char* shared_memory; 
    struct shmid_ds shmbuffer; 
    int segment_size; 
    const int shared_segment_size = 0x6400; 

    /* Allocate a shared memory segment.  */ 
    segment_id = shmget (KEY_ID, shared_segment_size, 
            IPC_EXCL | S_IRUSR | S_IWUSR); 
    /* Attach the shared memory segment.  */ 
    shared_memory = (char*) shmat (segment_id, 0, 0); 
    printf ("shared memory reattached at address %p\n", shared_memory); 
    /* Print out the string from shared memory.  */ 
    printf ("%s\n", shared_memory); 
    /* Detach the shared memory segment.  */ 
    shmdt (shared_memory); 

    /* Deallocate the shared memory segment.  */ 
    shmctl (segment_id, IPC_RMID, 0); 

    return 0; 
} 
