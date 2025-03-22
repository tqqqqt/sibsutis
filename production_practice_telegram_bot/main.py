import telebot
import requests
import re
import json
import config
import mesObjects
import dbObjects

from telebot import types

bot = telebot.TeleBot(config.TOKEN)

@bot.message_handler(commands=['start'])
def WelcomMessage(message):
    if(mesObjects.checkInput.get(message.from_user.id)==None):
        mesObjects.checkInput[message.from_user.id]=0
    bot.send_message(message.chat.id,"Привет {0.first_name}!\nЯ бот помощник. Чем могу помочь?".format(message.from_user,bot.get_me()),parse_mode='html',reply_markup=mesObjects.mainMarkup)

@bot.message_handler(content_types=['text'])
def BotAnswer(message):
    if message.chat.type=='private':
        if message.text=='Вернуться в начало':
            mesObjects.checkInput[message.from_user.id]=0
            bot.send_message(message.chat.id,"Возращаемся...",parse_mode='html',reply_markup=mesObjects.mainMarkup)
        elif (message.text=='Погода' and mesObjects.checkInput.get(message.from_user.id)==0):
            mesObjects.checkInput[message.from_user.id]=1
            bot.send_message(message.chat.id,"Какой город вас интересует? Выберете из предложенных или введите название города на английском языке.",parse_mode='html',reply_markup=mesObjects.weatherMarkup)
        elif (message.text=='Курс валют' and mesObjects.checkInput.get(message.from_user.id)==0):
            mesObjects.checkInput[message.from_user]=2
            bot.send_message(message.chat.id,"Какие валюты вас интересуют? Выберете из предложенных или введите по их образцу необходимые вам.",parse_mode='html',reply_markup=mesObjects.moneyMarkup)
        elif (message.text=='Словарь' and mesObjects.checkInput.get(message.from_user.id)==0):
            mesObjects.checkInput[message.from_user.id]=3
            if(mesObjects.yandLang.get(message.from_user.id)==None):
                mesObjects.yandLang[message.from_user.id]='ru-ru'
            bot.send_message(message.chat.id,"Поменяйте язык если вам это необходимо и введите то, что вас интересует. Текущий язык - {0}".format(mesObjects.yandLang.get(message.from_user.id)),parse_mode='html',reply_markup=mesObjects.yandexMarkup)
        elif (message.text=='Поиск АЗС' and mesObjects.checkInput.get(message.from_user.id)==0):
            mesObjects.checkInput[message.from_user.id]=4
            bot.send_message(message.chat.id,"Введите место рядом с которым искать АЗС.",parse_mode='html',reply_markup=types.ReplyKeyboardMarkup(resize_keyboard=True))
        elif (message.text in ['ru-ru','en-en','ru-en','en-ru','ru-uk','uk-ru'] and mesObjects.checkInput.get(message.from_user.id)==3):
            mesObjects.yandLang[message.from_user.id]=message.text
            bot.send_message(message.chat.id,"Язык успешно изменен.",parse_mode='html')
        elif (message.text in ['USD_RUB','RUB_USD','EUR_RUB','RUB_EUR','CNY_RUB','RUB_CNY'] or mesObjects.checkInput.get(message.from_user.id)==2):
            reqStr=mesObjects.MONEY_REQ.replace('{valut}',message.text)
            info=requests.get(reqStr)
            resMatch=re.findall(mesObjects.valuePatern,info.text)
            if(resMatch):
                resValue=''.join(str(format(float(resMatch[0]),'.2f')))
                sendMessage=mesObjects.messageMoneyTemp.replace('{value}',resValue)
                bot.send_message(message.chat.id,sendMessage,parse_mode='html')
                dbObjects.AddElement('positiveDB','money-valut',message.text)
            else:
                bot.send_message(message.chat.id,"Такой информации нет. Попробуйте проверить вводимые вами данные.",parse_mode='html')
                dbObjects.AddElement('negativeDB','money-valut',message.text)
        elif (message.text in ['Москва','Новосибирск','Екатеринбург','Казань'] and mesObjects.checkInput==1):
            if message.text=='Москва':
                reqStr=mesObjects.WEATHER_REQ.replace('{city}','Moscow')
            elif message.text=='Новосибирск':
                reqStr=mesObjects.WEATHER_REQ.replace('{city}','Novosibirsk')
            elif message.text=='Екатеринбург':
                reqStr=mesObjects.WEATHER_REQ.replace('{city}','Yekaterinburg')
            elif message.text=='Казань':
                reqStr=mesObjects.WEATHER_REQ.replace('{city}','Kazan')
            info=requests.get(reqStr)
            tempMatch=re.findall(mesObjects.tempPatern,info.text)
            feelsLikeMatch=re.findall(mesObjects.feelsPatern,info.text)
            if (tempMatch and feelsLikeMatch):
                resTemp=''.join(str(format(float(tempMatch[0]),'.2f')))
                resFeels=''.join(str(format(float(feelsLikeMatch[0]),'.2f')))
                sendMessage=mesObjects.messageWeatherTemp.replace('{temp}',resTemp)
                sendMessage=sendMessage.replace('{fels}',resFeels)
                bot.send_message(message.chat.id,sendMessage,parse_mode='html')
                dbObjects.AddElement('positiveDB','weather-button-city',message.text)
            else:
                bot.send_message(message.chat.id,"Почему то нет информации...",parse_mode='html')
                dbObjects.AddElement('negativeDB','weather-button-city',message.text)
        elif mesObjects.checkInput.get(message.from_user.id)==1:
            reqStr=mesObjects.WEATHER_REQ.replace('{city}',message.text)
            info=requests.get(reqStr)
            tempMatch=re.findall(mesObjects.tempPatern,info.text)
            feelsMatch=re.findall(mesObjects.feelsPatern,info.text)
            if(tempMatch and feelsMatch):
                resTemp=''.join(str(format(float(tempMatch[0]),'.2f')))
                resFeels=''.join(str(format(float(feelsMatch[0]),'.2f')))
                sendMessage=mesObjects.messageWeatherTemp.replace('{temp}',resTemp)
                sendMessage=sendMessage.replace('{fels}',resFeels)
                bot.send_message(message.chat.id,sendMessage,parse_mode='html')
                dbObjects.AddElement('positiveDB','weather-text-city',message.text)
            else:
                bot.send_message(message.chat.id,"Я не смог найти информацию по вашему городу. Проверьте правильность названия города.",parse_mode='html')
                dbObjects.AddElement('negativeDB','weather-text-city',message.text)
        elif mesObjects.checkInput.get(message.from_user.id)==3:
            reqStr=mesObjects.YANDEX_REQ.replace('{language}',mesObjects.yandLang.get(message.from_user.id))
            reqStr=reqStr.replace('{text}',message.text)
            info=requests.get(reqStr)
            transMatch=re.findall(mesObjects.translatePatern,info.text)
            if transMatch:
                for trans in transMatch:
                    synMatch=[]
                    meanMatch=[]
                    resSendMessage=''
                    transTemp=str(trans[1])+' ('+str(trans[0])+')'
                    sendMessage=mesObjects.translateTemp.replace('{trans}',transTemp)
                    resSendMessage+=sendMessage+'\n'
                    synAndMeanPat=mesObjects.synAndMeanFindPatern.replace('{temp}',str(trans[1]))
                    synAndMean=re.findall(synAndMeanPat,info.text)
                    synMatch=re.findall(mesObjects.synPatern,synAndMean[0])
                    meanMatch=re.findall(mesObjects.meanPatern,synAndMean[0])
                    if synMatch:
                        resSyn=''
                        count=0
                        for temp in synMatch:
                            if count==0:
                                resSyn+=temp
                                count+=1
                            else:
                                resSyn+=', '+temp
                        sendMessage=mesObjects.synTemp.replace('{syn}',resSyn)
                        resSendMessage+=sendMessage+'\n'
                    if meanMatch:
                        resMean=''
                        count=0
                        for temp in meanMatch:
                            if count==0:
                                resMean+=temp
                                count+=1
                            else:
                                resMean+=', '+temp
                        sendMessage=mesObjects.meanTemp.replace('{mean}',resMean)
                        resSendMessage+=sendMessage+'\n'
                    bot.send_message(message.chat.id,resSendMessage,parse_mode='html')
                if message.from_user.is_premium!=True:
                    words=message.text.split()
                    for tempWord in words:
                        word=tempWord[:1].lower()+tempWord[1:]
                        resMes=dbObjects.FindAds(word)
                        if resMes!='':
                            bot.send_message(message.chat.id,resMes,parse_mode='html')
            if not transMatch:
                bot.send_message(message.chat.id,"Не удалось найти информации. Проверьте вводимые данные",parse_mode='html')
                dbObjects.AddElement('negativeDB','yandex-info',message.text)
            else:
                dbObjects.AddElement('positiveDB','yandex-info',message.text)
        elif mesObjects.checkInput.get(message.from_user.id)==4:
            textMes=message.text.replace(' ','+')
            reqGPS=mesObjects.GPS_REQ.replace('{text}',textMes)
            infoGPS=requests.get(reqGPS)
            resGps=json.loads(infoGPS.text)
            try:
                coords=resGps['response']['GeoObjectCollection']['featureMember'][0]['GeoObject']['Point']['pos']
            except IndexError:
                bot.send_message(message.chat.id,"Место для поиска не определенно.",parse_mode='html',reply_markup=mesObjects.mainMarkup)
                dbObjects.AddElement('negativeDB','yandex-gps',message.text)
                return
            coords=coords.replace(' ',',')
            reqORG=mesObjects.ORG_REQ.replace('{text}','АЗС')
            reqORG=reqORG.replace('{cord}',str(coords))
            reqORG=reqORG.replace('{rad}',str('0.5,0.5'))
            infoORG=requests.get(reqORG)
            resORG=json.loads(infoORG.text)
            i=0
            while i<5:
                try:
                    nameOrg=resORG['features'][i]['properties']['name']
                    adresOrg=resORG['features'][i]['properties']['description']
                    descripOrg=resORG['features'][i]['properties']['CompanyMetaData']['url']
                    if(len(str(nameOrg))>0 and len(str(adresOrg))>0):
                        textMes=mesObjects.messOrgTemp.replace('{name}',str(nameOrg))
                        textMes=textMes.replace('{adr}',str(adresOrg))
                        if(len(str(descripOrg))>0):
                            textMes=textMes.replace('{desc}',str(descripOrg))
                        else:
                            textMes=textMes.replace('\nОписание:{desc}','')
                        bot.send_message(message.chat.id,textMes,parse_mode='html')
                except IndexError:
                    break
                except KeyError:
                    i+=1
                    continue
                i+=1
            mesObjects.checkInput[message.from_user.id]=0
            if(i!=0):
                dbObjects.AddElement('positiveDB','yandex-gps',message.text)
            else:
                dbObjects.AddElement('negativeDB','yandex-gps',message.text)
            bot.send_message(message.chat.id,"Конец поиска.",parse_mode='html',reply_markup=mesObjects.mainMarkup)
        else:
            mesObjects.checkInput[message.from_user.id]=0
            bot.send_message(message.chat.id,"Простите, что-то пошло не так и я не знаю как мне вам ответить... \nПопробуйте еще раз",parse_mode='html')

bot.polling(none_stop=True)
