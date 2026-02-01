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
}
