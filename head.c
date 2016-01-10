#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);

int
main(int argcm char *argv[])
{
    if (argc != 2){
        fprintf(stderr, "Usage: %s n\n, argv[0]");
        exit(1);
    }
    do_head(stdin, atol(argv[1]));
    exit(0);
}

static void
// 第一引数は読み込むファイル 第二引数は表示する行
do_head(FILE *f, long nlines)
{
  int c;
  // nlinesが0になったら関数を中断
  if (nlines <= 0) return;
  while ((c = getc(f)) != EOF){
    if (putchar(c) < 0) exit(1);
    if (c == '\n') {
      nlines--;
      if (nlines == 0) return;
    }
  }
}
