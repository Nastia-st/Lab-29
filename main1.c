#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *PF, *padres;
int main(void){
    system("chcp 65001");
    PF = fopen("d:\\my-lab1\\Lab-29\\var2.s", "r");
    padres = fopen("getrez.dan", "w");
    if (!PF)
        puts("File var2.s isn't open");
    else
        get();
    return 0;
}
void get(void)
{
    puts("get() викликана");
}