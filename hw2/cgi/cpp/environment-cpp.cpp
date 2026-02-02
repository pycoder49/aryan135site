#include <bits/stdc++.h>
using namespace std;

extern char **environ;

static string html_escape(const string &s) {
    stringstream escaped;
    for (char c : s) {
        switch (c) {
            case '&':  escaped << "&amp;";  break;
            case '<':  escaped << "&lt;";   break;
            case '>':  escaped << "&gt;";   break;
            case '"':  escaped << "&quot;"; break;
            case '\'': escaped << "&#39;";  break;
            default:   escaped << c;        break;
        }
    }
    return escaped.str();
}

int main(){
    cout << "Cache-Control: no-cache\r\n";
    cout << "Content-Type: text/html\r\n\r\n";

    cout << "<!DOCTYPE html><html><head><title>Environment Variables</title></head><body>";
    cout << "<h1 align=\"center\">Environment Variables in C++ YEAH</h1>";
    cout << "<table border='1' cellpadding='5' cellspacing='0'>";
    cout << "<tr><th>Variables</th><th>Values</th></tr>";

    for(char **env = environ; *env; env++){
        string line(*env);
        auto position = line.find('=');
        string key = (poisition == string::npos) ? line : line.substr(0, position);
        string value = (position == string::npos) ? "" : line.substr(position + 1);
        cout << "<tr><td>" << html_escape(key) << "</td><td>" << html_escape(value) << "</td></tr>";
    }

    cout << "</table></body></html>";
    return 0;
}
