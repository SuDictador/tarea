//Rodriguez de la Rosa Luis Enrique
//310264752
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>

#include <stdbool.h>
int grep(const char * arg)
{

  bool salto=true;
char bandera1[200];
char dir2[200];
int val = 0;

        int z =0;
for(int i = 0; i < strlen(arg); i++){
  //  printf("%c\n",(arg[i]) );
  if(salto){
    bandera1[i]=(arg[i]);
    if(isspace(arg[i])){
      bandera1[i]='\0';
      salto=false;
    }
    }else{

        dir2[z]=(arg[i]);
        z++;
        if(isspace(arg[i+1])){
          dir2[z]='\0';
          break;
        }
  }
}//for
   FILE *fp;

   char * line = NULL;
   size_t len = 0;
   ssize_t read;

   fp = fopen(dir2, "r");

   if (fp == NULL)
   {
      perror("Error En el direcotio.\n");
      exit(EXIT_FAILURE);
   }

   int i =0;
   while ((read = getline(&line, &len, fp)) != -1) {
     char *result = strstr(line,bandera1);
     if(result != NULL){
       printf("linea=[%d] %s\n",i,line);
     }
     i++;
   }

   fclose(fp);
   return 0;
}
