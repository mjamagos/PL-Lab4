<?php

date_default_timezone_set('Asia/Manila');

function getAssignmentCount(): int
{
    while (true) {
        echo "How many assignments do you have? ";
        $input = trim(fgets(STDIN));

        if ($input === false || $input === '') {
            echo "Invalid input. Please enter a whole number.\n";
            continue;
        }

        if (!preg_match('/^[+-]?\d+$/', $input)) {
            echo "Invalid input. Please enter a whole number.\n";
            continue;
        }

        $count = filter_var($input, FILTER_VALIDATE_INT);

        if ($count === false) {
            echo "Invalid input. Please enter a valid integer.\n";
            continue;
        }

        if ($count <= 0) {
            echo "You need at least one assignment. Nice try!\n";
            continue;
        }

        return $count;
    }
}

function getDeadline(): DateTime
{
    while (true) {
        echo "Enter your deadline (YYYY-MM-DD HH:MM): ";
        $input = trim(fgets(STDIN));

        $deadline = DateTime::createFromFormat(
            '!Y-m-d H:i',
            $input
        );

        $errors = DateTime::getLastErrors();

        if (
            $deadline === false ||
            ($errors !== false &&
                ($errors['warning_count'] > 0 ||
                 $errors['error_count'] > 0)) ||
            $deadline->format('Y-m-d H:i') !== $input
        ) {
            echo "Invalid date or format. Example: 2026-10-12 23:59\n";
            continue;
        }

        return $deadline;
    }
}

function getMessage(float $hoursPerAssignment): string
{
    if ($hoursPerAssignment >= 24) {
        return "Look at you, being responsible for once.";
    } elseif ($hoursPerAssignment >= 12) {
        return "Plenty of time. Surely nothing can go wrong.";
    } elseif ($hoursPerAssignment >= 6) {
        return "Okay, maybe stop scrolling now.";
    } elseif ($hoursPerAssignment >= 2) {
        return "Academic weapon mode: ACTIVATED.";
    } else {
        return "You and God are the only ones who know what happens next.";
    }
}

function main(): void
{
    echo "=============================================\n";
    echo "                 PROCRASTINATOR\n";
    echo "=============================================\n";

    $assignmentCount = getAssignmentCount();
    $deadline = getDeadline();

    // Automatically get the computer's current local date and time.
    $currentTime = new DateTime();

    // Calculate the time remaining until the deadline.
    $remainingSeconds =
        $deadline->getTimestamp() - $currentTime->getTimestamp();

    $remainingHours = $remainingSeconds / 3600;

    echo "\n---------------------------------------------\n";
    echo "                  YOUR RESULTS\n";
    echo "---------------------------------------------\n";

    echo "Current time: " . $currentTime->format('Y-m-d H:i') . "\n";
    echo "Deadline:     " . $deadline->format('Y-m-d H:i') . "\n";
    echo "Assignments:  " . $assignmentCount . "\n";

    if ($remainingHours <= 0) {
        echo "\nYour deadline has already passed.\n";
        echo "Congratulations! You have unlocked academic regret.\n";
        echo "Next time, perhaps start before the deadline.\n";
        echo "---------------------------------------------\n";
        return;
    }

    $hoursPerAssignment = $remainingHours / $assignmentCount;

    printf("\nTime remaining: %.2f hours\n", $remainingHours);
    printf("Time per assignment: %.2f hours\n", $hoursPerAssignment);

    echo "\n" . getMessage($hoursPerAssignment) . "\n";
    echo "---------------------------------------------\n";
}

main();
