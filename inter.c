#include <unistd.h>

int main(int argc, char **argv) {
  int list[255];
  int i;
  int j;

  i = 0;
  while (i < 255)
    list[i++] = 0;
  i = 2;
  if (argc == 3)
  {
    while (i > 0)
    {
      j = 0;
      while (argv[i][j])
      {
        if (i == 2 && !list[(int)argv[i][j]])
          list[(int)argv[i][j]] = 1;
        if (i == 1 && list[(int)argv[i][j]] == 1)
        {
          write(1, &argv[i][j], 1);
          list[(int)argv[i][j]]++;;
        }
        j++;
      }
      i--;
    }
  }
  write(1, "\n", 1);
}