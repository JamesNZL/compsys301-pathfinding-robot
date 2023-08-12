BOOLEANS = [
    False,
    True,
]


def determine_action(
    middle, front_left, front_right, rear_left, rear_right, left, right
):
    if (
        (
            not middle
            and not front_left
            and not front_right
            and not rear_left
            and not rear_right
        )
        or (
            not middle
            and front_left
            and front_right
            and not rear_left
            and not rear_right
        )
        or (
            middle
            and not front_left
            and front_right
            and rear_left
            and rear_right
            and left
            and right
        )
        or (
            middle
            and front_left
            and not front_right
            and rear_left
            and rear_right
            and left
            and right
        )
        or (not front_left and not front_right and rear_left and rear_right)
    ):
        return "Continue forward"

    if (
        (
            middle
            and not front_left
            and not front_right
            and not rear_left
            and not rear_right
        )
        or (middle and not front_left and front_right and rear_left and not rear_right)
        or (middle and front_left and not front_right and not rear_left and rear_right)
    ):
        return "Continue previous action"

    if (
        (not front_left and front_right and not rear_left and not rear_right)
        or (not front_left and not rear_left and rear_right)
        or (not middle and not front_left and front_right and rear_left)
        or (not middle and front_left and front_right and not rear_left and rear_right)
        or (
            middle
            and not front_left
            and front_right
            and rear_left
            and rear_right
            and not left
        )
        or (
            middle
            and not front_left
            and front_right
            and rear_left
            and rear_right
            and left
            and not right
        )
    ):
        return "Correct left"

    if (
        (front_left and not front_right and not rear_left and not rear_right)
        or (not middle and front_left and front_right and rear_left and not rear_right)
        or (not front_right and rear_left and not rear_right)
        or (not middle and front_left and not front_right and rear_right)
        or (
            middle
            and front_left
            and not front_right
            and rear_left
            and rear_right
            and not left
        )
        or (
            middle
            and front_left
            and not front_right
            and rear_left
            and rear_right
            and left
            and not right
        )
    ):
        return "Correct right"

    if (middle and front_left and front_right and rear_left and not rear_right) or (
        middle and front_left and front_right and not rear_left
    ):
        return "Rotate left and right to see if just skewed or whether turn around"

    if front_left and front_right and rear_left and rear_right:
        return "Rotate left and right to acquire valid state"

    print(
        f"\nERROR:\n{middle}\t{front_left}\t{front_right}\t{rear_left}\t{rear_right}\t{left}\t{right}\n"
    )
    raise Exception("No case matched!")


def main():
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
                                    f"{middle}\t{front_left}\t{front_right}\t{rear_left}\t{rear_right}\t{left}\t{right}:\t{action}"
                                )


if __name__ == "__main__":
    main()
