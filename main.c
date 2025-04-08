#include "./Data-Structures/Dynamic-Stack/dynamic-stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int precendence(char c)
{
    if (c == '^')
    {
        return 2;
    }
    else if (c == '*' || c == '/')
    {
        return 1;
    }
    else if (c == '+' || c == '-')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int isOperand(char c)
{
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           ('0' <= c && c <= '9');
}

int isOperator(char c)
{
    return (c == '+') ||
           (c == '-') ||
           (c == '*') ||
           (c == '/') ||
           (c == '^');
}

void postfixToInfix(char * expression, char * infix)
{
    int infix_i = 0;

    DynamicStack stack = createDynamicStack();

    int i = 0;

    while (expression[i] != '\0')
    {
        // Add operando to the result.
        if (isOperand(expression[i]))
        {
            infix[infix_i++] = expression[i];
        }
        else if (expression[i] == '(')
        {
            push(expression[i], &stack);
        }
        else if (expression[i] == ')')
        {
            char last_operator = pop(&stack);

            /*
                POP from the stack until another
                '(' and what it gets to the infix.
            */
            while (last_operator != '(')
            {
                infix[infix_i++] = last_operator;
                last_operator = pop(&stack);
            }
        }
        else if (isOperator(expression[i]))
        {
            /*
                If the precendence of the operator is smaller
                than of the top of the stack, we pop from the stack
                and add it to the infix.
            */
            while(!isStackEmpty(&stack) &&
                  (precendence(expression[i]) < precendence((stack.top)->value) ||
                   precendence(expression[i]) == precendence((stack.top)->value))
                 )
            {
                infix[infix_i++] = pop(&stack);
            }

            // We add the operator to the stack.
            push(expression[i], &stack);
        }
        else
        {
            printf("Char \"%c\" is not valid!\n", expression[i]);
        }

        i++;
    }

    // Pop the remaining elements.
    while(!isStackEmpty(&stack))
    {
        infix[infix_i++] = pop(&stack);
    }

    infix[infix_i] = '\0';

    cleanStack(&stack);
}

int main()
{
    char expression[100];

    printf("Write an infix expression: ");

    scanf("%s", &expression);

    char infix[strlen(expression)];

    postfixToInfix(&expression, &infix);

    printf("Postfix expression: %s", infix);

    return 0;
}
