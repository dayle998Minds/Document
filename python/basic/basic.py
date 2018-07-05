#!/usr/bin/python3

import logging


logging.basicConfig(level=logging.DEBUG, format="%(asctime)-15s [%(threadName)s] %(message)s")


class Basic:
    def __init__(self, name):
        self.name = name

    def call(self):
        logging.debug("call")


def main():
    logging.debug("start")
    basic = Basic("name")
    basic.call()


if __name__ == "__main__":
    main()
