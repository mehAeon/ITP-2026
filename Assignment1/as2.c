#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// MANDATORY TYPE DEFINITIONS
typedef enum {
    ACTIVE,
    RETIRED,
    DISQUALIFIED
} DriverStatus;

typedef enum {
    NORMAL_RACE,
    SPRINT_RACE
} RaceType;

typedef enum {
    FINISHED,
    DID_NOT_FINISH,
    DISQUALIFIED_RESULT
} ResultType;

typedef union {
    float finish_time;
    char *dnf_reason;
    char *disqualification_reason;
} ResultExtra;

typedef struct {
    int driver_id;
    int position;
    ResultType result_type;
    ResultExtra extra;
} RaceResult;

typedef struct {
    int driver_id;
    char *name;
    char *team;
    int team_id;

    DriverStatus status;

    int races_completed;
    int wins;
    int points;
} Driver;

typedef struct {
    int race_id;
    int finished;
    int dnf;
    int disqualified;
    int winner;
} Race;

typedef struct {
    char team_name[31];
    int drivers_count;
    int wins;
    int points;
} Team;

// GLOBAL VARIABLES
int N; // Number of initial drivers
int current_N; // Actual number of drivers
int driver_capacity;
int R; // Number of races
int Q; // Number of commands
Driver *driverArray = NULL; // Dynamic driver array
char all_names[1000000][31]; // Stored in static storage so that it automatically releases
char all_teams[1000000][31]; // Stored in static storage so that it automatically releases
Race *raceArray = NULL; // Dynamic race array 
Team *teamArray = NULL; // Static team array
int total_teams = 0; // Team counter
int NRpoints[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
int SRpoints[] = {8, 7, 6, 5, 4, 3, 2, 1};
int areArraysSorted = 1; // Used to determine when to sort during output

// FUNCTIONS
int compare_drivers(const void *a, const void *b) { // For qsort (doesnt know what the pointers point to)
    int id_a = ((Driver*)a)->driver_id; // take Driver_id, from a pointer a, that is a pointer to a Driver struct
    int id_b = ((Driver*)b)->driver_id;
    return (id_a > id_b) - (id_a < id_b); // 
}

int compare_races(const void *a, const void *b) { // For qsort (doesnt know what the pointers point to)
    int id_a = ((Race*)a)->race_id; // take Race_id, from a pointer a, that is a pointer to a Race struct
    int id_b = ((Race*)b)->race_id;
    return (id_a > id_b) - (id_a < id_b); // 
}

int compare_standings(const void *a, const void *b) { // For qsort, STANDINGS command (points -> wins -> id)
    Driver *driver_a = (Driver *)a; // Need multiple properties, so take the whole Driver struct pointer
    Driver *driver_b = (Driver *)b;

    if (driver_a->points != driver_b->points) {
        return (driver_b->points > driver_a->points) - (driver_b->points < driver_a->points);
    }

    if (driver_a->wins != driver_b->wins) {
        return (driver_b->wins > driver_a->wins) - (driver_b->wins < driver_a->wins);
    }

    return (driver_a->driver_id > driver_b->driver_id) - (driver_a->driver_id < driver_b->driver_id);
}

RaceType parse_race(const char* s) { // Convert string input into enum value
    if (strcmp(s, "NORMAL_RACE") == 0) return NORMAL_RACE;
    if (strcmp(s, "SPRINT_RACE") == 0) return SPRINT_RACE;

    return NORMAL_RACE;
}

char* parse_status(DriverStatus d) { // Convert string input into enum value
    if (d == ACTIVE) return "ACTIVE";
    if (d == RETIRED) return "RETIRED";
    if (d == DISQUALIFIED) return "DISQUALIFIED";

    return "";
}

int get_or_create_team(char *name) {
    for (int i = 0; i < total_teams; i++) { // Try to find the team
        if (strcmp(teamArray[i].team_name, name) == 0) {
            return i;
        }
    }

    int new_id = total_teams; // If not found, create it
    strcpy(teamArray[new_id].team_name, name);
    teamArray[new_id].drivers_count = teamArray[new_id].wins = teamArray[new_id].points = 0;

    total_teams++;
    return new_id;
}

int main () {
    //printf("%d %d %d", sizeof(Driver), sizeof(all_names), sizeof(Race));
    
    FILE *output_file = fopen("output.txt", "w");
    // read initial values from input
    FILE *input_file = fopen("input.txt", "r");

    // Scan drivers from input
    fscanf(input_file, "%d", &N);
    current_N = N;
    driver_capacity = N > 0 ? N : 1;

    driverArray = (Driver *)malloc(sizeof(Driver) * driver_capacity); // Convert void* to Driver*, otherwise wont compile
    teamArray = (Team *)malloc(sizeof(Team) * 500000);

    for (int i=0; i<N; i++) {
        Driver newd;
        // To prevent unexpected errors assign default values:
        newd.status = ACTIVE;
        newd.wins = newd.points = newd.races_completed = 0;

        fscanf(input_file, "%d %30s %30s", &newd.driver_id, all_names[i], all_teams[i]);
        newd.name = all_names[i];
        newd.team = all_teams[i];

        newd.team_id = get_or_create_team(newd.team);
        teamArray[newd.team_id].drivers_count += 1;

        driverArray[i] = newd;
        //printf("Added driver [NAME = %s]\n", newd.name);
    }
    qsort(driverArray, N, sizeof(Driver), compare_drivers); // Sort immediately

    // Scan races from input
    fscanf(input_file, "%d", &R);
    raceArray = (Race *)malloc(sizeof(Race) * R);

    for (int i=0; i<R; i++) { // Scan races one by one
        int K = 0, temp_raceid;
        char temp_typeStr[13];

        fscanf(input_file, "%d %12s %d", &temp_raceid, temp_typeStr, &K);
        RaceType temp_racetype = parse_race(temp_typeStr);

        // The results of this race are stored in a dynamic array
        RaceResult *results = (RaceResult *)malloc(sizeof(RaceResult) * K);

        // read the K results first
        for (int j=0; j<K; j++) {
            char temp_resultStr[21];
            char buf[1024];
            fscanf(input_file, "%d %d %20s", &results[j].driver_id, &results[j].position, temp_resultStr);

            if (strcmp(temp_resultStr, "FINISHED") == 0) {
                results[j].result_type = FINISHED;
                fscanf(input_file, "%f", &results[j].extra.finish_time);
            } else if (strcmp(temp_resultStr, "DID_NOT_FINISH") == 0) {
                results[j].result_type = DID_NOT_FINISH;
                fscanf(input_file, "%1023s", buf);
                results[j].extra.dnf_reason = (char *)malloc(strlen(buf) + 1);
                strcpy(results[j].extra.dnf_reason, buf);
            } else {
                results[j].result_type = DISQUALIFIED_RESULT;
                fscanf(input_file, "%1023s", buf);
                results[j].extra.disqualification_reason = (char *)malloc(strlen(buf) + 1);
                strcpy(results[j].extra.disqualification_reason, buf);
            }
        }

        // the smallest position among the drivers who FINISHED (0 = nobody finished)
        int best_position = 0;
        for (int j=0; j<K; j++) {
            if (results[j].result_type == FINISHED && (best_position == 0 || results[j].position < best_position)) {
                best_position = results[j].position;
            }
        }

        // how many uncounted results have a position better than the best finisher
        int finisherIncrement = 0;
        if (best_position != 0) {
            for (int j=0; j<K; j++) {
                if (results[j].result_type != FINISHED && results[j].position < best_position) finisherIncrement++;
            }
        }

        // go through them again now that we have finisherIncrement
        int temp_finished = 0, temp_dnf = 0, temp_disqualified = 0, temp_winner = 0;
        for (int j=0; j<K; j++) {
            if (results[j].result_type == FINISHED) {
                temp_finished++;
                int pos = results[j].position - finisherIncrement;
                int temp_points = 0;
                if (pos >= 1) {
                    if (temp_racetype == NORMAL_RACE) {
                        if (pos <= 10) temp_points = NRpoints[pos - 1];
                    } else {
                        if (pos <= 8) temp_points = SRpoints[pos - 1];
                    }
                }

                Driver key;
                key.driver_id = results[j].driver_id;
                Driver *found = (Driver *)bsearch(&key, driverArray, N, sizeof(Driver), compare_drivers);

                found->points += temp_points;
                teamArray[found->team_id].points += temp_points;
                found->races_completed += 1;
                if (pos == 1) {
                    found->wins += 1;
                    teamArray[found->team_id].wins += 1;
                    temp_winner = results[j].driver_id;
                }
            } else if (results[j].result_type == DID_NOT_FINISH) {
                temp_dnf++;
                free(results[j].extra.dnf_reason);
            } else {
                temp_disqualified++;
                free(results[j].extra.disqualification_reason);
            }
        }
        free(results);

        Race new_race;
        new_race.race_id = temp_raceid;
        new_race.finished = temp_finished;
        new_race.disqualified = temp_disqualified;
        new_race.dnf = temp_dnf;
        new_race.winner = temp_winner;

        raceArray[i] = new_race;
    }
    // Sort raceArray by race_id
    qsort(raceArray, R, sizeof(Race), compare_races);
    // Create a separate array that is sorted under STANDINGS conditions
    Driver *standingsDriverArray = (Driver *)malloc(sizeof(Driver) * driver_capacity); // Hopefully we have enough memory
    memcpy(standingsDriverArray, driverArray, sizeof(Driver) * current_N);
    qsort(standingsDriverArray, current_N, sizeof(Driver), compare_standings); // A separate array that is sorted under STANDINGS conditions

    // Scan commands from input
    fscanf(input_file, "%d", &Q);

    // scan the next (Q) commands
    char command_name[11], str_arg1[31];
    int int_arg;
    for (int i=0; i<Q; i++) {
        fscanf(input_file, "%10s", command_name); // pull the next command name
        
        if (strcmp(command_name, "STANDINGS") == 0) {
            if (areArraysSorted == 0) {
                qsort(driverArray, current_N, sizeof(Driver), compare_drivers);
                memcpy(standingsDriverArray, driverArray, sizeof(Driver) * current_N);
                qsort(standingsDriverArray, current_N, sizeof(Driver), compare_standings); // A separate array that is sorted under STANDINGS conditions
                areArraysSorted = 1;
            }
            for (int i=0; i<current_N; i++) {
                fprintf(output_file, "%d %s %s %d %d\n", standingsDriverArray[i].driver_id, standingsDriverArray[i].name,
                    standingsDriverArray[i].team, standingsDriverArray[i].points, standingsDriverArray[i].wins);
            }
        }

        else if (strcmp(command_name, "DRIVER") == 0) {
            if (areArraysSorted == 0) {
                qsort(driverArray, current_N, sizeof(Driver), compare_drivers);
                memcpy(standingsDriverArray, driverArray, sizeof(Driver) * current_N);
                qsort(standingsDriverArray, current_N, sizeof(Driver), compare_standings); // A separate array that is sorted under STANDINGS conditions
                areArraysSorted = 1;
            }

            fscanf(input_file, "%d", &int_arg);
            Driver key; // Create a 'dummy' driver as a mask telling what to look for
            key.driver_id = int_arg; // Tell the bsearch to look for driver_id equal to temp_id

            Driver *found = (Driver *)bsearch(&key, driverArray, current_N, sizeof(Driver), compare_drivers); // Binary search for the driver

            if (found == NULL) {
                fprintf(output_file, "NOT FOUND\n");
            } else {
                fprintf(output_file, "%d %s %s\nSTATUS %s\nRACES %d\nWINS %d\nPOINTS %d\n", found->driver_id, found->name, found->team,
                    parse_status(found->status), found->races_completed, found->wins, found->points);
            }
        }

        else if (strcmp(command_name, "TEAM") == 0) {
            fscanf(input_file, "%30s", str_arg1);
            int team_id = get_or_create_team(str_arg1);
            fprintf(output_file, "%s\nDRIVERS %d\nPOINTS %d\nWINS %d\n", teamArray[team_id].team_name, teamArray[team_id].drivers_count,
                teamArray[team_id].points, teamArray[team_id].wins);
        }

        else if (strcmp(command_name, "TOP") == 0) {
            if (areArraysSorted == 0) {
                qsort(driverArray, current_N, sizeof(Driver), compare_drivers);
                memcpy(standingsDriverArray, driverArray, sizeof(Driver) * current_N);
                qsort(standingsDriverArray, current_N, sizeof(Driver), compare_standings); // A separate array that is sorted under STANDINGS conditions
                areArraysSorted = 1;
            }

            if (current_N <= 0) {
                fprintf(output_file, "NO DATA\n");
            } else {
                fprintf(output_file, "%d %s %s %d\n", standingsDriverArray[0].driver_id, standingsDriverArray[0].name,
                    standingsDriverArray[0].team, standingsDriverArray[0].points);
            }
        }

        else if (strcmp(command_name, "ADD_DRIVER") == 0) {
            // Extend the driverArray
            if (current_N >= driver_capacity) {
                driver_capacity *= 2;
                Driver *temp = (Driver *)realloc(driverArray, sizeof(Driver) * driver_capacity);
                if (temp == NULL) {
                    return 0; // return if out of memory
                }
                driverArray = temp;

                temp = (Driver *)realloc(standingsDriverArray, sizeof(Driver) * driver_capacity);
                if (temp == NULL) {
                    return 0; // return if out of memory
                }
                standingsDriverArray = temp;
            }

            fscanf(input_file, "%d %30s %30s", &int_arg, all_names[current_N], all_teams[current_N]);
            Driver newd;
            newd.status = ACTIVE;
            newd.wins = newd.points = newd.races_completed = 0;

            newd.name = all_names[current_N];
            newd.team = all_teams[current_N];
            newd.driver_id = int_arg;

            newd.team_id = get_or_create_team(newd.team);
            teamArray[newd.team_id].drivers_count += 1;

            driverArray[current_N] = newd;
            //printf("Added driver [NAME = %s]\n", newd.name);
            current_N++;

            areArraysSorted = 0;
        }

        else if (strcmp(command_name, "RETIRE") == 0) {
            if (areArraysSorted == 0) {
                qsort(driverArray, current_N, sizeof(Driver), compare_drivers);
                memcpy(standingsDriverArray, driverArray, sizeof(Driver) * current_N);
                qsort(standingsDriverArray, current_N, sizeof(Driver), compare_standings); // A separate array that is sorted under STANDINGS conditions
                areArraysSorted = 1;
            }

            fscanf(input_file, "%d", &int_arg);
            Driver key; // Create a 'dummy' driver as a mask telling what to look for
            key.driver_id = int_arg; // Tell the bsearch to look for driver_id equal to temp_id

            Driver *found = (Driver *)bsearch(&key, driverArray, current_N, sizeof(Driver), compare_drivers); // Binary search for the driver

            if (found != NULL) {
                found->status = RETIRED;
            }
        }

        else if (strcmp(command_name, "DISQUALIFY") == 0) {
            if (areArraysSorted == 0) {
                qsort(driverArray, current_N, sizeof(Driver), compare_drivers);
                memcpy(standingsDriverArray, driverArray, sizeof(Driver) * current_N);
                qsort(standingsDriverArray, current_N, sizeof(Driver), compare_standings); // A separate array that is sorted under STANDINGS conditions
                areArraysSorted = 1;
            }

            fscanf(input_file, "%d", &int_arg);
            Driver key; // Create a 'dummy' driver as a mask telling what to look for
            key.driver_id = int_arg; // Tell the bsearch to look for driver_id equal to temp_id

            Driver *found = (Driver *)bsearch(&key, driverArray, current_N, sizeof(Driver), compare_drivers); // Binary search for the driver

            if (found != NULL) {
                found->status = DISQUALIFIED;
            }
        }

        else if (strcmp(command_name, "RACE_STATS") == 0) {
            fscanf(input_file, "%d", &int_arg);
            Race key; // Create a 'dummy' driver as a mask telling what to look for
            key.race_id = int_arg; // Tell the bsearch to look for driver_id equal to temp_id

            Race *found = (Race *)bsearch(&key, raceArray, R, sizeof(Race), compare_races); // Binary search for the race

            if (found == NULL) {
                fprintf(output_file, "NOT FOUND\n");
            } else {
                fprintf(output_file, "RACE %d\nFINISHED %d\nDNF %d\nDISQUALIFIED %d\nWINNER %d\n",
                    found->race_id, found->finished, found->dnf, found->disqualified, found->winner);
            }
        }
    }
    


    free(driverArray);
    free(raceArray);
    free(standingsDriverArray);
    free(teamArray);
    fclose(input_file);
    fclose(output_file);
    return 0;
}