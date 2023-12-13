# Market Microstructure


## Get started
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

That command u need to launch instead of cargo run. That's it. If u work in jupiter u might have problem with kernel after compile package, u need just reload that.

