/******************
Name: Liam Homay
ID: 333087807
Assignment: ex4
*******************/

#include <stdio.h>
#include <string.h>

#define SIZE 5
#define MAX 20

void task1robotPaths();
void task2humanPyramid();
void task3parenthesisValidator();
void task4queensBattle();

int robotPaths(int column, int row);
float humanPyramid(float arr[][SIZE], int size, int row, int column);
char parenthesisValidator(char charToCheck);
int queensBattle(char board[][MAX], int n);

char getMatchingClosing(char open);
int isOpening(char c);
int isClosing(char c);

int abs(int x);
int isSafe(int row, int col, int n, int queens[][2]);
int solve(int row, int n, char board[][MAX], char usedRegions[256], int queens[][2], int colUsed[MAX]);

int main() {
    int task = -1;
    do {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Exit\n");

        if (scanf("%d", &task)) {
            switch (task) {
                case 1:
                    task1robotPaths();
                    break;
                case 2:
                    task2humanPyramid();
                    break;
                case 3:
                    task3parenthesisValidator();
                    break;
                case 4:
                    task4queensBattle();
                    break;
                case 5:
                    printf("Goodbye!\n");
                    break;
                default:
                    printf("Please choose a task number from the list.\n");
                    break;
            }
        } else {
            scanf("%*s");
            printf("Please choose a task number from the list.\n");
        }
    } while (task != 5);
}

void task1robotPaths() {
    int column, row;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &column, &row);

    printf("The total number of paths the robot can take to reach home is: %d\n", robotPaths(column, row));
}

int robotPaths(int column, int row) {
    if (column < 0 || row < 0) return 0;
    if (column == 0 && row == 0) return 1;
    return robotPaths(column - 1, row) + robotPaths(column, row - 1);
}

void task2humanPyramid() {
    float arr[SIZE][SIZE];
    printf("Please enter the weights of the cheerleaders:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%f", &arr[i][j]);
            if (arr[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }

    printf("\nThe total weight on each cheerleader is:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%.2f ", humanPyramid(arr, SIZE, i, j));
        }
        printf("\n");
    }
}

float humanPyramid(float arr[][SIZE], int size, int row, int column) {
    if (column < 0 || row < 0 || column > row) return 0;

    float left = 0.5 * humanPyramid(arr, size, row - 1, column - 1);
    float right = 0.5 * humanPyramid(arr, size, row - 1, column);
    return arr[row][column] + left + right;
}

void task3parenthesisValidator() {
    char first;
    printf("Please enter a term for validation:\n");
    scanf(" %c", &first);
    char isBalanced = parenthesisValidator(first);
    if (isBalanced == '\0')
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");
    while (getchar() != '\n');
}

char parenthesisValidator(char charToCheck) {
    if (charToCheck == '(' || charToCheck == '{' || charToCheck == '[' || charToCheck == '<') {
        char nextCharToCheck;
        scanf(" %c", &nextCharToCheck);
        nextCharToCheck = parenthesisValidator(nextCharToCheck);
        if (nextCharToCheck == '\0') {
            return '\0';
        }

        if (charToCheck == '(' && nextCharToCheck != ')'
         || charToCheck == '{' && nextCharToCheck != '}'
         || charToCheck == '[' && nextCharToCheck != ']'
         || charToCheck == '<' && nextCharToCheck != '>') {
            if (nextCharToCheck != '\n' && nextCharToCheck != '\0') {
                scanf("%*[^\n]");
                scanf("%*c");
            }
            return '\0';
        }
    }

    if (charToCheck == ')' || charToCheck == '}' || charToCheck == ']' || charToCheck == '>') {
        return charToCheck;
    }

    if (charToCheck == '\n' || charToCheck == '\0') {
        return charToCheck;
    }

    char nextCharToCheck;
    scanf(" %c", &nextCharToCheck);
    return parenthesisValidator(nextCharToCheck);
}

char getMatchingClosing(char open) {
    if (open == '(') return ')';
    if (open == '[') return ']';
    if (open == '{') return '}';
    if (open == '<') return '>';
    return 0;
}

int isOpening(char c) {
    return c == '(' || c == '[' || c == '{' || c == '<';
}

int isClosing(char c) {
    return c == ')' || c == ']' || c == '}' || c == '>';
}

void task4queensBattle() {
    char arr[MAX][MAX] = {0};
    int n;

    printf("Please enter the board dimensions:\n");
    scanf("%d", &n);

    printf("Please enter the %d*%d puzzle board:\n", n, n);

    char ch;
    int i = 0, j = 0;

    while (i < n) {
        scanf(" %c", &ch);
        arr[i][j++] = ch;
        if (j == n) {
            i++;
            j = 0;
        }
    }

    if (!queensBattle(arr, n))
        printf("This puzzle cannot be solved.\n");
}

int queensBattle(char board[][MAX], int n) {
    int queens[MAX][2];
    int colUsed[MAX] = {0};
    char usedRegions[256] = {0};

    if (solve(0, n, board, usedRegions, queens, colUsed)) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                board[i][j] = '*';

        for (int i = 0; i < n; i++) {
            int row = queens[i][0];
            int col = queens[i][1];
            board[row][col] = 'X';
        }

        printf("Solution:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }
        return 1;
    }
    return 0;
}

int abs(int x) {
    return (x < 0) ? -x : x;
}

int isSafe(int row, int col, int n, int queens[][2]) {
    for (int i = 0; i < row; i++) {
        int qRow = queens[i][0];
        int qCol = queens[i][1];
        if (qCol == col || qRow - qCol == row - col || qRow + qCol == row + col)
            return 0;

        if (abs(qRow - row) <= 1 && abs(qCol - col) <= 1)
            return 0;
    }
    return 1;
}

int solve(int row, int n, char board[][MAX], char usedRegions[256], int queens[][2], int colUsed[MAX]) {
    if (row == n)
        return 1;

    for (int col = 0; col < n; col++) {
        char region = board[row][col];
        if (!colUsed[col] && !usedRegions[(unsigned char)region] && isSafe(row, col, n, queens)) {
            queens[row][0] = row;
            queens[row][1] = col;
            colUsed[col] = 1;
            usedRegions[(unsigned char)region] = 1;

            if (solve(row + 1, n, board, usedRegions, queens, colUsed))
                return 1;

            colUsed[col] = 0;
            usedRegions[(unsigned char)region] = 0;
        }
    }
    return 0;
}
