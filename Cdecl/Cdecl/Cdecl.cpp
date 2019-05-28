// Cdecl.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum type_tag { IDENTIFIER, QUALIFIER, TYPE };


struct token
{
    char type;
    char string[MAXTOKENLEN];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token This;

#define pop stack[top--]
#define push(s) stack[++top] = s

/* 
    figure out the identifier type 
    推断标识符类型
*/
enum type_tag classify_string(void)
{
    char *s = This.string;
    if (!strcmp(s, "const"))
    {
        strcpy(s, "read-only");
        return QUALIFIER;
    }
    if (!strcmp(s, "volatile"))
        return QUALIFIER;
    if (!strcmp(s, "void"))
        return TYPE;
    if (!strcmp(s, "char"))
        return TYPE;
    if (!strcmp(s, "signed"))
        return TYPE;
    if (!strcmp(s, "unsigned"))
        return TYPE;
    if (!strcmp(s, "short"))
        return TYPE;
    if (!strcmp(s, "int"))
        return TYPE;
    if (!strcmp(s, "long"))
        return TYPE;
    if (!strcmp(s, "float"))
        return TYPE;
    if (!strcmp(s, "double"))
        return TYPE;
    if (!strcmp(s, "struct"))
        return TYPE;
    if (!strcmp(s, "union"))
        return TYPE;
    if (!strcmp(s, "enum"))
        return TYPE;
    return IDENTIFIER;
}

/* 
    read next token into "this" 
    读取下一个标记到 "this"
*/
void gettoken(void)
{
    char *p = This.string;

    /* read past any space 略过空白字符*/
    while ((*p = getchar()) == ' ');

    if (isalnum(*p))
    {
        /* it starts with A-Z, 0-9 read in identifier 读入的标识符以A-Z，0-9开头 */
        while (isalnum(*++p = getchar()));
        ungetc(*p, stdin);
        *p = '\0';
        This.type = classify_string();
        return;
    }

    if (*p == '*')
    {
        strcpy(This.string, "pointer to");
        This.type = '*';
        return;
    }
    This.string[1] = '\0';
    This.type = *p;
    return;
}

/* the piece of code that understandeth all parsing 理解所有分析过程的代码段 */
void read_to_first_identifier()
{
    gettoken();
    while (This.type != IDENTIFIER)
    {
        push(This);
        gettoken();
    }
    printf("%s is ", This.string);
    gettoken();
}

void deal_with_arrays()
{
    while (This.type == '[')
    {
        printf("array ");
        gettoken(); /* a number or ']' */
        if (isdigit(This.string[0]))
        {
            printf("0..%d ", atoi(This.string) - 1);
            gettoken(); /* read the ']' */
        }
        gettoken(); /* read next past the ']' */
        printf("of ");
    }
}

void deal_with_function_args()
{
    while (This.type != ')')
    {
        gettoken();
    }
    gettoken();
    printf("function returning ");
}

void deal_with_pointers()
{
    while (stack[top].type == '*')
    {
        printf("%s ", pop.string);
    }
}

void deal_with_declarator()
{
    /* deal with possible array/function following identifier */
    switch (This.type)
    {
    case '[': deal_with_arrays(); break;
    case '(': deal_with_function_args();
    }

    deal_with_pointers();

    /* process tokens that we stacked while reading identifier */
    while (top >= 0)
    {
        if (stack[top].type == '(')
        {
            pop;
            gettoken(); /* read past ')' */
            deal_with_declarator();
        }
        else
        {
            printf("%s ", pop.string);
        }
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
    /* put tokens on stack until we reach identifier */
    read_to_first_identifier();
    deal_with_declarator();
    printf("\n");
    system("pause");
    return 0;
}

