import telegram

def my_scheduled_job():
	token = "1238912534:AAHq9DvTPVqKFzjO5sEHjFSpzZLqsilwIHA"
	bot = telegram.Bot(token)
	chat_id_list = []
	
	for i in bot.getUpdates():
		chat_id = i.message.chat.id
		if chat_id not in chat_id_list:
			bot.send_message(chat_id=chat_id, text='Test message')
			chat_id_list.append(chat_id)

