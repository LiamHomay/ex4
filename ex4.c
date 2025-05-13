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
int solve(int row, int n, char board[][MAX], char solution[][MAX], int usedCols[], int usedRegions[256]);
int isSafe(int x, int y, char solution[][MAX], int n);
int tryCols(int row, int col, int n, char board[][MAX], char solution[][MAX], int usedCols[], int usedRegions[256]);



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
    float left =  0.5 * humanPyramid(arr, size, row - 1, column - 1);
    float right =  0.5 * humanPyramid(arr, size, row - 1, column);
    // Return own weight plus weight from above
    return arr[row][column] + left + right + 0.00001;//for making 2.4999999 round to 3
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
                scanf("%*c");
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


void task4queensBattle() {
    char arr[MAX][MAX];
    int n;

    printf("Please enter the board dimensions:\n");
    scanf("%d", &n);

    printf("Please enter a %d*%d puzzle board:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf(" %c", &arr[i][j]);

    queensBattle(arr, n);
}

// Attempts to solve the Queens Battle puzzle.
// If a valid configuration is found, it prints the solution and returns 1.
// Otherwise, it prints that the puzzle is unsolvable and returns 0.
int queensBattle(char board[][MAX], int n) {
    char solution[MAX][MAX];
    int usedCols[MAX] = {0};         // Tracks which columns already have a queen
    int usedRegions[256] = {0};      // Tracks which regions are already occupied by a queen

    // Initialize the solution board with '*'
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            solution[i][j] = '*';

    // Start solving from the first row
    if (solve(0, n, board, solution, usedCols, usedRegions)) {
        printf("Solution:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%c ", solution[i][j]);
            printf("\n");
        }
        return 1;
    }
    else {
        printf("This puzzle cannot be solved.\n");
        return 0;
    }
}

// Recursive function that attempts to place a queen in each row
int solve(int row, int n, char board[][MAX], char solution[][MAX], int usedCols[], int usedRegions[256]) {
    if (row == n)
        return 1; // All queens placed successfully

    return tryCols(row, 0, n, board, solution, usedCols, usedRegions);
}

// Recursive helper that tries to place a queen in each column of a given row
int tryCols(int row, int col, int n, char board[][MAX], char solution[][MAX], int usedCols[], int usedRegions[256]) {
    if (col == n)
        return 0; // Tried all columns in this row with no success

    char region = board[row][col];

    // Check if the column and region are free, and the placement is safe
    if (!usedCols[col] && !usedRegions[(int)region] && isSafe(row, col, solution, n)) {
        // Place the queen
        solution[row][col] = 'X';
        usedCols[col] = 1;
        usedRegions[(int)region] = 1;

        // Recursively try to place the next queen
        if (solve(row + 1, n, board, solution, usedCols, usedRegions))
            return 1;

        // Backtrack if the solution didn't work
        solution[row][col] = '*';
        usedCols[col] = 0;
        usedRegions[(int)region] = 0;
    }

    // Try the next column in the row
    return tryCols(row, col + 1, n, board, solution, usedCols, usedRegions);
}

// Checks whether placing a queen at (x, y) is safe
// Ensures no queen is adjacent to this cell (including diagonals)
int isSafe(int x, int y, char solution[][MAX], int n) {
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0, a8 = 0;

    if (x + 1 < n)
        a1 = solution[x + 1][y] == 'X';
    if (x - 1 >= 0)
        a2 = solution[x - 1][y] == 'X';
    if (y + 1 < n)
        a3 = solution[x][y + 1] == 'X';
    if (y - 1 >= 0)
        a4 = solution[x][y - 1] == 'X';
    if (x + 1 < n && y + 1 < n)
        a5 = solution[x + 1][y + 1] == 'X';
    if (x + 1 < n && y - 1 >= 0)
        a6 = solution[x + 1][y - 1] == 'X';
    if (x - 1 >= 0 && y + 1 < n)
        a7 = solution[x - 1][y + 1] == 'X';
    if (x - 1 >= 0 && y - 1 >= 0)
        a8 = solution[x - 1][y - 1] == 'X';

    // Return true if all adjacent cells are safe (no queens around)
    return !(a1 || a2 || a3 || a4 || a5 || a6 || a7 || a8);
}













