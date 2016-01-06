#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;

    // 引数が渡されているかのチェック
    if (argc < 2){
      fprintf(stderr, "%s: file name not given\n", argv[0]);
      exit(1);
    }
    // すべての引数について繰り返す
    for (i = 1; i < argc; i++){
      do_cat(argv[i]);
    }
    exit(0);
}

#define BUFFER_SIZE 2048

// ここで行われる
static void
do_cat(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;

    // openでファイルを開く O_RDONLYは読み込み専用
    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);
    //　無限ループ
    for(;;){
      // readで読み込み
      n = read(fd, buf, sizeof buf);
      if (n < 0) die(path);
      if (n == 0) break;
      // writeで書き込み
      if (write(STDOUT_FILENO, buf, n) < 0) die(path);
    }
    // ファイルを閉じる
    if (close(fd) < 0) die(path);
}

// エラー処理
static void
die(const char *s)
{
  perror(s);
  exit(1);
}
