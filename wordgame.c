#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char selectsort(char *);
bool checkwords(char *, char *);

int main(int argc, char *argv[])
{
  FILE *fp;
  char *filename = "dictionary.txt";
  char dic[16];
  char tmp_dic[16];
  char factor[16];
  char *tp, *tp_re;
  int i;
  int j = 0;

  if (argc < 2)
  {
    fprintf(stderr, "Usage: wordgame <alphabet>\n");
    exit(EXIT_FAILURE);
  }

  /*辞書のファイルオープン*/
  if ((fp = fopen(filename, "r")) == NULL)
  {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  /*入力の文字を配列に代入*/
  for (i = 1; i < argc; i++)
  {
    factor[j] = *argv[i];
    j++;
  }

  selectsort(factor);

  /*一行よみこむ、辞書は１６文字,改行含め１７*/
  while (fgets(dic, 16, fp) != '\0')
  {
    
    //fgetsの改行対策
    if ((tp = strtok(dic, "\n")) == NULL)
    { //最後実行すると１文字足りない
      tp = dic;
    }
    for(i=0;i<16;i++){
      tmp_dic[i]=dic[i];
    }
  printf("");
    // 結果に使う用の文字列
    char result[strlen(tp)]; //最初に宣言したところ、余計な文字列が出てきてしまった
    for (i = 0; i < strlen(tp); i++)
    {
      result[i] = tmp_dic[i];
    }
    //辞書の文字を順番に並べる
    selectsort(tmp_dic);

    if (checkwords(tmp_dic, factor) == true)
    {
      printf("%s \n", dic);
    };
  }
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

  /*とてもダサい,ここで１６文字のnull文字が消える*/
  while (cen[i] != '\0')
  {
    j = i + 1;
    while (cen[j] != '\0')
    {
      if (cen[i] > cen[j])
      {
        tmp = cen[i];
        cen[i] = cen[j];
        cen[j] = tmp;
      }
      j++;
    }
    i++;
  }
  return *cen;
}
/*入力した文字列と辞書との比較*/
bool checkwords(char *dicWord, char *checkWord)
{
  bool decision = true;
  char *d = dicWord;
  char *c = checkWord;
  int i = 0, j = 0;

  //あとで消す,辞書の文字数,strlenよりできればmblen、mbstowcsの方が良い

  while ((i < strlen(d) - 1) || (j < strlen(c)))
  {
    if ((d[i] == '\0') && (c[j] != '\0'))
    {
      break;
    }
    else if (d[i] == c[j])
    {
      i++;
      j++;
    }
    else
    {
      if (j == strlen(c) - 1)
      {
        decision = false;
        break;
      }
      if (d[i] != c[j])
      {
        j++;
      }
      else
      {
        printf("error\n");
      }
    }
  }
  return decision;
}
