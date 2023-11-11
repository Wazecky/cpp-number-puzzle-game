#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

// Constants for the puzzle size
const int rows = 3;
const int cols = 3;

// Function to display the puzzle
void displayPuzzle(int puzzle[rows][cols]) {
    std::cout << "Puzzle:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (puzzle[i][j] == 0) {
                std::cout << "  ";
            } else {
                std::cout << puzzle[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

// Function to display rules and desired solution
void displayRulesAndSolution() {
    std::cout << "Number Puzzle Game Rules:" << std::endl;
    std::cout << "- Move the numbers to rearrange them in ascending order." << std::endl;
    std::cout << "- Enter the row and column of the number you want to move." << std::endl;
    std::cout << "- The empty cell is represented as '  '. Move numbers adjacent to it." << std::endl;
    std::cout << std::endl;
    std::cout << "Desired Solution:" << std::endl;
    std::cout << "1 2 3" << std::endl;
    std::cout << "4 5 6" << std::endl;
    std::cout << "7 8  " << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

// Function to check if the puzzle is solved
bool isPuzzleSolved(int puzzle[rows][cols]) {
    int count = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (puzzle[i][j] != count % (rows * cols)) {
                return false;
            }
            count++;
        }
    }
    return true;
}

// Function to check if the puzzle is solvable
bool isSolvable(int puzzle[rows][cols]) {
    // Flatten the puzzle into a 1D array
    int puzzleArray[rows * cols];
    int k = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            puzzleArray[k++] = puzzle[i][j];
        }
    }

    // Count the number of inversions
    int inversions = 0;
    for (int i = 0; i < rows * cols - 1; ++i) {
        for (int j = i + 1; j < rows * cols; ++j) {
            if (puzzleArray[i] > puzzleArray[j] && puzzleArray[i] != 0 && puzzleArray[j] != 0) {
                inversions++;
            }
        }
    }

    // Check if the puzzle is solvable based on the number of inversions
    if ((rows % 2 == 1 && inversions % 2 == 0) || (rows % 2 == 0 && ((rows - rows / 2) % 2 == 1) == (inversions % 2 == 0))) {
        return true;
    } else {
        return false;
    }
}

// Function to shuffle the puzzle (ensuring solvability)
void shufflePuzzle(int puzzle[rows][cols]) {
    srand(static_cast<unsigned int>(std::time(0)));

    // Perform a series of random swaps to shuffle the puzzle (ensuring solvability)
    do {
        // Initialize a solved puzzle
        int count = 1;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                puzzle[i][j] = count % (rows * cols);
                count++;
            }
        }
        puzzle[rows - 1][cols - 1] = 0;  // Set the last element to 0

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int randomRow = rand() % rows;
                int randomCol = rand() % cols;

                // Swap the current element with a randomly chosen element
                std::swap(puzzle[i][j], puzzle[randomRow][randomCol]);
            }
        }
    } while (!isSolvable(puzzle));
}

// Function to get the player's move
void getPlayerMove(int& moveRow, int& moveCol) {
    std::cout << "Enter move (row col): ";
    std::cin >> moveRow >> moveCol;
}

// Function to perform a move in the puzzle
void performMove(int puzzle[rows][cols], int moveRow, int moveCol) {
    int emptyRow, emptyCol;

    // Find the empty (0) cell
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (puzzle[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
            }
        }
    }

    // Check if the move is valid (adjacent to the empty cell)
    if ((std::abs(moveRow - emptyRow) == 1 && moveCol == emptyCol) ||
        (std::abs(moveCol - emptyCol) == 1 && moveRow == emptyRow)) {
        // Swap the selected cell with the empty cell
        std::swap(puzzle[moveRow][moveCol], puzzle[emptyRow][emptyCol]);
    } else {
        std::cout << "Invalid move! Try again." << std::endl;
    }
}

int main() {
    int puzzle[rows][cols];  // Initial puzzle configuration

    // Display rules and desired solution
    displayRulesAndSolution();

    // Shuffle the puzzle
    shufflePuzzle(puzzle);

    // Game loop
    while (!isPuzzleSolved(puzzle)) {
        // Display the current state of the puzzle
        displayPuzzle(puzzle);

        // Get and perform the player's move
        int moveRow, moveCol;
        getPlayerMove(moveRow, moveCol);

        // Perform the move
        performMove(puzzle, moveRow - 1, moveCol - 1);  // Adjust for 0-based indexing
    }

    // Puzzle is solved!
    displayPuzzle(puzzle);
    std::cout << "Congratulations! You solved the puzzle." << std::endl;

    return 0;
}
