#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum {
    BEGINL = 257, ENDL, IFL, THENL, WHILEL, DOL, RETRL,
    READL, PRINTL, INTL, CONSTL, IDEN, NUMB
};
int nst = 0;
int lval, lex;
static char nch = '\n';
FILE *PF, *padres;
void get(void);
void number(void);
void word(void);
char* add(char *nm);
char TNM[400];
char *ptn = TNM;
int main(void) {
    system("chcp 65001");
    PF = fopen("d:\\my-lab1\\Lab-29\\var2.s", "r");
    padres = fopen("getrez.dan", "w");
    if (!PF) {
        puts("Не вдалося відкрити файл var2.s");
        return 1;
    }
    get();
    fclose(PF);
    fclose(padres);
    return 0;
}
void get() {
    nch = getc(PF);
    while (nch != EOF) {
        while (isspace(nch)) {
            if (nch == '\n') nst++;
            nch = getc(PF);
        }
        if (isdigit(nch)) {
            number();
        } else if (isalpha(nch)) {
            word();
        } else if (nch == '{') {
            lex = BEGINL;
            printf("Початок блоку: {\n");
            fprintf(padres, "Початок блоку: {\n");
            nch = getc(PF);
        } else if (nch == '}') {
            lex = ENDL;
            printf("Кінець блоку: }\n");
            fprintf(padres, "Кінець блоку: }\n");
            nch = getc(PF);
        } else if (nch == '(' || nch == ')' || nch == ',' || nch == ';' || nch == '=' ||
                   nch == '+' || nch == '-' || nch == '*' || nch == '/' || nch == '%') {
            lex = nch;
            printf("Символ: %c\n", nch);
            fprintf(padres, "Символ: %c\n", nch);
            nch = getc(PF);
        } else {
            printf("Недопустимий символ: %c\n", nch);
            fprintf(padres, "Недопустимий символ: %c\n", nch);
            nch = getc(PF);
        }
    }
    lex = EOF;
}
void number() {
    lval = 0;
    while (isdigit(nch)) {
        lval = lval * 10 + nch - '0';
        nch = getc(PF);
    }
    lex = NUMB;
    printf("Число: %d\n", lval);
    fprintf(padres, "Число: %d\n", lval);
}
void word() {
    static int cdl[] = {IFL, THENL, WHILEL, DOL, RETRL, READL, PRINTL, INTL, CONSTL};
    static char *serv[] = {
        "if", "then", "while", "do", "return", "read", "print", "int", "const"
    };
    char tx[40], *p = tx;
    while (isalpha(nch) || isdigit(nch)) {
        *p++ = nch;
        nch = getc(PF);
    }
    *p = '\0';
    for (int i = 0; i < 9; i++) {
        if (strcmp(tx, serv[i]) == 0) {
            lex = cdl[i];
            printf("Ключове слово: %s\n", tx);
            fprintf(padres, "Ключове слово: %s\n", tx);
            return;
        }
    }
    lex = IDEN;
    lval = (int)add(tx);
    printf("Ідентифікатор: %s, адреса = %p\n", tx, (void *)lval);
    fprintf(padres, "Ідентифікатор: %s, адреса = %p\n", tx, (void *)lval);
}
char* add(char *nm) {
    char *p;
    for (p = TNM; p < ptn; p += strlen(p) + 1) {
        if (strcmp(p, nm) == 0)
            return p;
    }
    if ((ptn + strlen(nm) + 1) > TNM + sizeof(TNM)) {
        puts("Переповнення таблиці ідентифікаторів");
        exit(1);
    }
    strcpy(ptn, nm);
    p = ptn;
    ptn += strlen(nm) + 1;
    return p;
}