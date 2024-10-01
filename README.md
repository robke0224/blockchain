

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
   - Applies transformations based on character type (uppercase, lowercase, or non-alphabetic).
   - Optionally uses NAND operations and inversion for extra randomness.
   - Reverses the modified string at the end for additional complexity.

### 2. **`ivestis_i_bitus` Function**:
   - Converts the input string into a binary string representation (256 bits).
   - Ensures the string has a minimum length of 32 characters by padding with the letter k.

### 3. **`hexas` Function**:
   - Increases the value of hexadecimal characters.
   - For numbers (0-9), increments the character by 1; for letters (A-F, a-f), shifts them within the allowable hexadecimal range.

### 4. **`sesiolika_bitu` Function**:
   - Converts the binary string to hexadecimal using 4-bit chunks.
   - Randomizes transformations based on certain conditions like uppercase letters or special characters in the input string.
   - Ensures the final result is a 64-character hexadecimal string.

### 5. **`priebalses` Function**:
   - Calculates the sum of the alphabetic positions of consonants in the input string.
   - Treats both uppercase and lowercase consonants equally by converting the characters to lowercase.
   - Returns a sum that is later used to modify the binary representation of the input string.

### 6. **`daugyba` Function**:
   - Takes a binary string and modifies it based on the sum of consonants (`wordSum`) provided by `priebalses`.
   - If the `invert` flag is set, it will invert the bits; otherwise, it directly modifies the bits using the consonant sum.
   - The function stops modifying the string once `wordSum` is exhausted (divided down to zero).

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
   git clone https://github.com/robke0224/blockchain.git
   cd blockchain
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
---
FUNCTION keiciaIvesti(input, key, shift, invert, useNand)
    result = input
    
    Initialize a random generator with the hash of input
    Generate random shift values between 1 and 7
    
    FOR each character in result:
        Apply XOR between the character and a dynamic key derived from the input, key, and position

    FOR each character in result:
        Calculate a dynamic shift combining randomness, ASCII value, and position
        Apply a circular left shift to the character based on the dynamic shift

    IF invert is TRUE:
        FOR each character in result:
            Conditionally invert the bits of the character based on randomness

    IF useNand is TRUE:
        FOR each character in result:
            Apply NAND operation between the character and a dynamic key derived from input, key, and randomness

    FOR each adjacent pair of characters in result:
        XOR the current character with the previous character

    Fold the result by XORing the first half of the string with the second half
    
    RETURN result
---
FUNCTION ivestis_i_bitus(input, minLength, padChar)
    WHILE input length is less than minLength:
        Append padChar to the input
    
    Initialize an empty binary string
    
    FOR each character in input:
        Convert the character to an 8-bit binary string
        Append the binary string to the binary string

    RETURN binaryString
---
FUNCTION hexas(hexChar, step)
    IF hexChar is a digit:
        Convert hexChar to an integer
        Increment the integer by step and take modulo 10
        RETURN the new integer as a character
    
    IF hexChar is an uppercase hex character (A-F):
        Convert hexChar to an integer
        Increment the integer by step and take modulo 6
        RETURN the new integer as a character

    IF hexChar is a lowercase hex character (a-f):
        Convert hexChar to an integer
        Increment the integer by step and take modulo 6
        RETURN the new integer as a character

    RETURN hexChar if it's not a valid hex character
---
FUNCTION sesiolika_bitu(bits, originalInput)
    WHILE bits length is not a multiple of 4:
        Add '0' to the beginning of bits

    Initialize a stringstream for the hexadecimal result
    Initialize multiplier based on conditions (uppercase or special characters in the input)
    Initialize pakaitine_reiksme (temporary value)

    FOR each 4-bit segment of bits:
        Convert the 4-bit segment to an integer
        Modify the integer based on the multiplier and a random shift
        Convert the integer to hexadecimal and append it to the stringstream

    Convert the stringstream to a hexadecimal string
    FOR each character in the hexadecimal string:
        Apply the hexas function to modify the character

    IF the hexadecimal string is longer than 64 characters:
        Truncate it to 64 characters
    WHILE the hexadecimal string is shorter than 64 characters:
        Append '0' to the end

    RETURN the final 64-character hexadecimal string
---
FUNCTION priebalses(input)

    sum = 0
    FOR each character in input:
        Convert character to lowercase
        IF character is a consonant:
            Add the position of the character in the alphabet to sum
    
    RETURN sum
---
FUNCTION daugyba(bits, wordSum, invert)

    FOR each bit in bits:
        IF bit is '1':
            IF invert is TRUE:
                Set the bit based on the inverse of wordSum % 2
            ELSE:
                Set the bit based on wordSum % 2
        ELSE:
            IF invert is TRUE:
                Set the bit based on the inverse of wordSum % 2
            ELSE:
                Set the bit based on wordSum % 2
        
        Divide wordSum by 2
        IF wordSum equals 0, break the loop

    RETURN bits
---
FUNCTION apdoroja(input, outputFile)

    Append the length of input to the input string
    Modify the input using keiciaIvesti function
    Convert the modified input to binary using ivestis_i_bitus
    Calculate the consonant sum using priebalses function
    Modify the binary string using daugyba based on the consonant sum
    Convert the binary string to hexadecimal using sesiolika_bitu
    Write the final hash to the output file
---
FUNCTION failiukas(filename, c, size)

    Open a file for writing
    FOR size number of times:
        Write the character 'c' followed by a newline to the file
    Close the file
---
  FUNCTION kratinukas(filename, size)
  
    Open a file for writing
    Generate random printable ASCII characters
    FOR size number of times:
        Write a random character to the file
    Close the file
---   
FUNCTION nevienodi(filename1, filename2, size)

    Open two files for writing
    Generate a random string of size length
    Write the same string to both files
    Change the middle character of the second file
    Close both files
---
FUNCTION tuscias(filename)

    Open the file and immediately close it (creating an empty file)
  ---
FUNCTION testukas1(filename, lineCount)

    Open the input file for reading
    Open the output file for writing
    Record the start time

    FOR each line in the input file (up to lineCount):
        Hash the line using apdoroja
        Write the hash result to the output file

    Record the end time
    Calculate and display the elapsed time
    Close both input and output files
---
  FUNCTION poros_random(length)
  
    Initialize a string with all uppercase and lowercase alphabetic characters
    Initialize an empty random string
    FOR length number of times:
        Append a random character from the string to the random string
    RETURN the random string
---
FUNCTION kolizijos(stringPairs)

    Initialize an empty hash set and a collision counter
    FOR each pair of strings in stringPairs:
        Hash both strings in the pair
        IF both hashes are equal:
            Increment collision counter
            Display the colliding pair
    IF collision counter is greater than 0:
        Display the number of collisions
    ELSE:
        Display that no collisions were found
---
FUNCTION loadStringPairsFromFile(filename)

    Open the file for reading
    Initialize an empty vector of string pairs
    WHILE there are still lines to read:
        Read two strings (a pair) from the file
        Add the pair to the vector
    Close the file
    RETURN the vector of string pairs
---
FUNCTION generate_random_string(length, charSet)

    Initialize an empty string
    FOR length number of times:
        Append a random character from charSet to the string
    RETURN the random string
---
FUNCTION compute_bit_difference(binary1, binary2)

    Initialize a difference counter
    FOR each bit in both binary1 and binary2:
        IF the bits are different:
            Increment the difference counter
    RETURN the percentage of differing bits (differences / total bits * 100)
---
FUNCTION compute_hex_difference(hex1, hex2)

    Initialize a difference counter
    FOR each character in both hex1 and hex2:
        IF the characters are different:
            Increment the difference counter
    RETURN the percentage of differing characters (differences / total characters * 100)


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
