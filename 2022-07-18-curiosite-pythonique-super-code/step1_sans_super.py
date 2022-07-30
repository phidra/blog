#!/usr/bin/env python3

import datetime


class BaseLogger:
    def log(self, msg: str):
        print(msg)


class TimestampLogger(BaseLogger):
    def log(self, msg: str):
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        timestamped_msg = f"{timestamp} {msg}"
        BaseLogger.log(self, timestamped_msg)  # <-- appel explicite à la classe parente


logger = TimestampLogger()
logger.log("Pouet")  # <-- grâce à super(), TimestampLogger.log appelle BaseLogger.log
