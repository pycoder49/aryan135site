#include <bits/stdc++.h>
using namespace std;

static string html_escape(const string s){
    string result;
    result.reserve(s.size());
    for(char character : s){
        switch(character){
            case '&':  result.append("&amp;");  break;
            case '"': result.append("&quot;"); break;
            case '\'': result.append("&#39;");  break;
            case '<':  result.append("&lt;");   break;
            case '>':  result.append("&gt;");   break;
            default:   result.push_back(character); break;
        }
    }
    return result;
}

static string env_or(const char* key, const string& default_value) {
    const char* value = getenv(key);
    return value ? string(value) : default_value;
}

static string now_string(){
    time_t now = time(nullptr);
    string s = ctime(&now);
    while(!s.empty() && (s.back() == '\n' || s.back() == '\r')){
        s.pop_back();
    }
    return s;
}

int main(){
    string ip = env_or("REMOTE_ADDR", "unknown");

    cout << "Cache-Control: no-cache\r\n";
    cout << "Content-Type: text/html\r\n\r\n";

    cout << "<!DOCTYPE html><html><head><title>Hello CGI World</title></head><body>";
    cout << "<h1 align='center'>Hello HTML C++ World</h1><hr/>";
    cout << "<p>Hello Team Aryan! :D</p>";
    cout << "<p>This page was generated with the C++ programming language</p>";
    cout << "<p>This program was generated at: " << html_escape(now_string()) << "</p>";
    cout << "<p>Your current IP Address is: " << html_escape(ip) << "</p>";
    cout << "</body></html>";
    return 0;
}
