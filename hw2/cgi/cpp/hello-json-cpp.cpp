#include <bits/stdc++.h>
using namespace std;

static string json_escape(const string &s) {
    stringstream ss;
    for (char c : s) {
        switch (c) {
            case '\"': ss << "\\\""; break;
            case '\\': ss << "\\\\"; break;
            case '\b': ss << "\\b";  break;
            case '\f': ss << "\\f";  break;
            case '\n': ss << "\\n";  break;
            case '\r': ss << "\\r";  break;
            case '\t': ss << "\\t";  break;
            default:
                if ('\x00' <= c && c <= '\x1f') {
                    ss << "\\u"
                       << hex << setw(4) << setfill('0') << (int)c;
                } else {
                    ss << c;
                }
        }
    }
    return ss.str();
}

static string env_get(const char* key, const string &default_value){
    const char* value = getenv(key);
    return value ? string(value) : default_value;
}

static long long unix_seconds(){
    return (long long)time(nullptr);
}

int main(){
    string ip = env_get("REMOTE_ADDR", "unknown");
    string user_agent = env_get("HTTP_USER_AGENT", "unknown");

    cout << "Cache-Control: no-cache\r\n";
    cout << "Content-Type: application/json\r\n\r\n";

    cout << "{"
        << "\"message\": \"Hell, JSON C++!\", "
        << "\"language\": \"C++\", "
        << "\"generated_at\": " << unix_seconds() << ", "
        << "\"ip\": \"" << json_escape(ip) << "\", "
        << "\"user_agent\": \"" << json_escape(user_agent) << "\""
        << "}";
    return 0;
}
