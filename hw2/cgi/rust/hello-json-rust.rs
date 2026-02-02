use std::env;
use std::time::{SystemTime, UNIX_EPOCH};

fn json_escape(s: &str) -> String{
    let escaped = s
        .replace('\\', "\\\\")
        .replace('"', "\\\"")
        .replace('\n', "\\n")
        .replace('\r', "\\r")
        .replace('\t', "\\t");
    print!("{}", escaped);
}

fn main(){
    let ip = env::var("REMOTE_ADDR").unwrap_or("unknown".to_string());
    let now = SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_secs();
    let user_agent = env::var("HTTP_USER_AGENT").unwrap_or("unknown".to_string());

    print!("Cache-Control: no-cache\r\n");
    print!("Content-Type: application/json\r\n\r\n");

    println!(
        "{{\
            \"message\":\"Hello World\",\
            \"language\":\"Rust\",\
            \"generated_at\":{},\
            \"ip\":\"{}\",\
            \"user_agent\":\"{}\"\
        }}",
        now, json_escape(&ip), json_escape(&user_agent)
    );
}