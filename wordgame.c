#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

char selectsort(char *);
bool checkwords(char *, char *,int);

int main(int argc, char *argv[])
{
  FILE *fp;
  char *filename = "dictionary.txt";
  char dic[16];
  char result[16];
  char factor[16];
  int i,count=0;
  int j=0;

  if(argc<2){
    fprintf(stderr,"Usage: wordgame <alphabet>\n");
    exit(EXIT_FAILURE);
  }

/*入力の文字を配列に代入*/
  for(i=1;i<argc;i++){
    factor[j]=*argv[i];
    j++;
  }
  
  printf("\n%s\n",factor);//あとで消す

  selectsort(factor);

  printf("%s\n",factor);//あとで消す

  /*辞書のファイルオープン*/
  if ((fp = fopen(filename, "r")) == NULL)
  {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  /*一行よみこむ、辞書は１６文字なので１６文字*/
  while (fgets(dic, 16, fp) != '\0')
  {
    for(i=0;i<16;i++){
    // 結果に使う用の文字列
    result[i]=dic[i];
    }
    //辞書の文字を順番に並べる
    selectsort(dic);
    if(checkwords(dic,factor,argc-1)==true){
      printf("%s",result); 
    };
  }
    printf("\n");//あとで消す

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

/*とてもダサいのでいい書き方を教えて欲しい*/
  while(cen[i]!='\0')
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
/*入力した文字列と辞書との比較*/
bool checkwords(char *dicWord, char *checkWord,int num){

  bool decision = true;
  char *d=dicWord;
  char *c=checkWord;
  int i=0,j=0,count;
  char test[]="abcdhk";

  printf("%d",num);
  return false;

  while(test[i]!='\0'){
    printf("%c",test[i]);
    i++;
  }

return false;

  while((d[i]!='\0')||(c[j]!='\0')){
    if(d[i]==c[j]){
      i++;
      j++;
    }
    else if(c[j]=='\0'){
      decision=false;
      break;
    }
    else if(d[i]!=c[j]){
      j++;
    }
    // else{
    //   decision=false;
    //   break;
    // }
  }

  if(decision==true){
    printf("%s",d);
  }

  return decision;
}

