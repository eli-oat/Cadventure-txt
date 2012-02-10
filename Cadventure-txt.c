#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0 
#define bool char

void die(char *msg) {
  printf("%s\n", msg);
  exit(0);
}

void error(char *desc, int line) {
  char msg[1000];
  sprintf(msg, "ERROR at line %d: %s", line, desc);
  die(msg);
}

char story[1000][1000];
int lines = 0;
void read_story(char *filename) {
  FILE *fin = fopen(filename, "r");
  int i;

  if(!fin) die("Cannot open file");

  lines = 0;
  while(fgets(story[lines], sizeof(story[lines]), fin) != NULL) {
    lines++;
  }

  fclose(fin);
}

struct Function {
  int start, end, id;
  char name[50];
} functions[500];
int start_function, F;

void add_function(char *name, int start) {
  strcpy(functions[F].name, name);
  functions[F].start = start;
  functions[F].id = F;
  functions[F].end = start;
  if(strcmp(name, "START")==0) start_function = F;
  F++;
}

int find_function(char *name) {
  int i;
  for(i=0;i<F;i++) {
    if(strcmp(functions[i].name, name)==0) return i;
  }
  return -1;
}

struct Variable {
  int id;
  char name[50], value[50];
} variables[50];
int V;

struct Option {
  int id, function;
  char key, name[500];
} options[500];

inline bool is_letter(char c) {
  if ((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_') return true;
  else return false;
}

inline bool is_command(char c) {
  return (c=='=' || c=='@' || c=='>' || c=='-');
}

void init() {
  int i, j, k;
  char c, name[50];

  start_function = -1;
  for(i=0;i<lines;i++) {
    j = 0;
    while(story[i][j]==' ') j++;
    c = story[i][j];
    if(c=='@') { //Function definition
      j++;
      while(story[i][j]==' ') j++;
      k = 0;
      while(is_letter(story[i][j+k])) name[k++] = story[i][j+k];
      if(k==0) error("Expected function name after '='", i+1);
      name[k] = 0;
      add_function(name, i);
    }
    if(is_command(c)) { //Command
      if(F==0) error("Expected function decleration", i+1);
      functions[F-1].end = i;
    }
  }

  if(start_function == -1) error("Function 'START' not defined.", lines);
}

void print(char *msg) {
  printf("%s\n", msg);
}

void play(int func) {
  int i, j, k, O, l, function;
  char c, str[1000], name[500], function_name[50];
  bool cont;

  for(i=functions[func].start+1;i<=functions[func].end;i++) {
    j = 0;
    while(story[i][j]==' ') j++;
    c = story[i][j];
    if(!is_command(c)) continue;
    switch(c) {
      case '>': 
        sscanf(&story[i][j+(story[i][j+1]==' '?2:1)], "%[^\n]\n", str);
        print(str);
        break;
      case '=':
        j++;
        while(story[i][j]==' ') j++;
        sscanf(&story[i][j], "%s", str);
        int f = find_function(str);
        if(f==-1) error("Undefined function", i+1);
        play(f);
        break;
      case '-':
        O = 0;
        k = 0;
        while(true) {
          j = 0;
          while(story[i][j]==' ') j++;
          c = story[i][j];
          if(c!='-') break;
          j++;
          while(story[i][j]==' ') j++;
          c = story[i][j];
          if(!is_letter(c)) error("Expected valid key after the first '-'", i+1);
          options[O].key = c;
          j++;
          while(story[i][j]==' ') j++;
          c = story[i][j];
          if(c!='-') error("Expected '-' after option key", i+1);
          j++;
          while(story[i][j]==' ') j++;
          l = 0;
          while(is_letter(story[i][j+l]) || story[i][j+l]==' ') name[l++] = story[i][j+l];
          name[l] = 0;
          strcpy(options[O].name, name);
          j = j+l;
          while(story[i][j]==' ') j++;
          c = story[i][j];
          if(c!='-') error("Expected '-' after option name", i+1);
          j++;
          while(story[i][j]==' ') j++;
          sscanf(&story[i][j], "%s", function_name);
          function = find_function(function_name);
          if(function == -1) error("Undefined function", i+1);
          options[O].function = function;
          options[O].id = O; 

          O++;
          i++;
        }

        cont = true;
        while(cont) {
          printf("Choose an option:\n");
          for(k=0;k<O;k++) {
              printf("%c: %s\n", options[k].key, options[k].name);
          }
          printf("> ");
          scanf("%[^\n]%*c", str);
          c = str[0];
          for(k=0;k<O;k++) {
            if(c==options[k].key) {
              play(options[k].function);
              cont = false;
            }
          }
          if(cont) printf("That is not a valid option!\n");
        }
        i--;
        break;
    }
 
  }
}

int main(int argc, char *argv[]) {
  if(argc < 2) die("Please give a .story filename as a command-line argument.");
  read_story(argv[1]);
  init();
  play(start_function);

  return 0;
}
