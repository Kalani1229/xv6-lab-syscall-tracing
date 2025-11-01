#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;
  
  if(argc < 2){
    fprintf(2, "Usage: strace <command> [args...]\n");
    exit(1);
  }
  
  pid = fork();
  if(pid < 0){
    fprintf(2, "fork failed\n");
    exit(1);
  }
  
  if(pid == 0){
    // Child process: execute the command
    exec(argv[1], &argv[1]);
    fprintf(2, "exec %s failed\n", argv[1]);
    exit(1);
  } else {
    // Parent process: enable tracing on child, then wait
    if(trace(pid) < 0){
      fprintf(2, "trace failed\n");
      exit(1);
    }
    wait(0);
  }
  
  exit(0);
}

