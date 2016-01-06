/************************************************  file f1.c  ****/

#include <stdlib.h>  /* needed for system */
#include <string.h>  /* needed for strcpy */
#include <stdio.h>
#include "extern.h"

/* function prototypes */
double eval(char *str, int length, double *vect, int genes);
void printTypes(int p, int k, int b, int r, int q);

double eval(char *str, int length, double *vect, int genes)
{
  double sum;
  char command[200];
    
/*convert values into integers*/
  int p = (int)vect[0];
  int k = (int)vect[1];
  int b = (int)vect[2];
  int r = (int)(vect[3]);
  int q = (int)(vect[4]);


  /*set the environmental variables*/
  char buf[50];
  sprintf(buf, "%d", p);
    setenv("PawnValueMg", buf, 1);
    sprintf(buf, "%d", k);
    setenv("KnightValueMg", buf, 1);
    sprintf(buf, "%d", b);
    setenv("BishopValueMg", buf, 1);
    sprintf(buf, "%d", r);
    setenv("RookValueMg", buf, 1);
    sprintf(buf, "%d", q);
    setenv("QueenValueMg", buf, 1);

  printf("%d\t%d\t%d\t%d\t%d\t", p, k, b, r, q); /*print the genes*/
  printf("%d\t%d\t", Gen, Trials);  /*print the generation num and the trial num*/
  fflush(stdout);

  sum = 0.0;
    
  int i;
  for(i = 0; i < 2; i++){
      
      /*call Cutechess to similuate a match between stockfish19 and the evaluated engine (called sloppy)*/
      /*called twice (once per loop)*/
     strcpy(command, "./cutechess-cli/cutechess-cli -engine cmd=stockfish19 -engine cmd=sloppy -each proto=uci tc=40/1 -rounds 1 >> allout.txt");
    system(command);

    FILE * input;
    input = fopen("allout.txt", "r");
    char word[200];
    if(input != NULL){
      while(strcmp(word, "64:") != 0 ){  /*scan for the word before the score*/
	fscanf(input, "%s", word);
      }
      int score;
      fscanf(input, "%d", &score);  /*number of wins for stockfish19*/
      sum += score*2;  /*number of wins multiplied by 2 (a win is 2 points, draw is 1)*/
      fscanf(input, "%s", word);  /*hyphen*/
      fscanf(input, "%s", word);  /*number of losses for stockfish19*/
      fscanf(input, "%s", word);  /*hyphen*/
      fscanf(input, "%d", &score);  /*number of draws (not multiplied by a coefficient)*/
      sum += score;
    }
    else{
      printf("cannot open file\n");
    }
    fclose(input);
    system("rm allout.txt"); /*remove file so it can be used again*/

      /*call Cutechess to similuate a match between stockfish20 and the evaluated engine (called sloppy)*/
      /*called six times (3 times per loop)*/
 strcpy(command, "./cutechess-cli/cutechess-cli -engine cmd=stockfish20 -engine cmd=sloppy -each proto=uci tc=40/1 -rounds 1 >> allout.txt");
    system(command);

    input = fopen("allout.txt", "r");
    if(input != NULL){
      while(strcmp(word, "64:") != 0 ){  /*scan for the word before the score*/
	fscanf(input, "%s", word);
      }
      int score;
      fscanf(input, "%d", &score);  /*number of wins for stockfish20*/
      sum += score*2;  /*number of wins multiplied by 2 (a win is 2 points, draw is 1)*/
      fscanf(input, "%s", word);  /*hyphen*/
      fscanf(input, "%s", word);  /*number of losses for stockfish20*/
      fscanf(input, "%s", word);  /*hyphen*/
      fscanf(input, "%d", &score);  /*number of draws (not multiplied by a coefficient)*/
      sum += score;
    }
    else{
      printf("cannot open file\n");
    }
    close(input);
    system("rm allout.txt"); /*remove file so it can be used again*/

      /*call Cutechess to similuate a match between stockfish20 and the evaluated engine (called sloppy)*/
      /*called six times (3 times per loop)*/
    strcpy(command, "./cutechess-cli/cutechess-cli -engine cmd=stockfish20 -engine cmd=sloppy -each proto=uci tc=40/1 -rounds 1 >> allout.txt");
    system(command);

    input = fopen("allout.txt", "r");
    if(input != NULL){
      while(strcmp(word, "64:") != 0 ){  /*scan for the word before the score*/
	fscanf(input, "%s", word);
      }
      int score;
      fscanf(input, "%d", &score);  /*number of wins for stockfish20*/
      sum += score*2;  /*number of wins multiplied by 2 (a win is 2 points, draw is 1)*/
      fscanf(input, "%s", word);  /*hyphen*/
      fscanf(input, "%s", word);  /*number of losses for stockfish20*/
      fscanf(input, "%s", word);  /*hyphen*/
      fscanf(input, "%d", &score);  /*number of draws (not multiplied by a coefficient)*/
      sum += score;
    }
    else{
      printf("cannot open file\n");
    }
    fclose(input);
    system("rm allout.txt"); /*remove file so it can be used again*/

      /*call Cutechess to similuate a match between stockfish20 and the evaluated engine (called sloppy)*/
      /*called six times (3 times per loop)*/
    strcpy(command, "./cutechess-cli/cutechess-cli -engine cmd=stockfish20 -engine cmd=sloppy -each proto=uci tc=40/1 -rounds 1 >> allout.txt");
    system(command);

    input = fopen("allout.txt", "r");
    if(input != NULL){
      while(strcmp(word, "64:") != 0 ){  /*scan for the word before the score*/
	fscanf(input, "%s", word);
      }
      int score;
      fscanf(input, "%d", &score);  /*number of wins for stockfish20*/
      sum += score*2;  /*number of wins multiplied by 2 (a win is 2 points, draw is 1)*/
      fscanf(input, "%s", word);  /*hyphen*/
      fscanf(input, "%s", word);  /*number of losses for stockfish20*/
      fscanf(input, "%s", word);  /*hyphen*/
      fscanf(input, "%d", &score);  /*number of draws (not multiplied by a coefficient)*/
      sum += score;
    }
    else{
      printf("cannot open file\n");
    }
    fclose(input);
    system("rm allout.txt");  /*remove file so it can be used again*/
  }
  sum = 16-sum;  /*the fitness is 16-fitness because the fitness right now is the fitness of the default engine     against the modified one*/
    printf("%f\n", sum);  /*print out the fitness*/
    fflush(stdout);

  return (sum);
}


/************************************************ end of file ****/
