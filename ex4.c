/******************
Name: Liam Homay
ID: 333087807
Assignment: ex4
*******************/

#include <stdio.h>
#include <string.h>

#define SIZE 5
#define MAX 20

void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();

int RobotPaths(int column, int row);
float HumanPyramid(float arr[][SIZE], int size, int row, int column);
int ParenthesisValidator(char c);
int QueensBattle(char board[][MAX], int n);

char getMatchingClosing(char open);
int isOpening(char c) ;
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

        if (scanf("%d", &task)) { // To make sure the input is an integer
            switch (task) {
                case 1:
                    task1RobotPaths();
                    break;
                case 2:
                    task2HumanPyramid();
                    break;
                case 3:
                    task3ParenthesisValidator();
                    break;
                case 4:
                    task4QueensBattle();
                    break;
                case 5:
                    printf("Goodbye!\n");
                    break;
                default:
                    printf("Please choose a task number from the list.\n");
                    break;
            }
        } else {
            scanf("%*s"); // To discard the invalid input
            printf("Please choose a task number from the list.\n");
        }
    } while (task != 5);
}

void task1RobotPaths() {
    int column, row;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &column, &row);

    printf("The total number of paths the robot can take to reach home is: %d\n", RobotPaths(column, row));
}

int RobotPaths(int column, int row) {
    if (column < 0 || row < 0) return 0;
    if (column == 0 && row == 0) return 1;
    return RobotPaths(column - 1, row) + RobotPaths(column, row - 1);
}


void task2HumanPyramid() {
    float arr[SIZE][SIZE];
    printf("Please enter the weights of the cheerleaders:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%f", &arr[i][j]);
            if (arr[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;//Back to the menu
            }
        }
    }

    printf("\nThe total weight on each cheerleader is:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%.2f", HumanPyramid(arr, SIZE, i, j));
            printf(" ");
        }
        printf("\n");
    }
}

float HumanPyramid(float arr[][SIZE], int size, int row, int column) {
    if (column < 0 || row < 0 || column > row) return 0;

    float left = 0.5 * HumanPyramid(arr, size, row - 1, column - 1);
    float right = 0.5 * HumanPyramid(arr, size, row - 1, column);
    return arr[row][column] + left + right;
}


void task3ParenthesisValidator() {
    char first;
    printf("Please enter a term for validation:\n");
    scanf(" %c", &first);
    if (ParenthesisValidator(first))
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");

}

int ParenthesisValidator(char c) {

    while (!isOpening(c) && !isClosing(c) && c != '\n') {
        scanf(" %c", &c);
    }

    if (c == '\n') return 1;

    if (isClosing(c)) return 0;

    char expectedClose = getMatchingClosing(c);
    char next;
    scanf(" %c", &next);

    if (!ParenthesisValidator(next))
        return 0;

    scanf(" %c", &next);
    if (next != expectedClose)
        return 0;

    return ParenthesisValidator(next);
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



void task4QueensBattle() {
    char arr[MAX][MAX] = {0};
    int n;

    printf("Please enter the board dimensions:\n");
    scanf("%d", &n);

    printf("Please enter the %d*%d puzzle board:\n", n, n);

    char ch;
    int i = 0, j = 0;

    while (i < n) {
        scanf(" %c", &ch);
        arr[i][j] = ch;
        j++;
        if (j == n) {
            i++;
            j = 0;
        }
    }

    if (!QueensBattle(arr, n))
        printf("This puzzle cannot be solved.\n");
}

int QueensBattle(char board[][MAX], int n) {
    int queens[MAX][2]; // שורה ועמודה לכל מלכה
    int colUsed[MAX] = {0};
    char usedRegions[256] = {0};

    if (solve(0, n, board, usedRegions, queens, colUsed)) {
        // מלא את הלוח ב־'*'
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                board[i][j] = '*';

        // מקם את המלכות
        for (int i = 0; i < n; i++) {
            int row = queens[i][0];
            int col = queens[i][1];
            board[row][col] = 'X';
        }

        // הדפסה
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

        // צמודים במרחק 1
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

            // חזרה לאחור
            colUsed[col] = 0;
            usedRegions[(unsigned char)region] = 0;
        }
    }
    return 0;
}





