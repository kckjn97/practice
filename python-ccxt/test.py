from exchange import Exchange
import pprint

# test FetchOHLCV
exchange = Exchange('binance')
ohlcv = exchange.FetchOhlcv('BNB/USDT', '1h')
pprint.pprint(ohlcv)


# test Buy / Sell
BINANCE_API_KEY = "GgLBceEs819J44eOevTV9sYJcp5dk6CmEcwmRnb0aiz7sZkcO4wkdz4lO8nyNDWP"
BINANCE_API_SECRET = "EAoJTyxduMEqvQUb9Cv5l5KKuHMzRNEVg1814RknZ4LjhWTWQPR0L6sTnAxBOTko"
exchange2 = Exchange('binance', api_key = BINANCE_API_KEY, secret = BINANCE_API_SECRET)
exchange2.Sell('BNB/USDT', 1)
exchange2.Buy('BNB/USDT', 1)
