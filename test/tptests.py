#!/usr/bin/python3
# -*- coding: utf-8 -*-
"""
    Name: tptests.py
    Description:
        tppy testing
"""

import sys
from pathlib import Path
from subprocess import run

common_args = "--verbose --stats"

test_configs = [
    [
        "--rows",
        "1",
        "--columns",
        "4",
        "--l-right",
        "0",
        "--l-left",
        "0",
        "--step-right",
        "0",
        "--step-left",
        "0",
        "--tee",
        "1",
        "--bar",
        "0",
        "--square",
        "0",
    ],
    [
        "--rows",
        "1",
        "--columns",
        "4",
        "--l-right",
        "0",
        "--l-left",
        "0",
        "--step-right",
        "0",
        "--step-left",
        "0",
        "--tee",
        "0",
        "--bar",
        "1",
        "--square",
        "0",
    ],
    [
        "--rows",
        "2",
        "--columns",
        "2",
        "--l-right",
        "0",
        "--l-left",
        "0",
        "--step-right",
        "0",
        "--step-left",
        "0",
        "--tee",
        "0",
        "--bar",
        "0",
        "--square",
        "1",
    ],
    [
        "--rows",
        "4",
        "--columns",
        "2",
        "--l-right",
        "2",
        "--l-left",
        "0",
        "--step-right",
        "0",
        "--step-left",
        "0",
        "--tee",
        "0",
        "--bar",
        "0",
        "--square",
        "0",
    ],
    [
        "--rows",
        "4",
        "--columns",
        "7",
        "--l-right",
        "1",
        "--l-left",
        "1",
        "--step-right",
        "0",
        "--step-left",
        "2",
        "--tee",
        "2",
        "--bar",
        "1",
        "--square",
        "0",
    ],
    [
        "--first",
        "--rows",
        "4",
        "--columns",
        "7",
        "--l-right",
        "1",
        "--l-left",
        "1",
        "--step-right",
        "0",
        "--step-left",
        "2",
        "--tee",
        "2",
        "--bar",
        "1",
        "--square",
        "0",
    ],
    [
        "--first",
        "--rows",
        "6",
        "--columns",
        "6",
        "--l-right",
        "2",
        "--l-left",
        "2",
        "--step-right",
        "0",
        "--step-left",
        "3",
        "--tee",
        "2",
        "--bar",
        "0",
        "--square",
        "0",
    ],
    [
        "--rows",
        "4",
        "--columns",
        "4",
        "--l-right",
        "0",
        "--l-left",
        "0",
        "--step-right",
        "0",
        "--step-left",
        "0",
        "--tee",
        "0",
        "--bar",
        "4",
        "--square",
        "0",
    ],
]


def main():
    """ Script main function """
    try:
        app = Path("../x64/Debug/talospuzzle.exe").resolve(strict=True)
    except FileNotFoundError:
        print("Fatal: Can't find talospuzzle application.")
        exit(1)
    for config in test_configs:
        command = "\"{}\" {} {}".format(
            app,
            common_args,
            " ".join(config),
        )
        run(command, shell=True)


if __name__ == "__main__":
    main()
