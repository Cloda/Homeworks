use crate::market_microstructure_models::models;
use crate::market_microstructure_models::order_book;


pub struct PathOfStrategety
{
    sample_orderbook: OrderBook,
    sample_model: StoikovModel
    // sample_model: MODELS
}


pub struct BackTest
{
    to_backtest: HashMap<String, PathOfStrategety>,
    filename: String,
    instruments: HashSet<String>,
    start_time: NaiveDate,
    end_time: NaiveDate,
}

impl BackTest
{
    // не забыть сделать ивенты на премаркет 
    pub fn new()
    {
        // !!!!! ЖДЕМ ПОКА ВЫПОЛНЯТ ЧАСТЬ REVIEW ПАРСЕРА, ЕГО ОПТИМИЗАЦИИ
        // !!!!! ТАКЖЕ ЖДЕМ ЧАСТИ КОГДА СТРОИТСЯ СРАЗУ ДЛЯ ВСЕХ ИНСТРУМЕНТОВ
        // -------------------------
        // будет итератор ивентов по файлу через цикл 
        // проверка на тип ивента и запуск каких то фунций
        let mut orderbook = OrderBook::new(instrument.clone(), price_step);

        let mut reader = match csv::Reader::from_path(filename){
            Err(why) => panic!("Couldn't open {}: {}", filename, csv::Error::to_string(&why)),
            Ok(file) => file,
        };
        
        let mut l3_order_book_file: BufWriter<File> = __make_file(format!("{}_l3_orderbook.txt", instrument.clone().as_str()));
        let mut l2_order_book_ask_file: BufWriter<File> = __make_file(format!("{}_l2_ask.txt", instrument.clone().as_str()));
        let mut l2_order_book_bid_file: BufWriter<File> = __make_file(format!("{}_l2_bid.txt", instrument.clone().as_str()));

        let mut step_iter: i32 = 0;
        for result in reader.deserialize()
        {
            let record: Tick = match result {
                Err(why) => panic!("Couldn't parse string by serde {}: {}", filename, csv::Error::to_string(&why)),
                Ok(file) => file,
            };
            orderbook.update(&record, &mut step_iter, 
                            &mut l3_order_book_file, &mut l2_order_book_ask_file, &mut l2_order_book_bid_file, &timestamp);


        }

        
    }

    pub fn fit()
    {

    }
    
    pub fn summary()
    {
        
        
    }

}