#include <unistd.h>
#include <iostream>

#define SIZE 128
#define PROCESS_NUMBER 4

int main()
{
    char *process[]{
        "./processM",
        "./processA",
        "./processP",
        "./processS"
    };
    int pipes[2*(PROCESS_NUMBER+1)];
    int _pid[PROCESS_NUMBER];

    for(int i =  0;i<PROCESS_NUMBER+1;i++)
        if(pipe(pipes+i*2)<0)
            std::cout << "pipe error " << i << std::endl;

    for(int i = 0;i<PROCESS_NUMBER;i++){

        if(fork() != 0) continue;

        _pid[i] = getpid();
        for(int j = 0 ;j<PROCESS_NUMBER+1;j++){
            if(j != i && j!=i+1){
                close(pipes[2*j]);
                close(pipes[2*j+1]);
            }
        }
        close(pipes[2*i+1]);
        close(pipes[2*(i+1)]);
        if (dup2(pipes[2*i], STDIN_FILENO) != STDIN_FILENO)
            std::cerr << "dup2 error to stdin" << std::endl;
        if (dup2(pipes[2*(i+1)+1],STDOUT_FILENO)!= STDOUT_FILENO)
            std::cerr << "dup2 error to stdout" << std::endl;
        char* args2[] = { process[i],NULL};
        execvp(args2[0],args2);

    }

    for(int j = 1 ;j<PROCESS_NUMBER;j++){
            close(pipes[2*j]);
            close(pipes[2*j+1]);
    }

    close(pipes[2*PROCESS_NUMBER+1]);
    close(pipes[0]);

    char phrase[] = "13 14 15 0";
    char message[SIZE];
    unsigned long number;

    if(write(pipes[1],phrase, strlen(phrase)+1)<0)
        return 1;
    close(pipes[1]);

    int status;
    for(int i =0;i<PROCESS_NUMBER;i++){
        waitpid(_pid[i],&status,0);
        std::cout << "Child "<< process[i] <<" ended with Status "<< status << std::endl;
    }

    if(read(pipes[2*PROCESS_NUMBER], &message, SIZE)<0)
        return 1;

    std::cout << "Original message: " << phrase << std::endl;
    std::cout << "Result: ";
    char *ptr;
    number = strtol(message,&ptr,10);
    while(number){
        std::cout << number << " ";
        number = strtol(ptr,&ptr,10);
    }
    std::cout << std::endl;
    close(pipes[2*PROCESS_NUMBER+1]);
}