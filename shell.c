//Rodriguez de la Rosa Luis Enrique
//310264752
#include "grep.h"
#include <stdbool.h>



int pwd(){
  int status;
  pid_t pid;
  pid = fork();
    if(pid == 0){
      char cwd[1024];
      getcwd(cwd, sizeof(cwd));
      printf("%s\n", cwd);
      exit(EXIT_FAILURE);
    }else if(pid < 0){
      printf("Error\n");
      status = -1;
    }else{
      if(waitpid(pid,&status,0) != pid){
        printf("Error 2\n");
        status = -1;
      }
    }
    return status;
}



int ls(const char * arg){

  bool salto=true;
  int status;
  pid_t pid;
  pid = fork();
  if(pid == 0){

    char bandera[5];
    char dir[200];
    int val = 0;
    for(int i = 0; i < strlen(arg); i++){
      if(salto){
        bandera[i]=(arg[i]);
        if(isspace(arg[i])){
          bandera[i]='\0';
          salto=false;
        }
        }else{
          if(isspace((i-strlen(bandera)-1))){
            val=1;
          }else{
            dir[(i-strlen(bandera)-1)]=(arg[i]);
            if(isspace(arg[i+1])){
              dir[i+1]='\0';
              break;
            }
        }
      }
    }//for

    DIR* dire = opendir(bandera);
    if (dire)
    {
        execl("/bin/ls","/bin/ls",bandera,NULL);
        closedir(dire);
        exit(EXIT_FAILURE);
    }else{
    execl("/bin/ls","/bin/ls",bandera,dir,NULL);
    exit(EXIT_FAILURE);
    }

  }else if(pid < 0){
    printf("Error\n");
    status = -1;
  }else{
    if(waitpid(pid,&status,0) != pid){
      printf("Error 2\n");
      status = -1;
    }
  }
  return status;
}

int cat(const char * arg){
  int status;
  pid_t pid;
  pid = fork();
  if(pid == 0){

      bool salto=true;
    char bandera[200];
    char dir[200];
    int val = 0;
    for(int i = 0; i < strlen(arg); i++){
      if(salto){
        bandera[i]=(arg[i]);
        if(isspace(arg[i])){
          bandera[i]='\0';
          salto=false;
        }
        }else{
          if(isspace((i-strlen(bandera)-1))){
            val=1;
          }else{
            dir[(i-strlen(bandera)-1)]=(arg[i]);
            if(isspace(arg[i+1])){
              dir[i+1]='\0';
              break;
            }
        }
      }
    }//for

      bool cat2 = false;
      for(int i=0; i < strlen(dir);i++){
        if(dir[i] != '\0'){
          cat2=true;
        }
      }

    if(cat2){
          execl("/bin/cat","/bin/cat",bandera,dir,NULL);

          exit(EXIT_FAILURE);
    }else{

          execl("/bin/cat","/bin/cat",bandera,"",NULL);

          exit(EXIT_FAILURE);

    }
  }else if(pid < 0){
    printf("Error\n");
    status = -1;
  }else{
    if(waitpid(pid,&status,0) != pid){
      printf("Error 2\n");
      status = -1;
    }
  }
  return status;
  return 1;
}


int copy(const char * arg){
  int status;
  pid_t pid;
  pid = fork();
  if(pid == 0){

      bool salto=true;
    char bandera[200];
    char dir[200];
    int val = 0;
    for(int i = 0; i < strlen(arg); i++){
      if(salto){
        bandera[i]=(arg[i]);
        if(isspace(arg[i])){
          bandera[i]='\0';
          salto=false;
        }
        }else{
          if(isspace((i-strlen(bandera)-1))){
            val=1;
          }else{
            dir[(i-strlen(bandera)-1)]=(arg[i]);
            if(isspace(arg[i+1])){
              dir[i+1]='\0';
              break;
            }
        }
      }
    }//for


  execl("/bin/cp","/bin/cp",bandera,dir,(char *)0);
    exit(EXIT_FAILURE);

  }else if(pid < 0){
    printf("Error\n");
    status = -1;
  }else{
    if(waitpid(pid,&status,0) != pid){
      printf("Error 2\n");
      status = -1;
    }
  }
  return status;
  return 1;
}

int greep(const char * arg){
  printf("%s\n",arg );
  grep(arg);
}

int shell(){
  char buffer[1024];
  while(1){
    printf("ShellLayon$ ");
    fgets(buffer,1024,stdin);

    if(strncmp(buffer,"exit",4) == 0 )
      exit(0);
    if(strncmp(buffer,"ls",2) == 0 )
      ls(buffer + 3);
    if(strncmp(buffer,"pwd",3) == 0)
      pwd();
    if(strncmp(buffer,"cat",3) == 0)
      cat(buffer + 4);
    if(strncmp(buffer,"cp",2) == 0)
      copy(buffer + 3);
    if(strncmp(buffer,"grep",4) == 0)
        greep(buffer + 5);
  }
  return 1;
}

int main(){
  shell();
}
