#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define INPUT_SIZE 100

int getAssignmentCount(void) {
    char input[INPUT_SIZE];
    char extra;
    int count;

    while (1) {
        printf("How many assignments do you have? ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nInput ended unexpectedly.\n");
            exit(EXIT_FAILURE);
        }

        if (sscanf(input, " %d %c", &count, &extra) != 1) {
            printf("Invalid input. Please enter a whole number.\n");
            continue;
        }

        if (count <= 0) {
            printf("You need at least one assignment. Nice try!\n");
            continue;
        }

        return count;
    }
}

struct tm getDeadline(void) {
    char input[INPUT_SIZE];
    struct tm deadline;
    int year, month, day, hour, minute;
    char extra;

    while (1) {
        printf("Enter your deadline (YYYY-MM-DD HH:MM): ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nInput ended unexpectedly.\n");
            exit(EXIT_FAILURE);
        }

        if (sscanf(input, "%4d-%2d-%2d %2d:%2d %c",
                   &year, &month, &day, &hour, &minute, &extra) != 5) {
            printf("Invalid date or format. Example: 2026-10-12 23:59\n");
            continue;
        }

        if (month < 1 || month > 12 ||
            day < 1 || day > 31 ||
            hour < 0 || hour > 23 ||
            minute < 0 || minute > 59) {
            printf("Invalid date or time. Please try again.\n");
            continue;
        }

        memset(&deadline, 0, sizeof(deadline));

        deadline.tm_year = year - 1900;
        deadline.tm_mon = month - 1;
        deadline.tm_mday = day;
        deadline.tm_hour = hour;
        deadline.tm_min = minute;
        deadline.tm_sec = 0;
        deadline.tm_isdst = -1;

        /*
         * mktime normalizes invalid calendar dates.
         * Check the normalized values to reject dates like February 31.
         */
        struct tm original = deadline;
        time_t deadlineTimestamp = mktime(&deadline);

        if (deadlineTimestamp == (time_t)-1 ||
            deadline.tm_year != original.tm_year ||
            deadline.tm_mon != original.tm_mon ||
            deadline.tm_mday != original.tm_mday ||
            deadline.tm_hour != original.tm_hour ||
            deadline.tm_min != original.tm_min) {
            printf("That date does not exist. Please try again.\n");
            continue;
        }

        return deadline;
    }
}

const char *getMessage(double hoursPerAssignment) {
    if (hoursPerAssignment >= 24) {
        return "Look at you, being responsible for once.";
    } else if (hoursPerAssignment >= 12) {
        return "Plenty of time. Surely nothing can go wrong.";
    } else if (hoursPerAssignment >= 6) {
        return "Okay, maybe stop scrolling now.";
    } else if (hoursPerAssignment >= 2) {
        return "Academic weapon mode: ACTIVATED.";
    } else {
        return "You and God are the only ones who know what happens next.";
    }
}

int main(void) {
    printf("=============================================\n");
    printf("                 PROCRASTINATOR\n");
    printf("=============================================\n");

    int assignmentCount = getAssignmentCount();
    struct tm deadline = getDeadline();

    /* Convert the deadline to a timestamp. */
    time_t deadlineTimestamp = mktime(&deadline);

    /* Automatically get the computer's current local time. */
    time_t currentTimestamp = time(NULL);

    struct tm *currentTimeInfo = localtime(&currentTimestamp);

    if (currentTimeInfo == NULL) {
        printf("Unable to read the current local time.\n");
        return EXIT_FAILURE;
    }

    struct tm currentTime = *currentTimeInfo;

    /* Calculate the time remaining in seconds, then convert to hours. */
    double remainingSeconds = difftime(
        deadlineTimestamp, currentTimestamp
    );

    double remainingHours = remainingSeconds / 3600.0;

    printf("\n---------------------------------------------\n");
    printf("                  YOUR RESULTS\n");
    printf("---------------------------------------------\n");

    printf("Current time: %04d-%02d-%02d %02d:%02d\n",
           currentTime.tm_year + 1900,
           currentTime.tm_mon + 1,
           currentTime.tm_mday,
           currentTime.tm_hour,
           currentTime.tm_min);

    printf("Deadline:     %04d-%02d-%02d %02d:%02d\n",
           deadline.tm_year + 1900,
           deadline.tm_mon + 1,
           deadline.tm_mday,
           deadline.tm_hour,
           deadline.tm_min);

    printf("Assignments:  %d\n", assignmentCount);

    if (remainingHours <= 0) {
        printf("\nYour deadline has already passed.\n");
        printf("Congratulations! You have unlocked academic regret.\n");
        printf("Next time, perhaps start before the deadline.\n");
        printf("---------------------------------------------\n");
        return EXIT_SUCCESS;
    }

    double hoursPerAssignment =
        remainingHours / assignmentCount;

    printf("\nTime remaining: %.2f hours\n", remainingHours);
    printf("Time per assignment: %.2f hours\n",
           hoursPerAssignment);

    printf("\n%s\n", getMessage(hoursPerAssignment));
    printf("---------------------------------------------\n");

    return EXIT_SUCCESS;
}
