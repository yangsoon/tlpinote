#include <stdio.h>
#include <string.h>
int main(int argc, char const* argv[])
{
  char s[20] = "0123456789";
  printf("%s\n", s);
  int len = strlen(s);
  printf("%c\n", s[10]);
  printf("%d\n", len);
	char d[10];
	strncpy(d, s, sizeof(d) -1);
	printf("%s\n", d);
}
