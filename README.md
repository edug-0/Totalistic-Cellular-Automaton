# Totalistic-Cellular-Automaton

A C Program that simulates a **Totalistic Cellular Automaton** based on a user defined rule (0-2186).
The program evolves a world with a total of 65 cells over several generations, printing each generation's state and keeping track of cell activity.

## Features 
- **Rule Selection** Converts a user defined integer rule (0-2186) into it's base-3 ternary digit to determine cell behavior      over generations.
- **Linear World** Implements wrap around behavior so edge cells interact properly with the rest of the world.
- **Evolution** Iteratively updates cells based on local sums and user defined rule.
- **Activity Tracking** Counts the total number of times a cell is active and displays the result at the end.

## Concepts And Skills Practiced
- Structured programming with loops, arrays, structs, and conditionals
- Function Design
- Debugging and iterative program development

## How To Run
1. Clone Respitory or download file.
2. Compile using:
     ```bash
     gcc Totalistic_Cellular_Automaton -o automaton
     ./automaton.exe


