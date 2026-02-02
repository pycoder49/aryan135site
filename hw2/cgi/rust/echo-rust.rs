use std::collections::HashMap;
use std::env;
use std::io::{self, Read};

fn decode_url(s: &str) -> String{
    let mut result = String::new();
    let bytes = s.as_bytes();
    
    let mut i = 0;
    while i < bytes.len(){
        match bytes[i]{
            b'+' => {
                result.push(' ');
                i += 1;
            }
            b'%' if i + 2 < bytes.len() => {
                let h1 = bytes[i+1] as char;
                let h2 = bytes[i+2] as char;
                let hex_format = format!("{}{}", h1, h2);
                if let Ok(value) = u8::from_str_radix(&hex_format, 16){
                    result.push(value as char);
                }
                i += 3;
            }
            _ => {
                result.push(bytes[i] as char);
                i += 1;
            }
        }
    }
    result
}

fn parse_form_urlencoded(s: &str) -> HashMap<String, String>{
    let mut hash_map = HashMap::new();
    for pair in s.split('&'){
        if pair.is_empty(){
            continue;
        }
        let mut split = pair.splitn(2, '=');
        let key = split.next().unwrap_or("");
        let value = split.next().unwrap_or("");
        hash_map.insert(decode_url(key), decode_url(value));
    }
    hash_map
}

fn parse_json_object(s: &str) -> HashMap<String, String>{
    let mut hash_map = HashMap::new();
    let chopped = s.trim().trim_start_matches('{').trim_end_matches('}');

    for part in chopped.split(','){
        let part = part.trim();
        if part.is_empty(){
            continue;
        }

        let mut split = part.splitn(2, ':');
        let key = split.next().unwrap_or("").trim().trim_matches('"');
        let value = split.next().unwrap_or("").trim().trim_matches('"');
        
        hash_map.insert(key.to_string(), value.to_string());
    }
    hash_map
}

fn html_escape(s: &str) -> String{
    s.replace('&', "&amp;")
     .replace('<', "&lt;")
     .replace('>', "&gt;")
     .replace('"', "&quot;")
     .replace('\'', "&#39;")
}

fn main(){
    let method = env::var("REQUEST_METHOD").unwrap_or("GET".to_string());
    let query_string = env::var("QUERY_STRING").unwrap_or("".to_string());
    let ip = env::var("REMOTE_ADDR").unwrap_or("unknown".to_string());
    let user_agent = env::var("HTTP_USER_AGENT").unwrap_or("unknown".to_string());
    let content_type = env::var("CONTENT_TYPE").unwrap_or("".to_string());

    let mut body = String::new();
    if method != "GET"{
        if let Ok(content_length) = env::var("CONTENT_LENGTH").unwrap_or("0".to_string()).parse::<usize>(){
            if content_length > 0{
                io::stdin().read_to_string(&mut body).ok();
            }
        }
    }

    let mut params = HashMap::new();
    if !query_string.is_empty(){
        params.extend(parse_form_urlencoded(&query_string));
    }

    if !body.is_empty(){
        if content_type == "application/json"{
            params.extend(parse_json_object(&body));
        }
        else{
            params.extend(parse_form_urlencoded(&body));
        }
    }

    print!("Cache-Control: no-cache\r\n");
    print!("Content-Type: text/html\r\n\r\n");

    println!("<!DOCTYPE html>");
    println!("<html><head><title>Echo Rust</title></head><body>");
    println!("<h1 align='center'>Echo Rust</h1><hr/>");

    println!("<p><b>Method:</b> {}</p>", html_escape(&method));
    println!("<p><b>IP:</b> {}</p>", html_escape(&ip));
    println!("<p><b>User-Agent:</b> {}</p>", html_escape(&user_agent));
    println!("<p><b>Content-Type:</b> {}</p>", html_escape(&content_type));

    println!("<h2>Received Parameters</h2>");
    if params.is_empty() {
        println!("<p>No parameters received :(</p>");
    } else {
        println!("<ul>");
        let mut keys: Vec<String> = params.keys().cloned().collect();
        keys.sort();
        for key in keys {
            let value = params.get(&key).unwrap_or(&"".to_string()).clone();
            println!("<li><code>{}</code> = <code>{}</code></li>", html_escape(&key), html_escape(&value));
        }
        println!("</ul>");
    }

    println!("</body></html>");
}