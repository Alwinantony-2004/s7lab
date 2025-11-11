#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[100];
    char arr[100]; // stack as array
    int top = -1, i = 0;

    printf("Enter expression (use i for identifier): ");
    scanf("%s", input);

    while (input[i] != '\0') {
        // Shift
        arr[++top] = input[i];
        printf("Shift: %c\n", input[i]);
        i++;

        // Reduce loop
        int reduced;
        do {
            reduced = 0;

            // i -> E
            if (top >= 0 && arr[top] == 'i') {
                arr[top] = 'E';
                printf("Reduce:   E -> i");
                reduced = 1;
            }
            // (E) -> E
            else if (top >= 2 && arr[top-2] == '(' && arr[top-1] == 'E' && arr[top] == ')') {
                arr[top-2] = 'E';
                top -= 2;
                printf("Reduce:   E -> (E)  ");
                reduced = 1;
            }
            // E op E -> E
            else if (top >= 2 && arr[top-2] == 'E' &&
                     (arr[top-1] == '+' || arr[top-1] == '-' || arr[top-1] == '*') &&
                     arr[top] == 'E') {
                char op = arr[top-1];
                arr[top-2] = 'E';
                top -= 2;
                printf("\nReduce:    E -> E%cE   ", op);
                reduced = 1;
            }

        } while (reduced);

        // Print stack
        printf("   Stack: ");
        for (int j = 0; j <= top; j++)
            printf("%c", arr[j]);
        printf("\n");
    }

    // Final check
    if (top == 0 && arr[top] == 'E')
        printf("\n✅ Successfully parsed!\n");
    else
        printf("\n❌ Syntax Error.\n");

    return 0;
}
