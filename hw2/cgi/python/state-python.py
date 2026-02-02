#!/usr/bin/env python3
from urllib.parse import parse_qs
import uuid
import json
import sys
import os

# configurations
cookie = "CGISESSID"
session_dir = "/tmp/cse135-sessions-python"
base_url = "/hw2/cgi/python/state-python.py"
os.makedirs(session_dir, exist_ok=True)

# parsing the cookie
def parse_cookie(cookie_header) -> dict:
    cookies = {}
    if not cookie_header:
        return cookies
    
    for part in cookie_header.split(";"):
        part = part.strip()
        if "=" in part:
            key, value = part.split("=", 1)
            cookies[key] = value
    
    return cookies

# getting session id
def get_session_id() -> str:
    cookies = parse_cookie(os.environ.get("HTTP_COOKIE", ""))
    session_id = cookies.get(cookie)
    if session_id and session_id.replace("-", "").isalnum():
        return session_id
    return str(uuid.uuid4())

# loading the session
def load_session(session_id) -> dict:
    path = os.path.join(session_dir, f"session_{session_id}.json")
    if not os.path.exists(path): return{"items": []}

    try:
        with open(path, "r") as file:
            data = json.load(file)
        
        if "items" not in data or not isinstance(data["items"], list):
            data["items"] = []
        
        return data
    except Exception:
        return {"items": []}

# saving session
def save_session(session_id, data) -> None:
    path = os.path.join(session_dir, f"session_{session_id}.json")
    with open(path, "w") as file:
        json.dump(data, file)

# reading post data
def read_post_data() -> str:
    try:
        content_length = int(os.environ.get("CONTENT_LENGTH", "0") or 0)
    except ValueError:
        content_length = 0
    body = sys.stdin.read(content_length) if content_length > 0 else ""
    return parse_qs(body, keep_blank_values=True)

# html escape
def html_escape(s: str) -> str:
    return (s.replace("&", "&amp;")
             .replace("<", "&lt;")
             .replace(">", "&gt;")
             .replace('"', "&quot;")
             .replace("'", "&#39;"))

# getting request info
session_id = get_session_id()
method = os.environ.get("REQUEST_METHOD", "")
query_string = parse_qs(os.environ.get("QUERY_STRING", ""), keep_blank_values=True)
page = (query_string.get("page", ["form"])[0] or "form").lower()

# loading in the session
session = load_session(session_id)

todo = None
if method == "POST":
    post = read_post_data()
    todo = (post.get("action", [""])[0] or "").lower()

    if todo == "save":
        value = (post.get("value", [""])[0] or "").strip()
        if value:
            session["items"].append(value)
            save_session(session_id, session)
        page = "view"
    elif todo == "clear":
        session["items"] = []
        save_session(session_id, session)
        page = "view"

# output headers
print("Cache-Control: no-cache")
print("Content-Type: text/html")
print(f"Set-Cookie: {cookie}={session_id}; Path=/; SameSite=Lax")
print()

# html code
print("<!DOCTYPE html>")
print("<html><head><title>State Demo (Python)</title></head><body>")
print("<h1 align='center'>State Demo (Python)</h1><hr/>")

print(f"<p><a href='{base_url}?page=form'>Form Page</a> | ")
print(f"<a href='{base_url}?page=view'>View Page</a></p>")

if page == "form":
    print("<h2>Enter data to save data on the server side</h2>")
    print(f"<form method='POST' action='{base_url}?page=form'>")
    print("    <label for='value'>Value:</label>")
    print("    <input id='value' name='value' type='text' />")
    print("    <input type='hidden' name='action' value='save' />")
    print("    <button type='submit'>Save</button></form>")
    print("<p>After saving, you will be taken to the View Page to see saved values.</p>")
elif page == "view":
    print("<h2>Saved values</h2>")
    if session["items"]:
        print("<ul>")
        for item in session["items"]:
            print(f"<li>{html_escape(item)}</li>")
        print("</ul>")
    else:
        print("<p>(No saved data yet!!)</p>")

    print(f"""
        <form method="POST" action="{base_url}?page=view" style="margin-top: 20px;">
            <input type="hidden" name="action" value="clear" />
            <button type="submit">Clear Saved Data</button>
        </form>
    """)

print("<hr>")
print(f"<p><b>Session cookie:</b> {cookie} (server stores data in /tmp)</p>")
print("</body></html>")