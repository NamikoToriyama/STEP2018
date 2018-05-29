#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUF 20
char selectsort(char *);
bool checkwords(char *, char *);
int scoreword(char *);

// 大文字対応
// １行目は並び替えがされない（まあ１行目は大丈夫だが）
//点数高い順に並べる関数
//１文字減る時
//

int main(int argc, char *argv[])
{
  FILE *fp;
  char *filename = "test.txt";
  char dic[BUF];
  char factor[BUF];
  char *tp;
  int i = 0;
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
  for (int i = 1; i < argc; i++)
  {
    factor[j] = *argv[i];
    j++;
  }
  factor[j] = '\0';
  selectsort(factor);
  printf("%s\n", factor);
  printf("\n<result>\n");

  /*一行よみこむ、辞書は16文字*/
  while (fgets(dic, BUF, fp) != '\0')
  {
    //fgetsの改行対策
    if ((tp = strtok(dic, "\n")) == NULL)
    {
      printf("token error\n");
    }
    printf(""); //配列の後に必要

    // 結果に使う用の文字列
    char result[strlen(tp)];
    for (i = 0; i < strlen(tp); i++)
    {
      result[i] = dic[i];
    }
    result[i] = '\0';
    //辞書の文字を順番に並べる
    selectsort(dic);

    if (checkwords(dic, factor) == true)
    {
      printf("%s ", result);
      scoreword(dic);
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

  /*ここで１６文字のnull文字が消える*/
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
  cen[i] = '\0';
  return *cen;
}
/*入力した文字列と辞書との比較*/
bool checkwords(char *dicWord, char *checkWord)
{
  bool decision = true;
  char *d = dicWord;
  char *c = checkWord;
  int i = 0, j = 0;

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
        printf("check error\n");
      }
    }
  }
  return decision;
}
int scoreword(char *word)
{
  int score = 0;
  int i = 0;

  for (i = 0; i < strlen(word); i++)
  {
    if (word[i] == 'z')
    {
      score += 3;
    }
    else if (word[i] == 'y')
    {
      score += 2;
    }
    else
    {
      score += 1;
    }
  }
  printf("score: %d\n", score);
  return score;
}
