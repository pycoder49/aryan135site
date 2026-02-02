#!/usr/bin/env python3
from urllib.parse import parse_qs
from datetime import datetime
import json
import sys
import os

# reading the request info here
method = os.environ.get("REQUEST_METHOD", "")
content_type = os.environ.get("CONTENT_TYPE", "")
query_string = os.environ.get("QUERY_STRING", "")
user_agent = os.environ.get("HTTP_USER_AGENT", "")
ip = os.environ.get("REMOTE_ADDR", "")

# reaading the body if passed in
try:
    content_length = int(os.environ.get("CONTENT_LENGTH", 0))
except:
    content_length = 0
body = sys.stdin.read(content_length) if content_length > 0 else ""

# parsing the parameters
params = {}

if method == "GET" or method == "DELETE":
    parsed_params = parse_qs(query_string, keep_blank_values=True)
    for key in parsed_params:
        params[key] = parsed_params[key]
elif "application/json" in content_type:
    try:
        json_data = json.loads(body) if body else {}
        for key, value in json_data.items():
            params[key] = [str(value)]
    except:
        params["error"] = ["Invalid JSON"]
else: # for form-urlencoded
    parsed_params = parse_qs(body, keep_blank_values=True)
    for key in parsed_params:
        params[key] = parsed_params[key][-1]

# putting in the html code below
print("Cache-Control: no-cache")
print("Content-Type: text/html\n")

print("<!DOCTYPE html>")
print("<html><head><title>Echo Python</title></head><body>")
print("<h1 align='center'>Echo Python</h1><hr/>")

# putting in the variables
print(f"<p><b>Method: </b> {method}</p>")
print(f"<p><b>Content-Type: </b> {content_type if content_type else 'N/A'}</p>")
print(f"<p><b>Query String: </b> {query_string if query_string else 'N/A'}</p>")
print(f"<p><b>User-Agent: </b> {user_agent if user_agent else 'N/A'}</p>")
print(f"<p><b>IP Address: </b> {ip if ip else 'N/A'}</p>")
print(f"<p><b>Timestamp: </b> {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}</p>")

print("<h2>Raw Body</h2>")
print(f"<pre>{body}</pre>")

print("<h2>Parsed Parameters</h2>")
if params:
    print("<ul>")
    for key in sorted(params.keys()):
        print(f"<li><b>{key}:</b> = {params[key]}</li>")
    print("</ul>")
else:
    print("<p>No parameters found.</p>")

# closing html tags from above
print("</body></html>")
