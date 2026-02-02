#include <bits/stdc++.h>
using namespace std;

extern string cookie = "CGISESSID";
extern string session_dir = "/tmp/cse135-sessions-cpp/";
extern string base_url = "/hw2/cgi/cpp/state-cpp.cgi";

static string html_escape(const string& data){
    string result;
    for(char c : data){
        switch(c){
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default: result += c; break;
        }
    }
    return result;
}

static string env_get(const char* key, const string& default_value){
    const char* value = getenv(key);
    return value ? string(value) : default_value;
}

static string url_decode(const string& s){
    string result;
    result.reserve(s.size());
    for(size_t i = 0; i < s.size(); ++i){
        if(s[i] == '+'){
            result += ' ';
        } else if(s[i] == '%' && i + 2 < s.size()){
            string hex = s.substr(i + 1, 2);
            char decoded_char = static_cast<char>(strtol(hex.c_str(), nullptr, 16));
            result += decoded_char;
            i += 2;
        } else{
            result += s[i];
        }
    }
    return result;
}

static map<string, string> parse_form_encoded(const string& body){
    map<string, string> params;
    size_t start = 0;
    while (start <= body.size()){
        size_t x = body.find("&", start);
        if(x == string::npos) x = body.size();

        string pair = body.substr(start, x - start);
        size_t y = pair.find("=");

        string key = (y == string::npos) ? pair : pair.substr(0, y);
        string value = (y == string::npos) ? "" : pair.substr(y + 1);

        params[url_decode(key)] = url_decode(value);
        start = x + 1;
    }
    return params;
}

static string read_stdin_body(){
    string content_length = env_get("CONTENT_LENGTH", "0");
    int len = 0;

    try{
        length = stoi(content_length);
    }
    catch(...){
        len = 0;
    }
    string body;

    body.resize(max(0, lenght))
    if(length > 0){
        cin.read(&body[0], length);
    }

    return body;
}

static map<string, string> parse_cookie(const string& cookie_header){
    maps<string, string> cookies;
    string s = cookie_header;

    stringstream ss(s);
    string part;
    while(getline(ss, part, ";")){
        while(!part.empty() && part.front() == ' '){
            part.erase(part.begin());
        }
        auto y = part.find("=");
        if(y != string::npos){
            c[part.substr(0, y)] = part.substr(y + 1);
        }
    }
    return cookies;
}

static string random_session_id(){
    static const char* hex_format = "0123456789abcdef";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 15);
    string id;
    for(int i = 0; i < 32; i++){
        id += hex_format[dist(gen)];
    }
    return id;
}

static vector<string> load_items(const string& session_id){
    vector<string> items;
    ifstream in(session_dir + "/session_" + session_id + ".txt");
    
    string line;
    while(getline(in, line)){
        items.push_back(line);
    }
    return items;
}

static void save_items(const string& session_id, const vector<string>& items){
    system((string("mkdir -p ") + session_dir).c_str());
    ofstream out(session_dir + "/session_" + session_id + ".txt", ios::trunc);
    for(auto& item : items){
        out << item << "\n";
    }
}

int main(){
    string cookie_header = env_get("HTTP_COOKIE", "");
    auto cookies = parse_cookie(cookie_header);
    string session_id = cookies.count(cookie) ? cookies[cookie] : random_session_id();

    string method = env_get("REQUEST_METHOD", "GET");
    string query_string = env_get("QUERY_STRING", "??");
    auto query = parse_form_encoded(query_string);

    string page = "form";
    if(query.count("page") && !query["page"].empty()){
        page = query["page"];
    }

    vector<string> items = load_items(session_id);

    if(method == "POST"){
        auto post = parse_form_encoded(read_stdin_body());
        string todo = post.count("action") ? post["action"] : "";
        
        if(todo == "save"){
            string value = post.count("value") ? post["value"] : "";

            if(!value.empty()){
                items.push_back(value);
                save_items(session_id, items);
            }
            page = "view";
        }
        else if(todo == "clear"){
            items.clear();
            save_items(session_id, items);
            page = "view";
        }
    }

    cout << "Cache-Control: no-cache\r\n";
    cout << "Content-Type: text/html\r\n";
    cout << "Set-Cookie: " << cookie << "=" << session_id << "; Path=/; SameSite=Lax\r\n\r\n";

    cout << "<!DOCTYPE html><html><head><title>State Demo (C++)</title></head><body>";
    cout << "<h1 align='center'>State Demo (C++)</h1><hr/>";
    cout << "<p><a href='" << base_url << "?page=form'>Form Page</a><a href='" << base_url << "?page=view'>View Page</a></p>";

    if (page == "form") {
        cout << "<h2>Enter data to save on the server COOOKIE</h2>";
        cout << "<form method='POST' action='" << base_url << "?page=form'>"
            << "<label for='value'>Value:</label> "
            << "<input id='value' name='value' type='text'/> "
            << "<input type='hidden' name='action' value='save'/> "
            << "<button type='submit'>Save</button>"
            << "</form>";
        cout << "<p>After saving, you will be taken to the View Page.</p>";
    } else {
        cout << "<h2>Saved values</h2>";
        if (items.empty()){
            cout << "<p>No saved data yet!! :(</p>";
        } 
        else {
            cout << "<ul>";
            for (auto& it : items){
                cout << "<li>" << html_escape(it) << "</li>";
            }
            cout << "</ul>";
        }
        cout << "<form method='POST' action='" << base_url << "?page=view' style='margin-top:20px;'>"
            << "<input type='hidden' name='action' value='clear'/>"
            << "<button type='submit'>Clear Saved Data</button></form>";
    }

    cout << "<hr><p><b>Session cookie:</b> " << cookie << " data stored in /tmp</p>";
    cout << "</body></html>";
    return 0;
}
