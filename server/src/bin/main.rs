use std::net::TcpListener;
use std::thread::spawn;

fn main() {

    tcp_server::Database::create_table("users", ["login TEXT, ", "password TEXT, ", "database TEXT"].to_vec());

    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();
    println!("Listening started, ready to accept");
    loop {
        let (stream, addr) = listener.accept().unwrap();

        println!("New connection: {}", addr);

        spawn(move | |{
            loop {
                let q = tcp_server::handle_client(stream.try_clone().unwrap());
                if !q {
                    return;
                }
            }
        });
    }
    
}