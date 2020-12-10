import telegram
import sys

token = sys.argv[1]
msg = sys.argv[2]
bot = telegram.Bot(token)
chat_id_list = []

for i in bot.getUpdates():
    chat_id = i.message.chat.id
    if chat_id not in chat_id_list:
        bot.send_message(chat_id=chat_id, text=msg)
        chat_id_list.append(chat_id)

