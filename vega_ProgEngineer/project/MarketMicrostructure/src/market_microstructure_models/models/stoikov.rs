use chrono::NaiveDate;

use crate::market_microstructure_models::OrderBook;


pub struct SimulationsResult{
    q: Vec<i64>,
    x: Vec<f64>,
    delta_a: Vec<f64>,
    delta_b: Vec<f64>,
    intensity_a: Vec<f64>,
    intensity_b: Vec<f64>,
}

pub struct StoikovModel
{
    sigma: Vec<f64>,
}

impl StoikovModel
{
    pub fn new(filename: &str, instrument: String, price_step: f64){

    }
}