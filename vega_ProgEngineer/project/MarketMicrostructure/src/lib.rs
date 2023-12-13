use std::collections::HashSet;

use pyo3::prelude::*;

use chrono::NaiveTime;

mod market_microstructure_models;
use crate::market_microstructure_models::OrderBook;
use crate::market_microstructure_models::models;


// обязательно надо сделать возвращения объекта с состояниями стаканов для всех инструментов в файле 
// для этого надо будет попотеть и подружить pyo3 и нашу реализацию
// http://saidvandeklundert.net/learn/2021-11-18-calling-rust-from-python-using-pyo3/
#[pyfunction]
fn from_file(filename: &str, instrument: String, price_step: f64) {

    let mut list_of_timestamps: HashSet<NaiveTime> = HashSet::new();
    list_of_timestamps.insert(NaiveTime::parse_from_str("100000000000", "%H%M%S%f").unwrap());
    list_of_timestamps.insert(NaiveTime::parse_from_str("100000979342", "%H%M%S%f").unwrap());
    list_of_timestamps.insert(NaiveTime::parse_from_str("100000997825", "%H%M%S%f").unwrap());
    list_of_timestamps.insert(NaiveTime::parse_from_str("100032089772", "%H%M%S%f").unwrap());
    
    let temp_orderbook = OrderBook::from_file(filename, instrument, price_step, list_of_timestamps);
    for i in temp_orderbook.instruments{
        println!("{}", i);
    }
}


/// Some doc string , __doc__
#[pymodule]
fn orderbook_lib(_py: Python<'_>, m: &PyModule) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(from_file, m)?)?;
    Ok(())
}



// надо вынести в отдельную директорию
// также в toml добавить линковку
// для теста чисто питоновских функций https://aeshirey.github.io/code/2020/04/01/tests-and-pyo3.html

#[cfg(test)]
mod tests {
    #[test]
    fn test_add() {
        assert_eq!(3, 3);
    }
}