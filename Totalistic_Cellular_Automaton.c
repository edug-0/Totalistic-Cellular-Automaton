//Totalistic Cellular Automaton

#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65; // the size of the 1D world array
const int MIDDLE_CELL = 32; // the middle cell of the world

typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;

// convert an integer rule (0-2186) to its base-3 representation, 
// stored in reverse order, as an array of 7 status values, i.e. valArray[7] 
//return true if input rule is valid (0-2186)
//return false if input rule is invalid
bool setValArray(int valArray[7], int rule) {
        //TODO: Task 1 - write the setValArray() function
        
        //checks if user inputted value for rule is within bounds
        if(rule>=0 && rule<=2186){
            for(int i = 0; i<7; i++) {
                //inputs remainder into valArray at corresponding index for 7-ternary-digit
                    valArray[i] = rule % 3;
                    rule /= 3;
                }
            
            return true;
        } else {
            return false;
        }
}

// update the localSum subitem for each cell in the world array based on the
// current statuses for the nearby [left, me, right] cells
// note: world is periodic/cyclic, with front-to-back and back-to-front wrapping 
void setSums(cell world[WORLD_SIZE]) {

    //TODO: Task 4 - write the setSums() function
    for(int i = 0; i<WORLD_SIZE; i++) {
        
        //checks for left edge
        if(i == 0) {
            world[i].localSum = world[WORLD_SIZE-1].status + world[i].status + world[i+1].status;
        } else if (i == WORLD_SIZE-1) { //checks for right edge
            world[i].localSum = world[WORLD_SIZE-2].status + world[i].status + world[0].status;
        } else { //base case
            world[i].localSum = world[i-1].status + world[i].status + world[i+1].status;
        }
    }
    return;
}

// Evolve the world to the next generation by updating each cell's status value 
// using its localSum subitem (assumed to be updated outside of this function), where
// ruleValArray[7] stores the status values for the 7 possible local sums, in reverse order, 
// This function returns the total sum of all status values in world[] after the evolution step.
int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {

    //TODO: Task 6 - write the evolveWorld() function
    int sum = 0;
    for(int i = 0; i < WORLD_SIZE; i++) {
        //changes a cells status depending on rule 7-ternary-digit
        
        world[i].status = ruleValArray[world[i].localSum];
        world[i].count += world[i].status; 
        sum += world[i].status; //adds status to generations total sum
    }
    return sum;
}


int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Totalistic Cellular Automaton!\n");

    printf("Enter the rule # (0-2186): \n");
    
    //      read in a valid rule#, allowing repeated attempts if necessary,
    //      generate the rule's 7-trit (i.e. 7 base-3 digits) status value array,  
    //      print the status value array in correct ternary (i.e. base-3) number order
    int valArray[7];
    int rule;
    bool isValid;
    scanf("%d", &rule); //get user input for rule
    isValid = setValArray(valArray, rule); //checks validity
    while(isValid == false) { //loops until user input is valid
        printf("Enter the rule # (0-2186): \n");
        scanf("%d", &rule);
        isValid = setValArray(valArray, rule); 
    }
    printf("\n");
    //print valArray in reverse order
    printf("The value array for rule #%d is ", rule);
    for(int i = 6; i >= 0; i--) {
                printf("%d", valArray[i]);
            }
    printf("\n\n");
    

    printf("The evolution of all possible states are as follows:\n");
    printf("Local Sum:   6       5       4       3       2       1       0      \n");
    printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n");
    printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");
    printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");
    printf("                           |+--|   | +-|   |+  |                    \n");
    printf("                           |-+-|   |- +|   | + |                    \n");
    printf("                           |--+|   | -+|   |  +|                    \n");
    printf("                                   |---|                            \n");
    printf("New Status: ");      
    //      use the rule status value array to report the evolution 
    //      step for all possible cell neighbor states [left, me, right].
    for(int i = 6; i >= 0; i--) {
        if(valArray[i] == 0) {
            printf("| |     ");
        } else if (valArray[i] == 1) {
            printf("|-|     ");
        } else if (valArray[i] == 2) {
            printf("|+|     ");
        }
    }
    printf("\n\n");

    printf("Enter the number of generations (1-49): \n");     
    //      read in the total number of generation evolution steps
    //      from the user, allowing repeated attempts for invalid values.
    int gens; 
    scanf("%d", &gens);
    while(gens<1 || gens>49) { //loop until number of generations inputted by user is within bounds
        printf("Enter the number of generations (1-49): \n"); 
        scanf("%d", &gens);
    }
    
    printf("Enter the value (1 or 2) for the initial active cell: \n");
    //      read in the initial status value for the middle cell, 
    //      allowing repeated attempts for invalid values. 
    int initialCell;
    scanf("%d", &initialCell);
    while(initialCell < 1 || initialCell>2) { //loop until initial cell value inputted by user is within bounds
        printf("Enter the value (1 or 2) for the initial active cell: \n");
        scanf("%d", &initialCell);
    }
    printf("\n");
    printf("Initializing world & evolving...\n");
    //      initialize the world with the ONLY non-zero cell in the 
    //      exact middle of the world, whose status value is set using the 
    //      scanned-in value from the user above. 
    for(int i = 0; i < WORLD_SIZE; i++) {
        world[i].status = 0;
        world[i].count = 0;
        world[i].localSum = 0;
    }
    //change status of cell in the middle of the world to user inputted value initialCell
         world[MIDDLE_CELL].status = initialCell;
         world[MIDDLE_CELL].count = world[MIDDLE_CELL].status;
        

    //      evolve the world the user-specified number of generations,
    //      printing the world after each evolution step, where each cell prints as
    //      '+', '-', or ' ' (whitespace) for status value of 2, 1, or 0, respectively.
    //      After the world display, print total sum of all status values.
    int total = 0;
    for(int i = 0; i < WORLD_SIZE; i++) {
        if (world[i].status == 0) {
                printf(" "); // prints white space with status 0
            } else if (world[i].status == 1) {
                printf("-"); //prints - with status 1
            } else {
                printf("+"); //prints + with status 2
            }
            total = world[MIDDLE_CELL].status;
           
    }
     printf(" %d \n", total);
    setSums(world);
    for(int i = 1; i < gens; i++) {
        //setSums of every cell in world at the beginning of every new generation
        total = evolveWorld(world, valArray);
        setSums(world);
        for(int j = 0; j < WORLD_SIZE; j++) {
            if (world[j].status == 0) {
                printf(" "); // prints white space with status 0
            } else if (world[j].status == 1) {
                printf("-"); //prints - with status 1
            } else {
                printf("+"); //prints + with status 2
            }
        }
        
        printf(" %d \n", total);
        
        
    }

    //      after the line under the last generation, 
    //      print the total sum for each cell throughout all evolution steps vertically.
    //      The cell total sums printed as two digit numbers across two lines.
    //      Single-digit total sums represented as a whitespace on the top line, 
    //      and the single-digit on the lower line. 
    
    printf("_________________________________________________________________\n"); // make sure to end your program with a newline
    for(int i = 0; i < WORLD_SIZE; i++){ //print tens digit for each cell count
        int cellTotal = world[i].count;
        if(cellTotal / 10 == 0) printf(" "); //if cellTotal truncates to zero print nothing.
        else printf("%d", cellTotal / 10); //
    }
    printf("\n");
    for(int i = 0; i < WORLD_SIZE; i++){
        int cellTotal = world[i].count;
        if(cellTotal == 0) printf(" "); // if cell count is 0 white space is printed
        else printf("%d", cellTotal % 10); //remainder of cell count when % 10 is the ones digit
    }
    printf("\n");
    

    return 0;
}
