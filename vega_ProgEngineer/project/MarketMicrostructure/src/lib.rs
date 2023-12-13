use pyo3::prelude::*;

mod order_book;
use crate::order_book::OrderBook;


// обязательно надо сделать возвращения объекта с состояниями стаканов для всех инструментов в файле 
// для этого надо будет попотеть и подружить pyo3 и нашу реализацию
// http://saidvandeklundert.net/learn/2021-11-18-calling-rust-from-python-using-pyo3/
#[pyfunction]
fn from_file(filename: &str, instrument: String, price_step: f64) {
    let temp_orderbook = OrderBook::from_file(filename, instrument, price_step);
    for i in temp_orderbook.instruments{
        println!("{}", i);
    }
}


/// Some doc string , __doc__
#[pymodule]
fn market_making(_py: Python<'_>, m: &PyModule) -> PyResult<()> {
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