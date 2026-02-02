use std::env;

fn html_escape(s: &str) -> String{
    s.replace('&', "&amp;")
     .replace('<', "&lt;")
     .replace('>', "&gt;")
     .replace('"', "&quot;")
     .replace('\'', "&#39;")
}

fn main(){
    print!("Cache-Control: no-cache\r\n");
    print!("Content-Type: text/html\r\n\r\n");

    println!("<!DOCTYPE html>");
    println!("<html><head><title>Environment Variables Rust</title></head><body>");
    println!("<h1 align='center'>Environment Variables in Rust!</h1><hr/>");
    println!("<table border='1' cellpadding='6'>");
    println!("<tr><th>Key</th><th>Value</th></tr>");

    let mut vars: Vec<(String, String)> = env::vars().collect();
    vars.sort_by(|a, b| a.0.cmp(&b.0));

    for (key, value) in vars{
        println!(
            "<tr><td><code>{}</code></td><td><code>{}</code></td></tr>",
            html_escape(&key),
            html_escape(&value)
        );
    }
    
    println!("</table></body></html>");
}