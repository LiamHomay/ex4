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
int parenthesisValidator(char expectedClose);
int queensBattle(char board[][MAX], int n);

int isOpen(char c);
int isClose(char c);
char getMatchingClose(char open);

int queensBattle(char board[][MAX], int n);
int solve(int row, int n, char board[][MAX], char solution[][MAX], int cols[], int diag1[], int diag2[], int regions[]);
int isSafe(int row, int col, int n, int cols[], int diag1[], int diag2[], int regions[], char board[][MAX]);
int tryColumn(int row, int col, int n, char board[][MAX], char solution[][MAX],
              int cols[], int diag1[], int diag2[], int regions[]);


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
    printf("Please enter a term for validation:\n");

    // Clear input buffer
    scanf("%*[ \t\n]");
    // Start validation with no expected closing character
    int result = parenthesisValidator('\0');

    if (result)
        printf("The parentheses are balanced correctly.\n");
    else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

int isOpen(char c) {
    return c == '(' || c == '[' || c == '{' || c == '<';
}

int isClose(char c) {
    return c == ')' || c == ']' || c == '}' || c == '>';
}

char getMatchingClose(char open) {
    switch (open) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        default: return '\0';
    }
}

int parenthesisValidator(char expectedClose) {
    char c;
    scanf("%c", &c);

    if (c == '\n') {
        // End of input - valid only if we're not expecting any closing bracket
        return expectedClose == '\0';
    }

    // Skip non-bracket characters
    if (!isOpen(c) && !isClose(c)) {
        return parenthesisValidator(expectedClose);
    }

    if (isOpen(c)) {
        // Process opening bracket: validate what's inside it
        char matchingClose = getMatchingClose(c);
        if (!parenthesisValidator(matchingClose)) {
            return 0;
        }
        // After validating inside this bracket, continue with our original expectedClose
        return parenthesisValidator(expectedClose);
    }

    if (isClose(c)) {
        // Process closing bracket: must match what we're expecting
        return c == expectedClose;
    }

    return 1;  // Should never reach here
}









// פונקציית בדיקה אם מותר להציב מלכה (ללא אלכסונים משותפים)
int isSafe(int row, int col, int n,
           int cols[], int diag1[], int diag2[], int regions[], char board[][MAX]) {
    unsigned char regionChar = board[row][col];

    return !cols[col] && !diag1[row - col + n - 1] && !diag2[row + col] && !regions[regionChar];
}

// רקורסיה פנימית – ניסוי הצבת מלכה בכל עמודה בשורה row
int tryColumn(int row, int col, int n, char board[][MAX], char solution[][MAX],
              int cols[], int diag1[], int diag2[], int regions[]) {
    if (col == n)
        return 0;

    unsigned char regionChar = board[row][col];
    if (isSafe(row, col, n, cols, diag1, diag2, regions, board)) {
        // סמנו
        cols[col] = 1;
        diag1[row - col + n - 1] = 1;
        diag2[row + col] = 1;
        regions[regionChar] = 1;
        solution[row][col] = 'X';

        if (solve(row + 1, n, board, solution, cols, diag1, diag2, regions))
            return 1;

        // בטל
        cols[col] = 0;
        diag1[row - col + n - 1] = 0;
        diag2[row + col] = 0;
        regions[regionChar] = 0;
        solution[row][col] = '*';
    }

    // נסה בעמודה הבאה
    return tryColumn(row, col + 1, n, board, solution, cols, diag1, diag2, regions);
}

// פתרון ראשי – שורה אחר שורה
int solve(int row, int n, char board[][MAX], char solution[][MAX],
          int cols[], int diag1[], int diag2[], int regions[]) {
    if (row == n)
        return 1;

    return tryColumn(row, 0, n, board, solution, cols, diag1, diag2, regions);
}

int queensBattle(char board[][MAX], int n) {
    char solution[MAX][MAX];
    int cols[MAX] = {0};
    int diag1[2 * MAX] = {0};
    int diag2[2 * MAX] = {0};
    int regions[256] = {0}; // כל תו אפשרי

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            solution[i][j] = '*';


    if (solve(0, n, board, solution, cols, diag1, diag2, regions)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%c ", solution[i][j]);
            }
            printf("\n");
        }
        return 1;
    }
    else {
        printf("This puzzle cannot be solved.\n");
        return 0;
    }
}

void task4queensBattle() {
    char arr[MAX][MAX];
    int n;

    printf("Please enter the board dimensions:\n");
    scanf("%d", &n);

    printf("Please enter the %d*%d puzzle board:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf(" %c", &arr[i][j]);

    queensBattle(arr, n);
}




