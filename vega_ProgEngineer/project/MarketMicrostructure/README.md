# Basic model of Market-Making
In this project I want to implement the first academic Market-Making model[[1]](https://www.researchgate.net/publication/24086205_High_Frequency_Trading_in_a_Limit_Order_Book) on real market date(for getting of sample date u have to chat me to [telegram](t.me/User1Usr)). Project consist of two big parts: parser of orderlog from MOEX and calculate features for the model. I preferred to Rust/Python stack. I writing library On Rust, which implementing construction of the orderbook at the certain day, and ported some function from Rust lib to Python. The second part, I describe and implement model in detail [in this file](https://github.com/Cloda/homework_extracourse/blob/main/vega_ProgEngineer/project/MarketMicrostructure/script/stoikov.ipynb). 
## Getting started
Open virtual environment 

```sh
python3 -m venv ./test_venv  
source ./test_venv/bin/activate
```


Let's get all dependencies for python
```sh
pip3 install -r requirements.txt
```

Next u need to compile project(it makes in your env new package orderbook_lib):
```sh 
maturin develop
```

That command u need to launch instead of cargo run. Furter U can go to [main.ipynb](https://github.com/Cloda/homework_extracourse/blob/main/vega_ProgEngineer/project/MarketMicrostructure/script/main.ipynb) and check new Python package "market_making". If u work in jupiter u might have problem with kernel after compile package, u need just reload that.

## Result
I finished parser orderlog and Stoikov model in Brownian motion, but unfortunately i couldn't write before deadline calculete trading intensity and volatility from market date :( 


