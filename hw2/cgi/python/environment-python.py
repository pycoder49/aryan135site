#!/usr/bin/env python3
import os

print("Cache-Control: no-cache")
print("Content-Type: text/html\n")

print("""
<!DOCTYPE html>
<html>
      <head>
            <title>Python Environment Variables</title>
      </head>

      <body>
            <h1 align="center">Python Environment Variables</h1>
            <hr/>
""")

for key in sorted(os.environ.keys()):
    print(f"<b>{key}:</b> {os.environ.get(key, '')}<br/>")

print("</body></html>")
