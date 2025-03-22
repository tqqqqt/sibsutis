import re
import config
from telebot import types

#global param
checkInput={None:None}
yandLang={None:None}

#----------------------------------WEATHER-------------------------------
#weather api req
WEATHER_REQ_temp='https://api.openweathermap.org/data/2.5/weather?q={city}&appid={apiKey}&units=metric'
WEATHER_REQ=WEATHER_REQ_temp.replace('{apiKey}',config.WEATHER_KEY)

#/start markup
mainMarkup=types.ReplyKeyboardMarkup(resize_keyboard=True)
item1=types.KeyboardButton('Погода')
item2=types.KeyboardButton('Курс валют')
item3=types.KeyboardButton('Словарь')
item4=types.KeyboardButton('Поиск АЗС')
mainMarkup.add(item1)
mainMarkup.add(item2)
mainMarkup.add(item3)
mainMarkup.add(item4)

#weather markup
weatherMarkup=types.ReplyKeyboardMarkup(resize_keyboard=True)
item1=types.KeyboardButton('Москва')
item2=types.KeyboardButton('Новосибирск')
item3=types.KeyboardButton('Екатеринбург')
item4=types.KeyboardButton('Казань')
item5=types.KeyboardButton('Вернуться в начало')
weatherMarkup.add(item1,item2)
weatherMarkup.add(item3,item4)
weatherMarkup.add(item5)

#weather regex
tempPatern=re.compile(r'"temp":(-?\d+.\d+)')
feelsPatern=re.compile(r'"feels_like":(-?\d+.\d+)')

#weahet message template
messageWeatherTemp='Температура = {temp} градусов, ощущается как = {fels}'


#------------------------------MONEY--------------------------------
#money api req
MONEY_REQ_temp='https://free.currconv.com/api/v7/convert?q={valut}&compact=ultra&apiKey={apiKey}'
MONEY_REQ=MONEY_REQ_temp.replace('{apiKey}',config.MONEY_KEY)

#money markup
moneyMarkup=types.ReplyKeyboardMarkup(resize_keyboard=True)
item1=types.KeyboardButton('USD_RUB')
item2=types.KeyboardButton('RUB_USD')
item3=types.KeyboardButton('EUR_RUB')
item4=types.KeyboardButton('RUB_EUR')
item5=types.KeyboardButton('CNY_RUB')
item6=types.KeyboardButton('RUB_CNY')
item7=types.KeyboardButton('Вернуться в начало')
moneyMarkup.add(item1,item2)
moneyMarkup.add(item3,item4)
moneyMarkup.add(item5,item6)
moneyMarkup.add(item7)

#money regex
valuePatern=re.compile(r':(\d+.\d+)')

#money message template
messageMoneyTemp='Текущий курс = {value}'


#---------------------------YANDEX-------------------------------
#yandex api req
YANDEX_REQ_temp='https://dictionary.yandex.net/api/v1/dicservice/lookup?key={apiKey}&lang={language}&text={text}'
YANDEX_REQ=YANDEX_REQ_temp.replace('{apiKey}',config.YANDEX_KEY)

#yandex markup
yandexMarkup=types.ReplyKeyboardMarkup(resize_keyboard=True)
item1=types.KeyboardButton('ru-ru')
item2=types.KeyboardButton('en-en')
item3=types.KeyboardButton('ru-en')
item4=types.KeyboardButton('en-ru')
item5=types.KeyboardButton('ru-uk')
item6=types.KeyboardButton('uk-ru')
item7=types.KeyboardButton('Вернуться в начало')
yandexMarkup.add(item1,item2)
yandexMarkup.add(item3,item4)
yandexMarkup.add(item5,item6)
yandexMarkup.add(item7)

#yandex regex
translatePatern='<tr pos="(.*?)".*?<text>(.*?)<.*?tr>'
synAndMeanFindPatern='<tr.*?<text>(?={temp}).*?text>(.*?tr>)'
synPatern='<syn.*?text>(.*?)<.*?yn>'
meanPatern='<mean.*?xt>(.*?)<.*?an>'

#yandex message template
translateTemp='Перевод введеного текста - {trans}'
synTemp='Синонимы: {syn}'
meanTemp='Значения: {mean}'
exTemp='Примеры использования: {ex}'


#---------------------------YANDEX GPS+ORG-----------------------
#GPS api req
GPS_REQ_temp='https://geocode-maps.yandex.ru/1.x/?apikey={key}&geocode={text}&format=json'
GPS_REQ=GPS_REQ_temp.replace('{key}',config.YANDEX_GPS)

#ORG api req
ORG_REQ_temp='https://search-maps.yandex.ru/v1/?text={text}&ll={cord}&spn={rad}&rspn=1&type=biz&lang=ru_RU&apikey={key}'
ORG_REQ=ORG_REQ_temp.replace('{key}',config.YANDEX_ORG)

#ORG message template
messOrgTemp='Имя организации:{name}\nАдрес:{adr}\nОписание:{desc}'
