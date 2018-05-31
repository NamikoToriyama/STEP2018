#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUF 20
char selectsort(char *);
bool checkwords(char *, char *);
int scoreword(char *);


int main(int argc, char *argv[])
{
  FILE *fp;
  char *filename = "dictionary.txt";
  char dic[BUF];
  char factor[BUF];
  char *tp;
  int i = 0, j = 0;
  int score, prescore = 0;
  char recommend[20];

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
      //頭文字が大文字のものを小文字にする
      if (dic[i] >= 65 && dic[i] <= 90)
      {
        dic[i] = dic[i] + 32;
      }
      result[i] = dic[i];
    }
    result[i] = '\0';
    //辞書の文字を順番に並べる
    selectsort(dic);

    if (checkwords(dic, factor) == true)
    {
      printf("%s ", result);
      //点数から一番点数の高いものを表示する
      prescore = scoreword(dic);
      if (prescore > score)
      {
        score = prescore;
        for (i = 0; i < strlen(result); i++)
        {
          recommend[i] = result[i];
        }
        recommend[i] = '\0';
      }
    };
  }
  printf("\nRECOMMEND WORD : %s\n", recommend);

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
  bool decision = false;
  char *d = dicWord;
  char *c = checkWord;
  int i = 0, j = 0;
  while ((i < strlen(d) - 1) || (j < strlen(c)))
  {
    if (d[i] == '\0') //文字が終わった時
    {
      decision = true;
      break;
    }
    else if (d[i] == c[j]) //文字が一致した時
    {
      i++;
      j++;
      if (strlen(d) == i)
      { //最後の文字が一致した時
        decision = true;
        break;
      }
    }
    else
    {
      if (j == strlen(c) - 1) //単語が終わった時
      {
        break;
      }
      if (d[i] != c[j]) //単語が一致しないとき
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

/*点数の計算をする関数*/
int scoreword(char *word)
{
  int score = 0;
  int point = 0;
  int i = 0;

  for (i = 0; i < strlen(word); i++)
  {
    if ((word[i] == 'j') || (word[i] == 'k') || (word[i] == 'q') || (word[i] == 'x') || (word[i] == 'z'))
    {
      score += 3;
    }
    else if ((word[i] == 'c') || (word[i] == 'f') || (word[i] == 'h') || (word[i] == 'l') || (word[i] == 'm') || (word[i] == 'p') || (word[i] == 'v') || (word[i] == 'w') || (word[i] == 'y'))
    {
      score += 2;
    }
    else
    {
      score += 1;
    }
  }
  point = score * score;
  return point;
}
