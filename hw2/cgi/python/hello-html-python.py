#!/usr/bin/env python3
from datetime import datetime
import os

print("Cache-Control: no-cache")
print("Content-Type: text/html\n")

ip = os.environ.get("REMOTE_ADDR", "Unknown IP")

print(f"""
<!DOCTYPE html>
<html>
        <head>
            <title>Hello Aryan's CGI World</title>
        </head>
      
        <body>
            <h1 align="center">Hello Aryan's Python HTML World</h1><hr/>
            <p>Hello Team Aryan :D</p>
            <p>This page was generated with the Python programming language</p>
            <p>Your IP address is: {ip}</p>
            <p>Current date and time: {datetime.now()}</p>
        </body>
</html>
""")
