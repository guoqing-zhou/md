#include <stdio.h>
using namespace std;
int main(void) {
        int X = 1024 * 1024 - 1;
        FILE *fp = fopen("myfile", "w");
        fseek(fp, X , SEEK_SET);
        fputc('\0', fp);
        fclose(fp);
}
