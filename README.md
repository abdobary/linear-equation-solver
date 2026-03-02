# Linear Equation Solver

A C++ program that parses, displays, manipulates, and solves systems of linear equations using Cramer's Rule.

## About The Project

This project is a command-line linear equation solver developed in C++. It accepts a system of linear equations with potentially noisy/malformed input and provides an interactive command interface to inspect, manipulate, and solve the system using **Cramer's Rule** and **Gaussian Elimination** for determinant computation.

---

## Built With

- **C++17**
- Standard Template Library (STL): `<map>`, `<vector>`, `<set>`, `<sstream>`, `<cmath>`

---

## Getting Started

### Prerequisites

- A C++ compiler supporting C++17 (e.g., `g++`, `clang++`, MSVC)
- Linux, macOS, or Windows with a terminal

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/linear-equation-solver.git
   cd linear-equation-solver
   ```

2. Compile the source code:
   ```bash
   g++ -std=c++17 -o solver main.cpp
   ```

3. Run the program:
   ```bash
   ./solver
   ```

---

## Usage

### Input Format

```
<number_of_equations>
<equation_1>
<equation_2>
...
<command>
```

### Example Session

```
3
2x1+3x2-x3=10
x1-x2+2x3=5
3x1+x2+x3=15
solve
```

### Available Commands

| Command | Syntax | Description |
|---|---|---|
| `num_vars` | `num_vars` | Print count of unique variables |
| `equation` | `equation <i>` | Print equation i (1-based index) |
| `column` | `column <var>` | Print coefficient column for variable |
| `add` | `add <a> <b>` | Print sum of equations a and b |
| `subtract` | `subtract <a> <b>` | Print difference of equations a and b |
| `substitute` | `substitute <var> <a> <b>` | Substitute variable from eq b into eq a |
| `D` | `D` | Print the coefficient matrix |
| `D_value` | `D_value` | Print the determinant |
| `solve` | `solve` | Solve using Cramer's Rule |
| `quit` | `quit` | Exit the program |

### Noisy Input Handling

The parser automatically strips invalid characters (brackets, symbols, etc.) from equation strings:

```
Input:  6-6+3.2x5-5.2y2-*&(&44x3-[[5+]10-2x4-]]10-5+2=10+3x2
Parsed: Valid equation with clean coefficients and variables
```

---

## Features

- **Robust Parsing** – Handles malformed/noisy equations with special characters
- **Flexible Variable Names** – Supports any alphanumeric variable names
- **Equation Manipulation** – Add, subtract, and substitute equations interactively
- **Determinant Computation** – Gaussian elimination with partial pivoting
- **Cramer's Rule Solver** – Finds unique solutions or reports "No Solution"

---

## Course Information

| Field | Details |
|---|---|
| Course | Foundations of Software Development 2025–2026 |
| Group | Intelligent |
| Supervisor | Eng. Mostafa Ashraf |

---

## Author

**Abdelrahman Tarek**
Full project — Parser & Input Handling, Matrix Operations & Solver, Command Interface, Testing, and Documentation.

---

## License

This project was developed for academic purposes as part of the Foundations of Software Development course.
