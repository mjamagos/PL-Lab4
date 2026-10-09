import java.time.Duration;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.Scanner;

public class Procrastinator {

    private static final Scanner scanner = new Scanner(System.in);

    private static final DateTimeFormatter FORMATTER =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    public static int getAssignmentCount() {
        while (true) {
            System.out.print("How many assignments do you have? ");

            try {
                int count = Integer.parseInt(scanner.nextLine());

                if (count <= 0) {
                    System.out.println(
                            "You need at least one assignment. Nice try!"
                    );
                    continue;
                }

                return count;

            } catch (NumberFormatException e) {
                System.out.println(
                        "Invalid input. Please enter a whole number."
                );
            }
        }
    }

    public static LocalDateTime getDeadline() {
        while (true) {
            System.out.print(
                    "Enter your deadline (YYYY-MM-DD HH:MM): "
            );

            String input = scanner.nextLine();

            try {
                return LocalDateTime.parse(input, FORMATTER);

            } catch (DateTimeParseException e) {
                System.out.println(
                        "Invalid date or format. "
                        + "Example: 2026-10-12 23:59"
                );
            }
        }
    }

    public static String getMessage(double hoursPerAssignment) {
        if (hoursPerAssignment >= 24) {
            return "Look at you, being responsible for once.";
        } else if (hoursPerAssignment >= 12) {
            return "Plenty of time. Surely nothing can go wrong.";
        } else if (hoursPerAssignment >= 6) {
            return "Okay, maybe stop scrolling now.";
        } else if (hoursPerAssignment >= 2) {
            return "Academic weapon mode: ACTIVATED.";
        } else {
            return "You and God are the only ones "
                    + "who know what happens next.";
        }
    }

    public static void main(String[] args) {
        System.out.println("=============================================");
        System.out.println("                 PROCRASTINATOR");
        System.out.println("=============================================");

        int assignmentCount = getAssignmentCount();
        LocalDateTime deadline = getDeadline();

        // Get the computer's current local date and time.
        LocalDateTime currentTime = LocalDateTime.now();

        // Calculate the time remaining until the deadline.
        Duration remainingTime = Duration.between(
                currentTime, deadline
        );

        double remainingHours =
                remainingTime.toSeconds() / 3600.0;

        System.out.println("\n---------------------------------------------");
        System.out.println("                  YOUR RESULTS");
        System.out.println("---------------------------------------------");

        System.out.println(
                "Current time: "
                + currentTime.format(FORMATTER)
        );

        System.out.println(
                "Deadline:     "
                + deadline.format(FORMATTER)
        );

        System.out.println("Assignments:  " + assignmentCount);

        if (remainingHours <= 0) {
            System.out.println("\nYour deadline has already passed.");
            System.out.println(
                    "Congratulations! You have unlocked academic regret."
            );
            System.out.println(
                    "Next time, perhaps start before the deadline."
            );
            System.out.println("---------------------------------------------");
            scanner.close();
            return;
        }

        double hoursPerAssignment =
                remainingHours / assignmentCount;

        System.out.printf(
                "%nTime remaining: %.2f hours%n",
                remainingHours
        );

        System.out.printf(
                "Time per assignment: %.2f hours%n",
                hoursPerAssignment
        );

        System.out.println("\n" + getMessage(hoursPerAssignment));
        System.out.println("---------------------------------------------");

        scanner.close();
    }
}
