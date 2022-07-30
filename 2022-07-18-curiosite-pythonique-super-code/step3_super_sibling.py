#!/usr/bin/env python3

import datetime


class BaseLogger:
    def log(self, msg: str):
        print(msg)


class TimestampLogger(BaseLogger):
    def log(self, msg: str):
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        timestamped_msg = f"{timestamp} {msg}"
        super().log(timestamped_msg)


class UpperLogger(BaseLogger):
    def log(self, msg: str):
        uppercase_msg = msg.upper()
        super().log(uppercase_msg)


class TimestampUpperLogger(TimestampLogger, UpperLogger):
    def log(self, msg: str):
        super().log(msg)


logger = TimestampUpperLogger()
logger.log("Pouet")  # <-- que fait TimestampLogger.log ?

print(" ".join(klass.__name__ for klass in TimestampUpperLogger.__mro__))

super(TimestampLogger, logger).log("pouet")
