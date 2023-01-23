pub mod Database {
    const TABLE_NAME: &str = "users";
    fn connect_to_db() -> sqlite::Connection {
        let connection = sqlite::open("mainDatabase.db").expect("Can't open database");
        connection
    }

    pub fn create_table(table_name: &str, columns: Vec<&str>) {
        
        let column_names: String = columns.into_iter().collect(); // name TEXT, age INT, sirname TEXT

        let query = format!("CREATE TABLE IF NOT EXISTS {table_name}({column_names})");

        let connection = connect_to_db();
        connection.execute(query).expect("Error in executing the query!");
    }

    pub fn add_record(columns: Vec<&str>) {
        let login = columns[0];
        let password = columns[1];
        let database_name = columns[2];

        let query = format!("INSERT INTO {TABLE_NAME} VALUES ('{login}', '{password}', '{database_name}')");

        let connection = connect_to_db();
        connection.execute(query).expect("Error in executing the query!");
    }

    pub fn get_record(values: Vec<&str>) -> Vec<String> {
        let login = values[0];
        let password = values[1];
        let mut answer: Vec<String> = Vec::new();

        let query = format!("SELECT DISTINCT * FROM {TABLE_NAME} WHERE login = '{login}' AND password = '{password}'");

        let connection = connect_to_db();

        connection
        .iterate(query, |pairs| {
            for &(name, value) in pairs.iter() {
                let s = format!("{} {}", name, value.unwrap());
                answer.push(s);
            }
            true
        })
        .unwrap();

        answer
    }
}