use std::io::{Write, Read};
use std::net::TcpStream;

pub mod database;

pub use crate::database::*;

pub fn handle_client(mut stream: TcpStream) -> bool {
    let mut buf = vec![0; 128];
    let n = stream.read(&mut buf).unwrap();
    let message = String::from_utf8(buf.clone()).unwrap();
    let mut request: Vec<&str> = Vec::new();

    println!("New message from {}: {}", stream.peer_addr().unwrap(), message);

    let mut q = String::new();
    for i in message.chars() {
        if i != '\0' {
            q.push(i);
        }
    }

    if q.contains('L') {
        request = q.split_whitespace().collect();
        request.reverse();
        request.pop();
        request.reverse();
        
        let temp = Database::get_record(&request);

        if temp.len() > 0 {
            stream.write_all(&buf[..]).unwrap();
        }
    }

    if q.contains('R') {
        request = q.split_whitespace().collect();
        request.reverse();
        request.pop();
        request.reverse();
        
        Database::add_record(request);
        stream.write_all(&buf[0..n]).unwrap();
    }

    if n == 0 {
        return false;
    }

    return true;
}