use std::collections::HashMap;
use std::env;
use std::fs;
use std::io::{self, Read};

let cookie: &str = "CGISESSID";
let session_dir: &str = "/tmp/cse135-rust-sessions";
let base_url: &str = "/hw2/cgi/rust/state-rust.cgi";

fn html_escape(s: &str) -> String{
    s.replace('&', "&amp;")
     .replace('<', "&lt;")
     .replace('>', "&gt;")
     .replace('"', "&quot;")
     .replace('\'', "&#39;")
}

fn url_decode(s: &str) -> String{
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
                let hex_format = format!("{}{}", bytes[i+1] as char, bytes[i+2] as char);
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
        hash_map.insert(url_decode(key), url_decode(value));
    }
    hash_map
}

fn parse_cookie(s: &str) -> HashMap<String, String>{
    let mut hash_map = HashMap::new();
    for pair in s.split(';'){
        let part = part.trim();
        if part.is_empty(){
            continue;
        }

        let mut split = part.splitn(2, '=');
        let key = split.next().unwrap_or("").trim();
        let value = split.next().unwrap_or("").trim();
        if !key.is_empty(){
            hash_map.insert(key.to_string(), value.to_string());
        }
    }
    hash_map
}

fn random_session_id() -> String{
    let pid = std::process::id();
    let time = env::var("REQUEST_TIME").unwrap_or("0".to_string());
    format!("{}-{}", pid, time.replace('.', ""))
}

fn get_session_id() -> String{
    let cookie_header = env::var("HTTP_COOKIE").unwrap_or("".to_string());
    let cookies = parse_cookie(&cookie_header);
    if let Some(session_id) = cookies.get(cookie) {
        if session_id.replace('-', "").chars().all(|c| c.is_ascii_alphanumeric()){
            return session_id.clone();
        }
    }
    random_session_id()
}

fn load_items(session_id: &str) -> Vec<String>{
    let path = format!("{}/session_{}.txt", session_dir, session_id);
    if let Ok(contents) = fs::read_to_string(&path){
        contents.lines().map(|line| line.to_string()).collect()
    }
    else{
        vec![]
    }
}

fn save_items(session_id: &str, items: &[String]){
    let path = format!("{}/session_{}.txt", session_dir, session_id);
    let data = items.join("\n");
    let _ = fs::write(path, data);
}

fn main(){
    let _ = fs::create_dir_all(session_dir);

    let session_id = get_session_id();
    let method = env::var("REQUEST_METHOD").unwrap_or("GET".to_string());
    let query_string = env::var("QUERY_STRING").unwrap_or("".to_string());

    let mut query = HashMap::new();
    if !query_string.is_empty(){
        query = parse_form_urlencoded(&query_string);
    }

    let mut page = query.get("page").cloned().unwrap_or("form".to_string());
    if page != "form" && page != "view"{
        page = "form".to_string();
    }

    let mut items = load_items(&session_id);

    if method == "POST"{
        let mut body = String::new();
        if let Ok(content_length) = env::var("CONTENT_LENGTH").unwrap_or("0".to_string()).parse::<usize>(){
            if len > 0{
                io::stdin().read_to_string(&mut body).ok();
            }
        }

        let post = parse_from_urlencoded(&body);
        let todo = post.get("action").cloned().unwrap_or("".to_string());

        if todo == "save"{
            if let Some(value) = post.get("value"){
                let value = value.trim();
                if !value.is_empty(){
                    items.push(value.to_string());
                    save_items(&session_id, &items);
                }
            }
            page = "view".to_string();
        }
        else if todo == "clear"{
            items.clear();
            save_items(&session_id, &items);
            page = "view".to_string();
        }
    }

    print!("Cache-Control: no-cache\r\n");
    print!("Content-Type: text/html\r\n");
    print!("Set-Cookie: {}={}; Path=/; SameSite=Lax\r\n\r\n", cookie, sid);

    // html code
    println!("<!DOCTYPE html>");
    println!("<html><head><title>State Demo (Rust)</title></head><body>");
    println!("<h1 align='center'>State Demo (Rust)</h1><hr/>");
    println!("<p><a href='{}?page=form'>Form Page</a> | <a href='{}?page=view'>View Page</a></p>", base_url, base_url);

    if page == "form"{
        println!("<h2>Enter data to save (COOOOKIES)</h2>");
        println!(
            "<form method='POST' action='{}?page=form'>\
             <label for='value'>Value:</label>\
             <input id='value' name='value' type='text' />\
             <input type='hidden' name='action' value='save' />\
             <button type='submit'>Save</button>\
             </form>",
            base_url
        );
        println!("<p>After saving, go to View Page to see saved values :D</p>");
    }
    else{
        println!("<h2>Saved values</h2>");
        if items.is_empty() {
            println!("<p>No saved data yet :(</p>");
        } else {
            println!("<ul>");
            for item in &items {
                println!("<li>{}</li>", html_escape(item));
            }
            println!("</ul>");
        }

        println!(
            "<form method='POST' action='{}?page=view' style='margin-top: 20px;'>\
             <input type='hidden' name='action' value='clear' />\
             <button type='submit'>Clear Saved Data</button>\
             </form>",
            base_url
        );
    }

    println!("<hr><p><b>Session cookie:</b> {} (server stores data in /tmp)</p>", cookie);
    println!("</body></html>");
}