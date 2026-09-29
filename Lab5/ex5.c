#include <stdio.h>
#include <string.h>

typedef enum {
    Student,
    TA,
    Professor
} role;

typedef enum {
    Secondary, Bachelor, Master, PhD
} Degree;

typedef struct {
    char name[20];
    role position;
    Degree degree;
} moodleMember;

const char* role_string[] = {"Student", "TA", "Professor"};
const char* degree_string[] = {"Secondary", "Bachelor", "Master", "PhD"};

role transmuteRole (char *r) {
    if (!strcmp(r, role_string[Student])) {
        return Student;
    } else if (!strcmp(r, role_string[TA])) {
        return TA;
    } else if (!strcmp(r, role_string[Professor])) {
        return Professor;
    }
    return Student;
}

Degree convertDegree (char *r) {
    if (!strcmp(r, degree_string[Secondary])) {
        return Secondary;
    } else if (!strcmp(r, degree_string[Bachelor])) {
        return Bachelor;
    } else if (!strcmp(r, degree_string[Master])) {
        return Master;
    } else if (!strcmp(r, degree_string[PhD])) {
        return PhD;
    }
    return Secondary;
}

int main () {
    int n;

    printf("Enter the amount of moodle members:\n");
    scanf("%d", &n);

    moodleMember List[n];
    for (int i = 0; i < n; i++) {
        char role_buff[12], deg_buff[12];
        printf("Enter member #%d (name position degree):\n", i + 1);
        scanf("%s %s %s", List[i].name, role_buff, deg_buff);
        List[i].position = transmuteRole(role_buff);
        List[i].degree = convertDegree(deg_buff);
    };

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            int swap = (List[j - 1].position < List[j].position) ||
                (List[j - 1].position == List[j].position
                && List[j - 1].degree < List[j].degree);
            if (swap) {
                moodleMember temp = List[j - 1];
                List[j - 1] = List[j];
                List[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i ++) {
        printf("%s %s %s\n",
       List[i].name,
       role_string[List[i].position],
       degree_string[List[i].degree]);
    }
    return 0;
}