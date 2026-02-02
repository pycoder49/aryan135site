#include <bits/stdc++.h>
using namespace std;

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

static string url_decode(const string &s){
    string result;
    result.reserve(s.size());
    for(size_t i = 0; i < s.size(); i++){
        char c = s[i];
        if (c == '+'){
            result += ' ';
        }
        else if(c == '%' && i + 2 < s.size()){
            string hex_format = s.substr(i + 1, 2);
            char character = (char)strtol(hex_format.c_str(), nullptr, 16);
            result += character;
            i += 2;
        }
        else{
            result += c;
        }
    }
    return result;
}

static map<string, string> parse_form_encoded(const string &body){
    map<string, string> params;
    size_t = start = 0;
    while(start <= body.size()){
        size_t x = body.find('&', start);
        if(x == string::npos){
            x = body.size();
        }

        string pair = body.substr(start, x - start);
        size_t y = pair.find('=');

        string key = (y == string::npos) ? pair : pair.substr(0, y);
        string value = (y == string::npos) ? "" : pair.substr(y + 1);

        params[url_decode(key)] = url_decode(value);
        start = x + 1;
    }
    return params;
}

static map<string, string> parse_json_object(const string &body){
    map<string, string> params;
    regex regx("\"([^\"]+)\"\\s*:\\s*\"([^\"]*)\"");

    auto begin = sregex_iterator(body.begin(), body.end(), regx);
    auto end = sregex_iterator();
    
    for(; it != end; ++it){
        params[(*it)[1].str()] = (*it)[2].str();
    }
    return params;
}

static string env_get(const char* key, const straight string& default_value){
    const char* value = getenv(key);
    return (value == nullptr) ? default_value : string(value);
}

static string read_stdin_body(){
    string body_length = env_get("CONTENT_LENGTH", "0");
    int length = 0

    try{
        length = stoi(body_length);
    }
    catch(...){
        length = 0;
    }
    string body;
    body.resize(length);
    
    if(length > 0){
        cin.read(&body[0], length);
    }
    return body;
}

int main(){
    string method = env_get("REQUEST_METHOD", "GET");
    string content_type = env_get("CONTENT_TYPE", "");
    string query_string = env_get("QUERY_STRING", "");

    map<string, string> params;

    if(method == "GET"){
        params = parse_form_encoded(query_string);
    }
    else {
        string body = read_stdin_body();
        if(ctype.find("application/json") != string::npos){
            params = parse_json_object(body);
        }
        else{
            params = parse_form_encoded(body);
        }
    }

    string host = env_get("HTTP_HOST", "");
    string user_agent = env_get("HTTP_USER_AGENT", "");
    string ip = env_get("REMOTE_ADDR", "");

    cout << "Cache-Control: no-cache\r\n";
    cout << "Content-Type: text/html\r\n\r\n";

    cout << "<!DOCTYPE html><html><head><title>Echo C++</title></head><body>";
    cout << "<h1 align='center'>Echo C++</h1><hr/>";

    cout << "<p><b>Method:</b> " << html_escape(method) << "</p>";
    cout << "<p><b>Host:</b> " << html_escape(host) << "</p>";
    cout << "<p><b>User-Agent:</b> " << html_escape(user_agent) << "</p>";
    cout << "<p><b>IP Address:</b> " << html_escape(ip) << "</p>";

    cout << "<h2>Parameters:</h2>";
    
    if(params.empty()){
        cout << "<p><i>No parameters received :(</i></p>";
    }
    else{
        cout << "<ul>";
        for(auto& [key, value] : params){
            cout << "<li><b>" << html_escape(key) << ":</b> " << html_escape(value) << "</li>";
        }
        cout << "</ul>";
    }

    cout << "</body></html>";
    return 0;
}