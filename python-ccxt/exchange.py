import ccxt

class Exchange:
	def __init__(self, name, api_key = None, secret = None):
		self.exchange_name = name
		self.api_key = api_key
		self.secret = secret
		
		if api_key is None:
			if self.exchange_name == 'binance':
				self.exchange = ccxt.binance()
			else:
				assert(0)

		else:
			if self.exchange_name == 'binance':
				self.exchange = ccxt.binance({
					'apiKey': api_key,
					'secret': secret,
				})
			else:
				assert(0)
	
	def buy(self, symbol, amount, price = None):
		try:
			if price is None:
				order = self.exchange.create_market_buy_order(symbol, amount)
			else:
				order = self.exchange.create_order(symbol, 'limit', 'buy', amount, price)
		except:
			print("Buy error")

	def sell(self, symbol, amount, price = None):
		try:
			if price is None:
				order = self.exchange.create_market_sell_order(symbol, amount)
			else:
				order = self.exchange.create_order(symbol, 'limit', 'sell', amount, price)
		except:
			print("Sell error")

	def fetch_ohlcv(self, symbol, timeframe='1h', limit=100):
		ohlcv = self.exchange.fetch_ohlcv(symbol, timeframe, limit)
		return ohlcv
