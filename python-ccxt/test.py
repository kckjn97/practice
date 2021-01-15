from exchange import Exchange
import pprint

# test FetchOHLCV
exchange = Exchange('binance')
ohlcv = exchange.fetch_ohlcv('BNB/USDT', '1h')
pprint.pprint(ohlcv)


# test Buy / Sell
BINANCE_API_KEY = "GgLBceEs819J44eOevTV9sYJcp5dk6CmEcwmRnb0aiz7sZkcO4wkdz4lO8nyNDWP"
BINANCE_API_SECRET = "EAoJTyxduMEqvQUb9Cv5l5KKuHMzRNEVg1814RknZ4LjhWTWQPR0L6sTnAxBOTko"
exchange2 = Exchange('binance', api_key = BINANCE_API_KEY, secret = BINANCE_API_SECRET)
exchange2.sell('BNB/USDT', 1)
exchange2.buy('BNB/USDT', 1)
