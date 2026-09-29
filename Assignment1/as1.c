#include <stdio.h>
#include <stdlib.h> // functions: abs
#include <string.h> // functions: strcmp

int max(int a, int b) { // returns the maximum of 2 integers
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int min(int a, int b) { // returns the minimum of 2 integers
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

// INITIAL PROGRAM STATE
int x = 0, y = 0;
int battery = 0, heat = 0, cargo = 0;
int mode = 0; // 0=IDLE, 1=ACTIVE, 2=SAFE
int distance = 0;
int accepted = 0, rejected = 0, restores = 0;
int checkpoint[5]; // array for saved data
int checkpoint_valid = 0; // 0 if no checkpoint has been saved in this execution, otherwise 1
int L; // coordinate limit
int CAP; // highest possible ccargo mass
int BMAX; // battery maximum capacity
int b0, h0; // initial input for battery & heat

int command_start () {
    if (mode == 1) { // Reject if already active
        rejected += 1;
        return -1;
    }
    else if (mode == 2) { // Reject if mode is SAFE
        rejected += 1;
        return -2;
    }
    else if (battery < 5) { // Reject if not enough battery
        rejected += 1;
        return -3;
    }
    else if (heat >= 80) { // Reject if overheating
        rejected += 1;
        return -4;
    }

    accepted += 1;
    mode = 1; // Activate the rover and increment accepted count otherwise
    return 1;
}

int command_stop () {
    if (mode != 1) { // Reject if inactive
        rejected += 1;
        return -5;
    }

    accepted += 1; // Otherwise stop the rover
    mode = 0;
    return 2;
}

int command_move(int dx, int dy, int *x, int *y) {
    int dest_x = *x + dx, dest_y = *y + dy; // calculate the destination coordinates
    int manhattan_distance = abs(dx) + abs(dy); // absolute value is needed to prevent "negative distance"
    int energy_cost = manhattan_distance * (2 + cargo); // energy cost scales with cargo mass

    // Rejection rules after calculations in order to prevent splitting rules into two blocks (readability)
    if (mode != 1) { // reject if rover is inactive
        rejected += 1;
        return -10;
    }
    else if (dx == 0 && dy == 0) { // reject if no destination
        rejected += 1;
        return -11;
    }
    else if (abs(dest_x) > L || abs(dest_y) > L) { // reject if destination is outside the legal coordinate square
        rejected += 1; // ^ if L is 100, then x = 101 and x = -101 are illegal, thus abs() is needed
        return -12;
    }
    else if (battery < energy_cost) { // reject if insufficient battery energy
        rejected += 1;
        return -13;
    }

    // Otherwise, apply updates
    heat += manhattan_distance + cargo;
    *x = dest_x;
    *y = dest_y;
    battery -= energy_cost;
    distance += manhattan_distance;

    // Automatic rule
    if (heat >= 100 || battery == 0) {
        mode = 2; // Set mode to SAFE
    }

    accepted += 1;
    return 3; // Successful return and increment
}

int command_load(int w) { // adds weight to cargo mass
    if (mode != 0) { // Reject if rover is not IDLE
        rejected += 1;
        return -20;
    }
    else if (x != 0 || y != 0) { // Reject if rover is not at base (0, 0)
        rejected += 1;
        return -21;
    }
    else if (w <= 0) { // Reject if the weight is invalid
        rejected += 1;
        return -22;
    }
    else if (cargo + w > CAP) { // Reject if the weight is invalid
        rejected += 1;
        return -23;
    }

    // Otherwise, add w to cargo and increment
    accepted += 1;
    cargo += w;
    return 4;
}

int command_unload(int w) { // removes weight from cargo mass
    if (mode == 1) { // Reject if rover is ACTIVE
        rejected += 1;
        return -30;
    }
    else if (w <= 0) { // Reject if the weight is invalid
        rejected += 1;
        return -31;
    }
    else if (w > cargo) { // Reject if the weight exceeds current cargo mass
        rejected += 1;
        return -32;
    }

    // Otherwise, remove w from cargo and increment
    accepted += 1;
    cargo -= w;
    return 5;
}

int command_cool () {
    if (mode == 1) { // Reject if rover is active
        rejected += 1;
        return -40;
    }

    // Otherwise, decrease heat by 25 but heat can't go below 0
    heat = max(0, heat - 25);

    // Set mode to IDLE, if the rover is SAFE and heat<80 & battery>0
    if (mode == 2 && heat < 80 && battery > 0) {
        mode = 0;
    }

    accepted += 1;
    return 6;
}

int command_recharge (int amount) { // increase battery by an amount
    if (mode == 1) { // Reject if rover is active
        rejected += 1;
        return -50;
    }
    else if (x != 0 || y != 0) { // Reject if rover is not at base (0, 0)
        rejected += 1;
        return -51;
    }
    else if (amount <= 0) { // Reject if the amount is invalid
        rejected += 1;
        return -52;
    }

    // Otherwise, increase battery and increment
    battery = min(BMAX, battery + amount); // min() to prevent overcharge over max capacity

    // Set mode to IDLE, if the rover is SAFE and heat<80 & battery>0
    if (mode == 2 && heat < 80 && battery > 0) {
        mode = 0;
    }

    accepted += 1;
    return 7;
}

int command_save () {
    if (mode != 0) { // Reject if rover is not idle
        rejected += 1;
        return -60;
    }

    // Otherwise, write current stats into checkpoint[5]
    checkpoint_valid = 1;
    checkpoint[0] = x;
    checkpoint[1] = y;
    checkpoint[2] = battery;
    checkpoint[3] = heat;
    checkpoint[4] = cargo;
    accepted += 1;
    return 8;
}

int command_restore () {
    if (mode == 1) { // Reject if rover is active
        rejected += 1;
        return -70;
    }
    else if (checkpoint_valid == 0) { // Reject if no checkpoint was saved yet
        rejected += 1;
        return -71;
    }

    // Otherwise, restore stats from checkpoint
    x = checkpoint[0];
    y = checkpoint[1];
    battery = checkpoint[2];
    heat = checkpoint[3];
    cargo = checkpoint[4];
    // Set mode to idle, increment restores
    mode = 0;
    restores += 1;
    accepted += 1;
    return 9;
}



int main () {
    // open output.txt
    FILE *output_file = fopen("output.txt", "w");
    // read initial values from input
    FILE *input_file = fopen("input.txt", "r");
    fscanf(input_file, "%d %d %d %d %d", &b0, &BMAX, &h0, &CAP, &L);
    battery = b0;
    heat = h0;
    
    // scan the amount of commands (n)
    int n;
    fscanf(input_file, "%d", &n);

    // scan the next (n) commands
    char command_name[9];
    int arg1, arg2, result;
    for (int i = 0; i < n; i++) {
        fscanf(input_file, "%s", command_name); // pull the next command name
        
        // identify the command to decide what to pull next
        // if the command name implies arguments, then it looks for integers after the command name
        // command code is stored into (result), function call executes the function
        // STATUS has a special output
        if (strcmp(command_name, "STATUS") == 0) {
            fprintf(output_file, "S %d %d %d %d %d %d %d %d %d %d %d\n", x, y, battery, heat, cargo, mode, distance, accepted, rejected, restores, checkpoint_valid);
        } else {
            if (strcmp(command_name, "START") == 0) {
                result = command_start();
            } else if (strcmp(command_name, "STOP") == 0) {
                result = command_stop();
            } else if (strcmp(command_name, "MOVE") == 0) {
                fscanf(input_file, "%d %d", &arg1, &arg2);
                result = command_move(arg1, arg2, &x, &y);
            } else if (strcmp(command_name, "LOAD") == 0) {
                fscanf(input_file, "%d", &arg1);
                result = command_load(arg1);
            } else if (strcmp(command_name, "UNLOAD") == 0) {
                fscanf(input_file, "%d", &arg1);
                result = command_unload(arg1);
            } else if (strcmp(command_name, "COOL") == 0) {
                result = command_cool();
            } else if (strcmp(command_name, "RECHARGE") == 0) {
                fscanf(input_file, "%d", &arg1);
                result = command_recharge(arg1);
            } else if (strcmp(command_name, "SAVE") == 0) {
                result = command_save();
            } else if (strcmp(command_name, "RESTORE") == 0) {
                result = command_restore();
            }
            fprintf(output_file, "R %d\n", result);
        }
    }
    // final output
    fprintf(output_file, "F %d %d %d %d %d %d %d %d %d %d %d\n", x, y, battery, heat, cargo, mode, distance, accepted, rejected, restores, checkpoint_valid);
    
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}