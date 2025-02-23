# Bit Manipulation in C

Name: Malhar Mahajan

## Overview
This project focuses on **low-level bit manipulation in C**, specifically **decoding packed integer data streams**. It involves efficiently unpacking compressed data encoded in a binary format.

## Features
- Uses **bitwise operations** for efficient data extraction.
- Implements **big-endian decoding** to reconstruct integers from byte streams.
- Reads input in **hexadecimal notation** and converts it to standard integers.
- Supports multiple packed integers in a single byte stream.

## How It Works
1. Reads the number of data lines from input.
2. Parses each line to extract bytes in hexadecimal format.
3. Decodes each byte sequence into standard integers using **bitwise operations**.
4. Prints the unpacked integers with their respective input line numbers.

## Compilation & Execution
To compile the project, run:
```bash
gcc -o decoder main.c
