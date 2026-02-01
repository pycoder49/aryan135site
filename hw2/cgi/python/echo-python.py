#!/usr/bin/env python3
from urllib.parse import parse_qs
import os

print("Cache-Control: no-cache")
print("Content-Type: text/html\n")

print("""
<!DOCTYPE html>
<html>
    <head>
        <title>GET Request Echo</title>
    </head>
    <body>
        <h1 align="center">Get Request Echo</h1>
        <hr>
""")

query_string = os.environ.get("QUERY_STRING", "")
print(f"<b>Query String:</b> {query_string}<br />\n")

params = parse_qs(query_string, keep_blank_values=True)

for key in sorted(params.keys()):
    for value in params[key]:
        print(f"{key}: {value}<br />\n")

print("</body></html>")

