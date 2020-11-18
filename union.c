#include <unistd.h>

int main(int argc, char **argv) {
  int list[255];
  int i;
  int j;

  i = 0;
  while (i < 255)
    list[i++] = 0;
  i = 1;
  if (argc == 3)
  {
    while (i < 3)
    {
      j = 0;
      while (argv[i][j])
      {
        if (!list[(int)argv[i][j]])
        {
          write(1, &argv[i][j], 1);
          list[(int)argv[i][j]] = 1;
        }
        j++;
      }
      i++;
    }
  }
  write(1, "\n", 1);
}