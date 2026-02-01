#!/usr/bin/env python3
from datetime import datetime
import json
import os

print("Cache-Control: no-cache")
print("Content-Type: application/json\n")

ip = os.environ.get("REMOTE_ADDR", "Unknown IP")

data = {
    "title": "Hello Aryan's CGI World",
    "heading": "Hello Aryan's Python JSON World",
    "message": "Hello Team Aryan :D, this page was generated with the Python programming language.",
    "ip_address": ip,
    "current_datetime": str(datetime.now())
}

print(json.dumps(data, indent=4))
