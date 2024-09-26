# Blockchain
-----------------------------------------------------------------------------------------------
# Custom Hash Generator

This repository contains a C++ program that generates a custom hash from user input. The program provides two options for input: manual entry or reading from a file. The hash is generated using bit manipulation, string transformations, and hexadecimal calculations, with additional randomization elements, and the result is saved into a file.

## Features
- **Input Options**: 
  - Manually input text from the console.
  - Read text from a file (`konstitucija.txt`).
- **Custom Hash Generation**:
  - Manipulates input using XOR operations, ASCII modifications, and reverse transformations.
  - Converts the input into a 256-bit binary string and further transforms it.
  - Performs hexadecimal manipulations.
  - Produces a unique 64-character hexadecimal hash.

## How the Code Works

### 1. **`keiciaIvesti` Function**:
   - Alters the input string by applying XOR on each character.
   - Different transformations are applied based on whether the character is uppercase, lowercase, or a non-alphabet character.
   - Reverses the modified string at the end.

### 2. **`ivestis_i_bitus` Function**:
   - Converts the input string into a binary representation (256 bits).
   - Pads the input string with the letter `k` to ensure it reaches a minimum length of 32 characters.

### 3. **`hexas` Function**:
   - Increases the value of hexadecimal characters.
   - For numbers (0-9), increments the character by 1, and for letters (A-F, a-f), shifts the character within its range.

### 4. **`sesiolika_bitu` Function**:
   - Converts the binary string into hexadecimal using 4-bit chunks.
   - Randomizes the transformation based on conditions such as the presence of uppercase letters or exclamation marks in the original input.
   - Ensures the result is exactly 64 hexadecimal characters.

### 5. **`suma` Function**:
   - Calculates the sum of the alphabetic characters in the input string.
   - Treats both uppercase and lowercase letters as lowercase to compute the sum.

### 6. **`dauginti_bitus_is_sumos` Function**:
   - Modifies the binary string based on the sum of the alphabetic characters.
   - Performs bitwise changes using the sum value.

### 7. **`apdoroja` Function**:
   - Coordinates the hashing process by:
     - Modifying the input.
     - Converting it to binary.
     - Applying bit transformations.
     - Generating the final hash.

### Input/Output:
- The user can either input a string directly or the program can read from a file.
- The hash is written into a file named `hashas.txt`.

## How to Run

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/your-repo.git
   cd your-repo
   ```

2. **Compile the Program**:
   ```bash
   g++ -o hash_generator hash_generator.cpp
   ```

3. **Run the Program**:
   ```bash
   ./hash_generator
   ```

4. **Input Options**:
   - Option 1: Enter a string manually.
   - Option 2: The program will read from the file `konstitucija.txt` (you can modify this file or replace it with your own).

5. **Output**:
   - The resulting hash will be saved in a file named `hashas.txt` in the same directory.

## Example
If you input the string `HelloWorld!`, the program will generate a 64-character hexadecimal hash and save it into the file `hashas.txt`.

## File Structure

- **`main.cpp`**: Main C++ file that implements the custom hash generator.
- **`hash.cpp`**: Contains the functions.
- **`hash.h`**: Header file.
- **`hashas.txt`**: Output file where the generated hash is saved.
- **`konstitucija.txt`**: Sample input file to be used if the file input option is selected.

## Customization
Feel free to modify the transformation functions (like `keiciaIvesti`, `sesiolika_bitu`, etc.) to generate hashes with different properties, or add additional input/output features as needed.

## Notes
- The code uses the system time to seed random number generation for additional randomness in the hash.
- Ensure that the `konstitucija.txt` file exists in the working directory if you're selecting the file input option.

------------------------------------------------------------------------------------------------------
## Pseudocode


The program allows users to hash strings, test hash performance, detect collisions, and measure hash sensitivity. The pseudocode below outlines the program's structure and functionality.

## Main Menu

Display a menu with options:
- Manual Input Hashing
- File-based Hashing
- Generate Test Files
- Performance Testing
- Collision Testing
- Hash Sensitivity Testing
- Exit the Program
  
Based on the user's choice, call the corresponding function.
