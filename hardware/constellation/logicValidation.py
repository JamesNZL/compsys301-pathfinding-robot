from enum import Enum

BOOLEANS = [
    False,
    True,
]


class Actions(Enum):
    CONTINUE_PREVIOUS = 0
    CONTINUE_FORWARD = 1
    CORRECT_LEFT = 2
    CORRECT_RIGHT = 3
    DETERMINE_SKEW_OR_TURN_ABOUT = 4
    FIND_VALID_STATE = 5


ACTION_DESCRIPTIONS = [
    "Continue previous action",
    "Continue forward",
    "Correct left",
    "Correct right",
    "Rotate left and right to see if just skewed or whether turn around",
    "Rotate left and right to acquire valid state",
]

# Use an enum here so this lookup only has to be a uint8_t[128]
ACTIONS_LOOKUP = [
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.FIND_VALID_STATE,
    Actions.FIND_VALID_STATE,
    Actions.FIND_VALID_STATE,
    Actions.FIND_VALID_STATE,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CONTINUE_FORWARD,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CORRECT_LEFT,
    Actions.CONTINUE_FORWARD,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CONTINUE_PREVIOUS,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CORRECT_RIGHT,
    Actions.CONTINUE_FORWARD,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.DETERMINE_SKEW_OR_TURN_ABOUT,
    Actions.FIND_VALID_STATE,
    Actions.FIND_VALID_STATE,
    Actions.FIND_VALID_STATE,
    Actions.FIND_VALID_STATE,
]


def determine_action(
    middle, front_left, front_right, rear_left, rear_right, left, right
):
    bitfield = (
        (middle << 6)
        | (front_left << 5)
        | (front_right << 4)
        | (rear_left << 3)
        | (rear_right << 2)
        | (left << 1)
        | (right)
    )

    return ACTIONS_LOOKUP[bitfield]


def main():
    print(
        "Middle\t\tFront Left\tFront Right\tRear Left\tRear Right\tLeft\t\tRight\t\tAction"
    )
    print(
        "----------------------------------------------------------------------------------------------------------------------------------------"
    )

    for middle in BOOLEANS:
        for front_left in BOOLEANS:
            for front_right in BOOLEANS:
                for rear_left in BOOLEANS:
                    for rear_right in BOOLEANS:
                        for left in BOOLEANS:
                            for right in BOOLEANS:
                                action = determine_action(
                                    middle,
                                    front_left,
                                    front_right,
                                    rear_left,
                                    rear_right,
                                    left,
                                    right,
                                )

                                print(
                                    f"{middle}\t\t{front_left}\t\t{front_right}\t\t{rear_left}\t\t{rear_right}\t\t{left}\t\t{right}\t\t{ACTION_DESCRIPTIONS[action.value]}"
                                )


if __name__ == "__main__":
    main()
