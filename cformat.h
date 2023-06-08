#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

int check_brackets(char *c)
{
    Stack_t *st = createStack();
    char a;
    char ch;
    push(st, '1');
    int len_text = strlen(c);
    for (int i = 0; i < len_text; i++)
    {
	ch = c[i];
	a = peek(st);
        if(ch == '{')
        {
	    push(st, '{');
        }
        if(ch == '(')
        {
            push(st, '(');
        }
        if(ch == '[')
        {
            push(st, '[');

        }
        if((ch == '}') && (a != '{')) {

	    return 0;
	    break;
        }
	else if ((ch == '}') && (a == '{')) {

	    pop(st);
	}
        if((ch == ')') && (a != '(')) {

            return 0;
            break;
	}
        else if ((ch == ')') && (a == '(')) {

            pop(st);
        }
        if((ch == ']') && (a != '[')) {
            return 0;
            break;
	}
        else if ((ch == ']') && (a == '[')) {
            pop(st);
        }
    }
    if (a != '1')
    {
	return 0;
    }
    else
    {
	return 1;
    }
}




void strcut(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

int checkToOneWord(char *text, char *word)
{
    return isalpha(*(strstr(text, word) - 1)) != 1 && isalpha(*(strstr(text, word) + strlen(word))) != 1;
}

void cutFromAndTo(char *text, int from, int to)
{
    // char result[strlen(*text) + 1];
    int index = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        if (!(i >= from && i < to))
        {
            text[index++] = text[i];
        }
    }
    // strcpy(*text, result);
}

char *formatFigureBrackets(char *text)
{
    int len_text = strlen(text);
    char *result = (char *)malloc(sizeof(char) * len_text * 3);
    strcpy(result, text);
    // strcut(text, '\t');
    char *find = (char *)malloc(sizeof(char) * len_text * 3);
    for (int i = 0; i < strlen(result); i++)
    {
        if (result[i] == '{')
        {
            // Вырезаем все пустые поля около скобочки
            int indexOperator = i - 1;
            while (isspace(result[indexOperator--]))
                ;
            cutFromAndTo(result, indexOperator + 2, i);
            while (result[i] != '{')
                i--;

            // Проверяем есть ли перед нами операторы
            indexOperator = i;
            strcpy(find, result);
            find[indexOperator] = 0;
            while (find[indexOperator] != '\n')
                indexOperator--;
            if (strstr(&find[indexOperator], "for") != NULL || strstr(&find[indexOperator], "if") != NULL || strstr(&find[indexOperator], "while") != NULL)
            {
            }
            else
            {
                strcpy(find, result);
                result[i] = '\n';
                result[i + 1] = 0;
                strcat(result, &find[i]);
                i++;
            }
            if (result[i + 1] != '\n')
            {
                strcpy(find, result);
                result[i + 1] = '\n';
                result[i + 2] = 0;
                strcat(result, &find[i + 1]);
            }
        }
	if (result[i] == '}')
	{
            int indexOperator = i - 1;
            while (isspace(result[indexOperator--]))
                ;
            cutFromAndTo(result, indexOperator + 2, i);
            while (result[i] != '}')
                i--;

            // Проверяем есть ли перед нами операторы
            indexOperator = i;
            strcpy(find, result);
            find[indexOperator] = 0;
            while (find[indexOperator] != '\n')
                indexOperator--;
	    if (result[i-1] != '\n')
	    {
                strcpy(find, result);
                result[i] = '\n';
                result[i + 1] = 0;
                strcat(result, &find[i]);
                i++;
	    }
            if (result[i + 1] != '\n')
            {
                strcpy(find, result);
                result[i + 1] = '\n';
                result[i + 2] = 0;
                strcat(result, &find[i + 1]);
            }
	}
        if (result[i] == ';')
        {
            int indexOperator = i - 1;
            while (isspace(result[indexOperator--]))
                ;
            cutFromAndTo(result, indexOperator + 2, i);
            while (result[i] != ';')
                i--;

            // Проверяем есть ли перед нами операторы
            indexOperator = i;
            strcpy(find, result);
            find[indexOperator] = 0;
            while (find[indexOperator] != '\n')
                indexOperator--;
            if (result[i + 1] != '\n')
            {
                strcpy(find, result);
                result[i + 1] = '\n';
                result[i + 2] = 0;
                strcat(result, &find[i + 1]);
            }
	}
    }
    // Убераем всё что может быть в начале новой строки
    for (int i = 0; i < strlen(result); i++)
    {
        if (result[i] == '\n')
        {
            int indexSpace = i;
            while (isspace(result[indexSpace]))
                indexSpace++;
            cutFromAndTo(result, i + 1, indexSpace);
        }
    }
    // Расставляем табы
    int countBrackets = 0;
    for (int i = 0; i < strlen(result); i++)
    {
        if (result[i] == '{')
            countBrackets++;
        else if (result[i + 1] == '}')
            countBrackets--;
        if (result[i] == '\n')
        {
            for (int j = 0; j < countBrackets; j++)
            {
                strcpy(find, result);
                result[i + 1] = '\t';
                result[i + 2] = 0;
                strcat(result, &find[i + 1]);
                i += 1;
            }
        }
    }
    int literFirst = -1;
    int literLast = -1;
    int countChar = 0;
    for (int i = 0; i < strlen(result); i++)
    {
	if ((result[i] != '=') && (literFirst < 0)){
	    if (result[i] == '\t'){
		literFirst -= 8;
	    }
	    else{
		literFirst--;
	    }
	}
	if ((result[i] == '=') && (literFirst < 0)){
	    literFirst *= -1;
	}
        if (result[i] == '+' || result[i] == '-' || result[i] == '/' || result[i] == '*' || result[i] == '%' || result[i] == '>' || result[i] == '<' || result[i] == '|' || result[i] == '&'){
            literLast = i;
        }
	countChar++;
        if ((countChar > 80) && (literLast != -1)){
            if (literLast < 80){
                int indexSpace = literLast + 1;
                while (isspace(result[indexSpace]))
                    indexSpace++;
                cutFromAndTo(result, literLast + 1, indexSpace);
		strcpy(find, result);
                result[literLast + 1] = '\n';
                result[literLast + 2] = 0;
                strcat(result, &find[literLast + 1]);
                i = literLast + 2;
		for (int j = 0; j < literFirst; j++)
                {
                    strcpy(find, result);
                    result[i + 1] = ' ';
                    result[i + 2] = 0;
                    strcat(result, &find[i + 1]);
                    i += 1;
                }
	    }
            else{
                int indexSpace = literLast - 1;
                while (isspace(result[indexSpace]))
                    indexSpace--;
                cutFromAndTo(result, indexSpace + 1, literLast);
                strcpy(find, result);
                result[indexSpace + 1] = '\n';
                result[indexSpace + 2] = 0;
                strcat(result, &find[indexSpace + 1]);
                i = indexSpace + 2;
                for (int j = 0; j < literFirst; j++)
                {
                    strcpy(find, result);
                    result[i] = ' ';
                    result[i + 1] = 0;
                    strcat(result, &find[i]);
                    i += 1;
                }
            }
	    literLast = -1;
	}
	if (result[i] == '\n'){
	    literFirst = -1;
	    literLast = -1;
	    countChar = 0;
	}
    }
    free(find);
    char *res = (char *)malloc(sizeof(char) * strlen(result) + 2);
    strcpy(res, result);
    return res;
}
