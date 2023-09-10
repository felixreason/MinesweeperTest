# Minesweeper Game

This is a simple implementation of the Minesweeper game in C++. It allows users to implement parameters and then generates a mine field according to these paraments.

## Getting Started

To run the Minesweeper test, follow these steps.

### Prerequisites

- Windows operating system (for GUI application)
- No additional software is required.

### Usage

1. Download the latest release of the project from the [Releases](https://github.com/yourusername/minesweeper/releases) section of this GitHub repository.

2. Extract the downloaded ZIP file to a directory of your choice.

3. Double-click the `minesweeper.exe` file under ..\MinesweeperTest\Minesweeper\x64\Release to launch the application.

4. The Minesweeper GUI will open, prompting you to enter the width, height, and number of mines.

5. Enter the desired values in the provided fields or prompts within the GUI.

6. A minefield will generate with the given width and height, populated with the given number of mines.

### Example Output
The program generates a minefield to the console, each cell being represented by a cahracter:

- '.' representing an empty cell.
- 'M' representing a mine.
- Numbers representing the number of adjacent mines (e.g. '1', '2', etc.).

Example:

Enter a width: 10
Enter a height: 10
Enter the number of mines: 10

12M21.....
1M3M1.....
22311.....
1M1.......
22311.....
1M2M1...11
11211...1M
.111....11
12M1...111
M211...1M1
