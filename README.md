# TextEditorProject

Kilo is a simple, yet powerful, text editor built in C based on the guide from [kilo.c](https://viewsourcecode.org/snaptoken/kilo/) by **Snaptoken**. This project demonstrates the basic concepts of text editing, including input handling, screen drawing, file reading, and more. It’s a great starting point for understanding how a text editor works at a low level using C.

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Controls](#controls)
6. [Contributing](#contributing)
7. [License](#license)

## Introduction

This text editor is a minimal, terminal-based editor created to handle basic text editing tasks. The implementation closely follows the guide from the `kilo.c` repository and is an educational project to help users understand how to build a terminal-based text editor from scratch in C.

Key features include:

- Open and edit text files.
- Navigation through text with arrow keys.
- Basic text input and deletion.
- File saving functionality.

## Features

- **Edit files**: Open a file and make changes to it in real-time.
- **Basic controls**: Use arrow keys to move the cursor, backspace to delete, and `Ctrl+S` to save.
- **Terminal-based**: The editor runs directly in the terminal, with no GUI required.
- **File opening and saving**: Easily open text files and save changes.

## Installation

To compile and run the Kilo text editor, you need a C compiler and a terminal environment.

### Prerequisites

- A C compiler (e.g., GCC or Clang).
- A Unix-like terminal (Linux, macOS, or WSL on Windows).

### Steps

1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/inserturuser/kilo-text-editor.git
    ```

2. Navigate to the project directory:
    ```bash
    cd urdirectoryname

3. Compile the project using GCC or any C compiler:
    ```bash
    gcc -o kilo kilo.c
    ```

4. Run the editor:
    ```bash
    ./kilo
    ```

## Usage

Once the editor is compiled, you can use it to open and edit text files from your terminal. Upon starting the program, you'll be presented with a blank screen where you can type your text.
