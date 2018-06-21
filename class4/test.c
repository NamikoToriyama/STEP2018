#include <stdio.h>
 
int main(void) {
	FILE *fp; // FILE型構造体
	char fname[] = "pagelank.txt";
 
	fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	} 

	fclose(fp); // ファイルを閉じる
 
	return 0;
}