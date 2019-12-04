#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

void  ClientProcess(int []);
void ServerProcess(int []);
int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;
     //telling the user how to use the program; what arguments to pass
     if (argc != 11) { //if there are not ten command line arguments following program itself 
          printf("Use: %s #1 #2 #3 #4 #5 #6 #7 #8 #9 #10\n", argv[0]);
          exit(1);
     }

     ShmID = shmget(IPC_PRIVATE, 10*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) { //returns an ID if successful, else returns -1 
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     
     //ShmPtr points to the shared memory segment 
     ShmPTR = (int *) shmat(ShmID, NULL, 0); //NULL means it will find a free address space for the segment; 
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     

     ShmPTR[0] = atoi(argv[1]); //turning the first argument (number) into an int, and storing it at the first block of space at the pointers referring address
     ShmPTR[1] = atoi(argv[2]);
     ShmPTR[2] = atoi(argv[3]);
     ShmPTR[3] = atoi(argv[4]);
     ShmPTR[4] = atoi(argv[5]);
     ShmPTR[5] = atoi(argv[6]);
     ShmPTR[6] = atoi(argv[7]);
     ShmPTR[7] = atoi(argv[8]);
     ShmPTR[8] = atoi(argv[9]);
     ShmPTR[9] = atoi(argv[10]);
  
     
    
     pid = fork(); //CHILD IS CREATED
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          ClientProcess(ShmPTR);
          
          exit(0); 
     }

     wait(&status);
    
     
     printf("Parent: %d %d %d %d %d %d %d %d %d %d  \n", ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3], ShmPTR[4], ShmPTR[5], ShmPTR[6], ShmPTR[7], ShmPTR[8], ShmPTR[9] );

     shmdt((void *) ShmPTR);
    
     shmctl(ShmID, IPC_RMID, NULL);
     
     exit(0);
}

void  ClientProcess(int  SharedMem[])
{
     printf("Child: %d %d %d %d %d %d %d %d %d %d\n",
                SharedMem[0], SharedMem[1], SharedMem[2], SharedMem[3], SharedMem[4], SharedMem[5], SharedMem[6], SharedMem[7], SharedMem[8], SharedMem[9]);
}
