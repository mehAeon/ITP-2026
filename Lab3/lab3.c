#include <stdio.h>
#include <string.h>
// REPLACE FUNCTION NAMES UNDER EXERCISE NUMBERS WITH main TO BOOT THEM UP

int fact (int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}

/* EXERCISE 1 */
int strong_number ()
{
    int a, b;
    printf("Input two integers (a and b):\n");
    scanf("%d %d", &a, &b);

    for (int i = a; i <= b; i++) {
        int n = i;
        int sum = 0;
        bool strong = false;
        while (n > 0) {
            int digit = n % 10;
            sum += fact(digit);
            n /= 10;
        }
        if (sum == i) {
            strong = true;
        }
        if (strong) {
            printf("%d is a strong number.\n", i);
        } else {
            printf("%d is not a strong number.\n", i);
        }
    }

    return 0;
}

/* EXERCISE 2 */
int count_of_chars () {
    char String[20];
    int A[26] = {0};
    int current_max = -1;
    printf("Input a string:\n");
    fgets(String, sizeof(String), stdin);
    for (int i = 0; i < strlen(String); i++) {
        if ((int)(String[i]) - 97 < 0 || (int)(String[i]) - 97 > 27) {
            continue;
        }
        A[(int)(String[i]) - 97]++;
        current_max = A[(int)(String[i]) - 97] > current_max ? A[(int)(String[i]) - 97] : current_max;
        //printf("%d ", A[(int)(String[i]) - 97]); DEBUGGING
        //printf("%d\n", current_max);
    }

    for (int i = current_max; i > 0; i--) { // Goes from the maximum of occurences to display them first
        for (int j = 0; j < 26; j++) {
            if (A[j] == i) {
                printf("%c ", (char)(j + 97));
                for (int dot = 0; dot < i; dot++) {
                    printf(".");
                }
                printf("\n");
            }
        }
    }
    return 0;
}

bool found = false;
int attempts = 0;

int brute_force (char *pass) {
    int len = strlen(pass) - 1;

    // FIRST GIGAATTEMPT
    for (int c1 = 32; c1 <= 126; c1++) {
        attempts += 1;
        if (pass[0] == (char)(c1) && len == 1) { // WITHOUT len == 1 IT WONT WORK BECAUSE IT WILL SKIP OTHER STEPS
            found = true;
            break;
        }
    }

    if (found) {
        return 1;
    }

    // SECOND GIGAATTEMPT
    for (int c1 = 32; c1 <= 126; c1++) {
        for (int c2 = 32; c2 <= 126; c2++) {
            attempts += 1;
            if (pass[0] == (char)(c1) && pass[1] == (char)(c2) && len == 2) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (found) {
        return 1;
    }

    // THIRD GIGAATTEMPT
    for (int c1 = 32; c1 <= 126; c1++) {
        for (int c2 = 32; c2 <= 126; c2++) {
            for (int c3 = 32; c3 <= 126; c3++) {
                attempts += 1;
                // NO len == 3 IN THE CONDITION BECAUSE IF len = 1 or len = 2 ITS TOO LATE, THEY DIDNT PASS THE PREVIOUS CHECKS
                if (pass[0] == (char)(c1) && pass[1] == (char)(c2) && pass[2] == (char)(c3)) {
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        if (found) {
            break;
        }
    }
    
    if (found) {
        return 1;
    } else {
        return 0;
    }
}


/* EXERCISE 3 */
int main () {
    char password[10];

    printf("Input your password:\n");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("I don't like your password.");
        return 1;   
    };

    int len = strlen(password) - 1;
    if (len > 3) {
        printf("I don't like your password.");
        return 1;   
    };

    bool result = brute_force(password);

    if (result) {
        printf("Found! It's %s", password);
        printf("Number of attempts: %d\n", attempts);
    } else {
        printf("I like your password.\n");
    }

    return 0;
}