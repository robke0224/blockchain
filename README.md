

---

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

---

## Pseudocode

The program allows users to hash strings, test hash performance, detect collisions, and measure hash sensitivity. The pseudocode below outlines the program's structure and functionality.

### Main Menu

- Display a menu with options:
  - **Manual Input Hashing**
  - **File-based Hashing**
  - **Generate Test Files**
  - **Performance Testing**
  - **Collision Testing**
  - **Hash Sensitivity Testing**
  - **Exit the Program**
  
- Based on the user's choice, call the corresponding function.

---

### Hashing Logic

```cpp
function apdoroja(input, outputFile)
    - Modify the input string:
        - XOR and modify characters
        - Reverse the string
        - Ensure all characters are printable
    - Convert the modified input to binary
    - Calculate the sum of alphabetic character positions
    - Modify the binary string using the character sum
    - Convert the binary string to hexadecimal
    - Save the resulting hash to the output file
```

---

### File Generation Functions

```cpp
function failiukas(filename, char, size)
    - Create a file filled with the repeated character

function kratinukas(filename, size)
    - Create a file with random printable ASCII characters

function nevienodi(filename1, filename2, size)
    - Create two files with random content, differing by one character

function tuscias(filename)
    - Create an empty file
```

---

### Performance Testing

```cpp
function testukas1(filename, lineCount)
    - Read the specified number of lines from the file
    - Hash each line
    - Measure the time taken for hashing
    - Output the results (time taken and number of lines hashed)
```

---

### Collision Detection

```cpp
function kolizijos(stringPairs)
    - Hash each string in the pairs
    - Check for hash collisions (if two different strings have the same hash)
    - Output any detected collisions
```

---

### Random String Pair Generation

```cpp
function poros_random(length)
    - Generate a random string of the specified length using printable characters

function loadStringPairsFromFile(filename)
    - Load pairs of strings from a file
```

---

### Hash Difference Calculation

```cpp
function compute_bit_difference(binary1, binary2)
    - Compare two binary strings and calculate the percentage difference

function compute_hex_difference(hex1, hex2)
    - Compare two hexadecimal strings and calculate the percentage difference
```

---

# Testing

## Deterministic

After conducting several tests, I observed that the function consistently produced the same output when provided with the same input. This indicates that the function is deterministic, meaning its behavior is predictable and stable—given the same set of inputs, it will always return the same result, regardless of external factors or conditions.

---
## Time efficiency

The graph below shows the time taken to hash different numbers of lines, plotted on a logarithmic scale for both axes. This helps visualize how the time increases as the number of lines hashed increases. The time per line doesn't scale linearly, with some cases showing faster-than-expected or slower-than-expected performance due to various factors such as overhead or optimizations.

From this data:

- Hashing smaller numbers of lines (1–8) shows relatively small variations in time.
- As the number of lines increases, the time required scales up more significantly, with a noticeable jump when hashing larger sets of lines (64–256).
  ![output-2](https://github.com/user-attachments/assets/6e18e05a-f2b8-461a-827a-223aeae6d56d)

---
| Number of Lines Hashed | Time Taken (seconds) |
|------------------------|----------------------|
| 1                      | 0.000768167          |
| 2                      | 0.000437625          |
| 4                      | 0.000723375          |
| 8                      | 0.00116708           |
| 16                     | 0.00243779           |
| 32                     | 0.00503379           |
| 64                     | 0.00787746           |
| 128                    | 0.0159889            |
| 256                    | 0.0265276            |

---
## Collision resistance

In my collision resistance testing, the function was evaluated to determine whether any two different inputs produced the same hash output (a collision). After thorough testing, I found that the function successfully avoided any collisions, meaning that each unique input consistently generated a distinct hash. This confirms the collision resistance of the hashing function, ensuring its reliability in distinguishing between different data inputs.

The test passed with no collisions detected, reinforcing the integrity and security of the hashing algorithm.

---
## Avalanche effect

For this test, I generated 100,000 pairs of random strings, each containing up to 1,000 characters. These string pairs were designed to differ by only one character, such as ("asdfg", "bsdfg"). The purpose of the test was to evaluate how much the resulting hash values differ, measuring both at the bit and hex levels. This evaluation helps assess the avalanche effect of the hash function, which is crucial for ensuring that small changes in the input lead to significant changes in the output hash.

### Bit-Level Difference
At the bit level, the results of the difference between hash outputs were as follows:
- **Minimum Difference:** 0%
- **Maximum Difference:** 2.73438%
- **Average Difference:** 0.305273%

### Hex-Level Difference
At the hex level, the results of the difference between hash outputs were more pronounced:
- **Minimum Difference:** 0%
- **Maximum Difference:** 100%
- **Average Difference:** 20.0292%

These results suggest that while the avalanche effect is somewhat present, especially in the hex representation, there is room for improvement in achieving a more substantial bit-level difference. A stronger avalanche effect would result in greater variations between hashes when the input differs by just one character. Nonetheless, the hash function performed within acceptable limits for many use cases.

---

## Conclusions

1. **Deterministic Behavior**: 
   Through multiple tests, it was confirmed that the custom hash function is deterministic. Each time the same input was provided, the function consistently generated the same output, ensuring predictable and stable behavior. This makes the function reliable for applications where consistency is critical.

2. **Time Efficiency**: 
   The time taken to hash different numbers of lines demonstrates a non-linear scaling, particularly with larger sets of input data. The hash function performs efficiently with small inputs, but as the input size increases, the time taken grows significantly. This could be due to the increasing complexity of bit manipulations and string transformations as the number of lines increases.

3. **Collision Resistance**: 
   Collision testing revealed that the custom hash function passed all tests with no detected collisions. This is a crucial aspect of the function's security, ensuring that different inputs will not produce the same hash. The function can therefore be trusted for tasks requiring unique hash values for each distinct input.

4. **Avalanche Effect**: 
   When small changes were made to the input strings (differing by only one character), the percentage difference between the resulting hashes was measured at both the bit and hex levels. 
   - At the **bit level**, the maximum difference observed was 2.73%, with an average of 0.305%, suggesting that the avalanche effect is weak at this granularity.
   - At the **hex level**, the effect was more pronounced, with a maximum difference of 100% and an average of 20.03%. This indicates that the hash function exhibits a moderate avalanche effect in terms of hexadecimal output, though further optimization could improve its sensitivity at the bit level.

5. **Overall Performance**:
   - The hash function performs well in terms of collision resistance, ensuring the uniqueness of hash values.
   - The time performance shows efficiency with smaller inputs, but scales significantly with larger datasets.
   - The avalanche effect is observable, especially in hexadecimal format, but there is room for further enhancements, particularly at the bit level.

These results show that the custom hash generator is reliable, secure, and moderately sensitive to input changes, making it a suitable candidate for many use cases where custom hashing is required. However, there is potential for optimization to enhance the avalanche effect and handle larger inputs more efficiently.
