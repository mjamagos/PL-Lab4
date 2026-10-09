from datetime import datetime


def get_assignment_count():
    while True:
        try:
            count = int(input("How many assignments do you have? "))

            if count <= 0:
                print("You need at least one assignment. Nice try!")
                continue
            return count
        
        except ValueError:
            print("Invalid input. Please enter a whole number.")


def get_deadline():
    while True:
        deadline_input = input(
            "Enter your deadline (YYYY-MM-DD HH:MM): "
        )

        try:
            deadline = datetime.strptime(
                deadline_input, "%Y-%m-%d %H:%M"
            )
            return deadline

        except ValueError:
            print(
                "Invalid date or format. "
                "Example: 2026-10-12 23:59"
            )


def get_message(hours_per_assignment):
    if hours_per_assignment >= 24:
        return "Look at you, being responsible for once."
    elif hours_per_assignment >= 12:
        return "Plenty of time. Surely nothing can go wrong."
    elif hours_per_assignment >= 6:
        return "Okay, maybe stop scrolling now."
    elif hours_per_assignment >= 2:
        return "Academic weapon mode: ACTIVATED."
    else:
        return (
            "You and God are the only ones "
            "who know what happens next."
        )


def main():
    print("=" * 45)
    print("              PROCRASTINATOR")
    print("=" * 45)

    assignment_count = get_assignment_count()
    deadline = get_deadline()

    # Get the computer's current local date and time.
    current_time = datetime.now()

    # Calculate the time remaining until the deadline.
    remaining_time = deadline - current_time
    remaining_hours = remaining_time.total_seconds() / 3600

    print("\n" + "-" * 45)
    print("                 YOUR RESULTS")
    print("-" * 45)

    print(
        f"Current time: {current_time.strftime('%Y-%m-%d %H:%M')}"
    )
    print(
        f"Deadline:     {deadline.strftime('%Y-%m-%d %H:%M')}"
    )
    print(f"Assignments:  {assignment_count}")

    if remaining_hours <= 0:
        print("\nYour deadline has already passed.")
        print("Next time, perhaps start before the deadline.")
        print("-" * 45)
        return

    hours_per_assignment = remaining_hours / assignment_count

    print(f"\nTime remaining: {remaining_hours:.2f} hours")
    print(
        f"Time per assignment: {hours_per_assignment:.2f} hours"
    )

    print("\n" + get_message(hours_per_assignment))
    print("-" * 45)


if __name__ == "__main__":
    main()