use std::env;
use std::time::{SystemTime, UNIX_EPOCH};

fn main(){
    let ip = env::var("REMOTE_ADDR").unwrap_or(|_| "unknown".to_string());
    let now = SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_secs();

    print!("Cache-Control: no-cache\r\n");
    print!("Content-Type: text/html\r\n\r\n");

    println!("<!DOCTYPE html>");
    println!("<html><head><title>Hello HTML (Rust)</title></head><body>");
    println!("<h1 align='center'>Hello HTML Rust!</h1><hr/>");
    println!("<p>Hello Team Aryan! :D</p>");
    println!("<p>This page was generated with the Rust programming language</p>");
    println!("<p>Generated at (epoch seconds): {}</p>", now);
    println!("<p>Your IP Address is: {}</p>", ip);
    println!("</body></html>");
}