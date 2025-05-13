/******************
Name: Liam Homay
ID: 333087807
Assignment: ex4
*******************/

#include <stdio.h>
#include <string.h>

#define SIZE 5// size of the cheerleaders array
#define MAX 20// max size of the board

void task1robotPaths();
void task2humanPyramid();
void task3parenthesisValidator();
void task4queensBattle();

int robotPaths(int column, int row);// hepler for task1
float humanPyramid(float arr[][SIZE], int size, int row, int column);// helper for task2
char parenthesisValidator(char charToCheck);// helper for task3
int queensBattle(char board[][MAX], int n);// helper for task4

//functions for task3
int isOpen(char c);
int isClose(char c);
char getMatchingClose(char open);

//functions for task4
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
            scanf("%*s");// Clear invalid input from buffer
            printf("Please choose a task number from the list.\n");
        }
    } while (task != 5);
}

// Function to handle the robot paths task interface
void task1robotPaths() {
    int column, row;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &column, &row);
    printf("The total number of paths the robot can take to reach home is: %d\n", robotPaths(column, row));
}

// Recursive function to calculate number of possible paths to origin (0,0)
// Robot can only move left or down
int robotPaths(int column, int row) {
    // Base cases: if position is invalid or reached destination
    if (column < 0 || row < 0) return 0;  // Invalid position
    if (column == 0 && row == 0) return 1; // Reached destination
    // Recursive case: sum of paths from left and from down
    return robotPaths(column - 1, row) + robotPaths(column, row - 1);
}

// Function to handle the human pyramid weight calculation interface
void task2humanPyramid() {
    float arr[SIZE][SIZE];
    printf("Please enter the weights of the cheerleaders:\n");
    // Input weights for pyramid structure
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%f", &arr[i][j]);
            // Check for negative weights
            if (arr[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }

    // Calculate and display total weight on each person
    printf("\nThe total weight on each cheerleader is:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%.2f ", humanPyramid(arr, SIZE, i, j));
        }
        printf("\n");
    }
}

// Recursive function to calculate total weight on each person in pyramid
float humanPyramid(float arr[][SIZE], int size, int row, int column) {
    // Base case: invalid position
    if (column < 0 || row < 0 || column > row) return 0;

    // Calculate weight from person above-left and above-right (half of their total weight)
    float left = 0.5 * humanPyramid(arr, size, row - 1, column - 1);
    float right = 0.5 * humanPyramid(arr, size, row - 1, column);
    // Return own weight plus weight from above
    return arr[row][column] + left + right;
}

// Function to handle parenthesis validation interface
void task3parenthesisValidator() {
    printf("Please enter a term for validation:\n");
    char first;
    scanf(" %c", &first);
    // Check if parentheses are balanced
    if (parenthesisValidator(first) == '\n')
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");
}

// Recursive function to validate matching parentheses
char parenthesisValidator(char c) {
    // If current character is an opening bracket
    if (isOpen(c)) {
        char next;
        scanf("%c", &next);
        next = parenthesisValidator(next);
        if (next == '\0') return '\0';

        // Check if closing bracket matches
        if (next != getMatchingClose(c)) {
            if (next != '\n') {
                scanf("%*[^\n]");
                scanf("*%c");
            }
            return '\0';
        }
    }

    // If current character is a closing bracket
    if (isClose(c)) return c;

    // If reached end of input
    if (c == '\n' || c == '\0') return c;

    // Continue with next character
    char next;
    scanf("%c", &next);
    return parenthesisValidator(next);
}

// Helper function to check if character is an opening bracket
int isOpen(char c) {
    return c == '(' || c == '[' || c == '{' || c == '<';
}

// Helper function to check if character is a closing bracket
int isClose(char c) {
    return c == ')' || c == ']' || c == '}' || c == '>';
}

// Helper function to get matching closing bracket for an opening bracket
char getMatchingClose(char open) {
    switch (open) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        default: return '\0';
    }
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