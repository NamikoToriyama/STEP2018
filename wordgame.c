#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char selectsort(char *);
// void swap(int *, int *);

int main(int argc, char *argv[])
{
  FILE *fp;
  char *filename = "dictionary.txt";
  char dic[16];
  char tmp;

  // if(argc<2){
  //   fprintf(stderr,"Usage: wordgame <ALPHABET>\n");
  //   exit(EXIT_FAILURE);
  // }

  if ((fp = fopen(filename, "r")) == NULL)
  {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  //一行よみこむ、辞書は１６文字なので１６文字
  while (fgets(dic, 16, fp) != '\0')
  {
    selectsort(dic);
    printf("%s", dic); //あとで消す
  }
    printf("\n");

  if (EOF == fclose(fp))
  {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  return 0;
}
/*文字列を並び替える関数*/
char selectsort(char *str)
{
  char *cen = str;
  char tmp;
  int i, j;

  while(cen[i]!='\0')//拡張for文で書きたかった
  {
    j=i+1;
    while(cen[j]!='\0')
    { 
      if (cen[i]>cen[j])
      {
        tmp=cen[i];
        cen[i]=cen[j];
        cen[j]=tmp;
      }
      j++;
    }
    i++;
  }
  return*cen;
}

