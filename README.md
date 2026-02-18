<div align="center">

  <h1> 🧩 Sudoku Management System </h1>
  
  <p>
    <img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white" />
    <img src="https://img.shields.io/badge/Algorithms-FFD700?style=for-the-badge&logo=algorithms&logoColor=black" />
    <img src="https://img.shields.io/badge/STU_FIIT-00529B?style=for-the-badge&logo=university&logoColor=white" />
  </p>

  <br/>
</div>

---

### 📝 Project Overview
This is a comprehensive management system for Sudoku players and game results developed in **C**. The project focuses on low-level system programming, efficient data parsing, and manual memory management.

### 🛠 Key Technical Concepts
* **Dynamic Memory Management**: Expert use of `malloc`, `realloc`, and `free` to handle data of variable sizes without memory leaks.
* **Advanced Data Structures**: Implementation of **nested linked lists** (a player list where each node contains its own list of solutions).
* **Robust File I/O**: Parsing custom-formatted data from `.txt` files using `strtok` and `fgets`.
* **Procedural Logic**: A custom algorithm to generate playable Sudoku grids by strategically hiding numbers based on difficulty settings.

---

### 🕹 Commands & Functionality
The system is controlled via single-character commands in the terminal:

| Command | Function | Description |
| :---: | :--- | :--- |
| **`v`** | `funkcia_v` | **View**: Displays database records from files, dynamic arrays, or linked lists. |
| **`n`** | `funkcia_n` | **Initialize**: Loads player and solution data into **dynamic arrays**. |
| **`m`** | `funkcia_m` | **Map**: Builds the **linked list** hierarchy from flat text files. |
| **`h`** | `funkcia_h` | **History**: Exports specific game records to `Vystup_H.txt`. |
| **`q`** | `funkcia_q` | **Queue**: Adds a new record to the arrays using dynamic resizing (`realloc`). |
| **`w`** | `funkcia_w` | **Wipe**: Deletes all solution records for a specific Player ID from the arrays. |
| **`e`** | `funkcia_e` | **Edit**: Generates a Sudoku grid by hiding `X` numbers, creating file `vystup_E.txt`(Difficulty Generator). |
| **`a`** | `funkcia_a` | **Add**: Inserts a new player into the linked list at a custom position `Y`. |
| **`s`** | `funkcia_s` | **Scrub**: Removes solution records from the list based on a specific Group ID. |
| **`d`** | `funkcia_d` | **Duration**: Sorts player results by time using a sorting algorithm. |
| **`k`** | `main` | **Kill**: Safely closes all files and frees all allocated heap memory. |

---

### 🚀 Usage
1. **Compilation**:
   ```bash
   gcc sudoku.c -o sudoku_system
2. **Execution**:
```bash
  ./sudoku_system
```
<div align="center">
<p>Developed as part of the curriculum at <b>STU FIIT Bratislava</b> 🎓</p>
</div>


