#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int main() {
    char expr[MAX];       // input expression
    char postfix[MAX];    // postfix version
    char opArr[MAX];      // array for operators
    int opTop = -1;       // operator index
    char tac[MAX][10];    // array for operands in TAC
    int sTop = -1;        // operand index
    int temp = 1;         // temporary variable counter

    printf("Enter expression (like (a+b)*c): ");
    scanf("%s", expr);

    // Helper: operator precedence
    int prec(char c) {
        if (c == '*' || c == '/') return 2;
        if (c == '+' || c == '-') return 1;
        return 0;
    }

    // Convert infix to postfix (simple version)
    int k = 0;
    for (int i = 0; expr[i]; i++) {
        char c = expr[i];
        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            opArr[++opTop] = c;
        } else if (c == ')') {
            while (opTop >= 0 && opArr[opTop] != '(')
                postfix[k++] = opArr[opTop--];
            opTop--; // remove '('
        } else { // operator
            while (opTop >= 0 && prec(opArr[opTop]) >= prec(c))
                postfix[k++] = opArr[opTop--];
            opArr[++opTop] = c;
        }
    }
    while (opTop >= 0)
        postfix[k++] = opArr[opTop--];
    postfix[k] = '\0';

    printf("Postfix: %s\n\n", postfix);

    // Generate 3-address code (simplest array version)
    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            char tempStr[2] = {c, '\0'};
            strcpy(tac[++sTop], tempStr);
        } else { // operator
            char op2[10], op1[10], res[10];
            strcpy(op2, tac[sTop--]);
            strcpy(op1, tac[sTop--]);
            sprintf(res, "t%d", temp++);
            printf("%s = %s %c %s\n", res, op1, c, op2);
            strcpy(tac[++sTop], res);
        }
    }

    printf("result = %s\n", tac[sTop]);

    return 0;
}
