#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
#define clear() printf("\033[H\033[J")

// Lets first implement a Stack
typedef struct node{
    struct node* next;
    char data;
}node;

typedef struct stack{
    node* head;
    int size;
}stack;

void printStk(stack* Stack);
stack* createStack();
int push(stack* Stack, int item);
int pop(stack* Stack);
int getPriority(char element);
int isOperator(char element);
int isAlpha(char element);
char* postfixConversion(char * equation);


int main(){
    char* equation = "A-(B+C)*A/D";
    postfixConversion(equation);
}



char* postfixConversion(char * equation){
    printf("%s\n", equation);

    stack* operatorStack = createStack();
    char result[100];
    int resIndex = 0;
    char* cursor = equation;
    while(*cursor != '\0'){
        printf("------\n");
        if (isAlpha(*cursor)){
            printf("Action: "YELLOW "Adding %c in result\n" RESET, *cursor);
            result[resIndex++] = *cursor;
        }
        else if (*cursor == '(') {
            printf("Action: " YELLOW "Adding ( in operator Stack\n" RESET);
            push(operatorStack, *cursor);
        }
        else if (*cursor == ')') {
            printf(RED "Encountered ), INITIATE POP\n" RESET);
            while (operatorStack->head != NULL && operatorStack->head->data != '(') {
                result[resIndex++] = pop(operatorStack);
            }
            pop(operatorStack); // Pop '(' from stack
        }
        else if (isOperator(*cursor)){
            while (operatorStack->head != NULL && 
                   getPriority(operatorStack->head->data) >= getPriority(*cursor)) {
                result[resIndex++] = pop(operatorStack);
            }
            printf("Action: " YELLOW "Adding %c in operator Stack\n" RESET, *cursor);
            push(operatorStack, *cursor);
        }
        printf(GREEN "Current Stack State: "RESET );
        printStk(operatorStack);
        printf(BLUE "Current Result State: "RESET );
        printf("%s", result);
        printf("\n");
        cursor++;
        printf("------\n");
        sleep(2);
        clear();
    }
    while (operatorStack->head != NULL) {
        result[resIndex++] = pop(operatorStack);

    }
    result[resIndex] = '\0'; // Null-terminate the result
    printf(GREEN "Postfix Expression: %s\n" RESET, result);
    return strdup(result); // Return a copy of the result
}
void printStk(stack* Stack){
    node* temp = Stack->head;
    while (temp != NULL){
        printf("%c, ", temp -> data);
        temp = temp -> next;
    }
    printf("NULL\n");
}

stack* createStack(){
    stack* newStack = (stack*)malloc(sizeof(stack));
    newStack -> size = 0;
    newStack -> head = NULL;
    return newStack;
}



int push(stack* Stack, int item){
    node* temp = (node*)malloc(sizeof(node));    
    temp -> data = item;
    temp -> next = Stack -> head;
    Stack -> head = temp;
    Stack -> size ++;
    return 0;
}

int pop(stack* Stack){
    int temp = Stack -> head -> data;
    Stack -> head = Stack -> head -> next;
    return temp;
}


int getPriority(char element){
    switch(element){
        case '+':
        case '-':
            return 1;
        case '/':
        case '*':
            return 2;
        case '^':
            return 3;
        default: 
            return 0;
    }
}


int isOperator(char element){
    switch(element){
        case '+':
        case '-':
        case '/':
        case '*':
        case '^':
            return 1;
        }
    return 0;
}

int isAlpha(char element){
    if ((element >= 65 && element <= 90) || (element >= 98 && element <= 123)){
            return 1;
        }
    return 0;
}
