#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

//int GetNeighbouringMineCount(int x, int y, int width, int height, Cell** minefield);

enum Cell {
    EMPTY = 0,
    M1 = 1,
    M2 = 2,
    M3 = 3,
    M4 = 4,
    M5 = 5,
    M6 = 6,
    M7 = 7,
    M8 = 8,
    M9 = 9,
    MINE = 10,
};

/// <summary>
/// Find out how many mines surround any given cell.
/// </summary>
/// <param name="x">X Position of the cell.</param>
/// <param name="y">Y Position of the cell.</param>
/// <param name="width">Width of the minefield.</param>
/// <param name="height">Height of the minefield.</param>
/// <param name="minefield">The current minefield.</param>
/// <returns>The total surrounding mines.</returns>
/// 
int GetNeighbouringMineCount(int x, int y, int width, int height, Cell** minefield) {

    // Difference in coordinates for all neighbouring cells
    const int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    const int dy[] = { 1, 0, -1, 1, -1, 1, 0, -1 };

    int totalMines = 0;

    // At any empty cells, check how many mines there are adjacent
    if (minefield[x][y] != MINE) {
        for (int i = 0; i < 8; i++) {

            // Get the coords of the neighbour
            int neighbourX = x + dx[i];
            int neighbourY = y + dy[i];

            // Make sure we're not out of bounds
            bool inBounds =
                neighbourX >= 0 && neighbourX < width&&
                neighbourY >= 0 && neighbourY < height;

            if (inBounds && minefield[neighbourX][neighbourY] == MINE) {
                totalMines++;
            }
        }

        return totalMines;
    }
    else {
        return (int)MINE;
    }

}

/// <summary>
/// Create and populate the minefield.
/// </summary>
/// <param name="width">Width of the minefield.</param>
/// <param name="height">Height of the minefield.</param>
/// <param name="count">Number of mines to add to the field.</param>
/// <param name="minefield">The current minefield.</param>
/// 
void GenerateMineField(unsigned int width, unsigned int height, unsigned int count, Cell**& minefield) {

    // Seed the random number generator using timestamp
    srand((unsigned)time(NULL));

    int totalMines = 0;

    // Randomly place the mines throughout the field
    while (totalMines < count) {
        int mineX = rand() % width;
        int mineY = rand() % height;

        // Increment the count on successful placement
        if (minefield[mineX][mineY] != MINE) {
            minefield[mineX][mineY] = MINE;
            totalMines++;
        }
    }  

    // Populate the minefield
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {

            // Mark the cell indicating the number of surrounding mines.
            minefield[i][j] = (Cell)GetNeighbouringMineCount(i, j, width, height, minefield);
        }
    }

    
}

/// <summary>
/// Print the generated minefield to the console
/// </summary>
/// <param name="width">Width of the field.</param>
/// <param name="height">Height of the field.</param>
/// <param name="minefield">The actual minefield.</param>
/// 
void PrintMineField(unsigned int width, unsigned int height, Cell** minefield) {

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            Cell current = minefield[i][j];
            switch (minefield[i][j]) {
            case EMPTY: std::cout << '.'; break;
            case MINE: std::cout << 'M'; break;
            default: std::cout << (int)minefield[i][j];
            }
        }
        std::cout << std::endl;
    }
}

/// <summary>
/// Get the input from the user.
/// </summary>
/// <param name="prompt">Prompt for input that will appear.</param>
/// <param name="value">Value to be stored from input.</param>
/// 
void GetInput(const std::string prompt, int& value) {

    std::string input;

    // Repeatedly ask for input until successful.
    while (true) {

        std::cout << prompt;
        std::cin >> input;

        try {
            if (std::stoi(input) < 1) {
                throw (std::out_of_range("Value must be greater than 0."));
            }

            // Try to convert and assign the value.
            value = std::stoi(input);
            
            // Input was successfully converted to an integer
            return; 
        }
        // Invalid argument entered.
        catch (const std::invalid_argument& e) {
            std::cout << "Invalid argument: Value must be an integer." << std::endl;
        }
        // Integer was out of range 
        catch (const std::out_of_range& e) {
            std::cout << "Argument out of range: " << e.what() << std::endl;
        }

        // Clear any invalid input
        // From: https://www.hackerearth.com/practice/notes/validating-user-input-in-c/#:~:text=If%20the%20cin%20fails%20then,loop%20of%20error%20message%20display.
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {

    int width;
    int height;
    int count;

    // Prompt the user for width, height, and mine count.
    while (true) {
        GetInput("Enter a width: ", width);
        GetInput("Enter a height: ", height);
        GetInput("Enter the number of mines: ", count);

        // Ensure we don't have more mines than possible.
        if (count <= width * height) {
            break;
        }
        else {
            std::cout << "Number of mines must not exceed the dimensions of the field." << std::endl;
            continue;
        }
    }

    // Allocate memory for the minefield.
    Cell** minefield = new Cell* [height];

    for (int i = 0; i < height; i++)
        minefield[i] = new Cell[width];

    GenerateMineField(width, height, count, minefield);
    PrintMineField(width, height, minefield);

    // Free allocated memory.
    delete[] minefield;
}
