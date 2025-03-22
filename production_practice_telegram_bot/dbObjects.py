import sqlite3
import datetime

#settings
dataBasePositive="positiveDB.sql"
tablePositive="positiveDB"
dataBaseNegative="negativeDB.sql"
tableNegative="negativeDB"
dataBaseAds="adsMessage.db"

#connect and cursor
posConnect=sqlite3.connect(dataBasePositive,check_same_thread=False)
negConnect=sqlite3.connect(dataBaseNegative,check_same_thread=False)
adsConnect=sqlite3.connect(dataBaseAds,check_same_thread=False)
posCursor=posConnect.cursor()
negCursor=negConnect.cursor()
adsCursor=adsConnect.cursor()

#query template
createTableQuery="CREATE TABLE IF NOT EXISTS {nameDB} (id INTEGER PRIMARY KEY AUTOINCREMENT, timemes VARCHAR(255), typemes VARCHAR(255), message VARCHAR(255))"
insertQuery='INSERT INTO {nameDB} (timemes,typemes,message) VALUES ("{curTime}","{typeMessage}","{curMessage}")'
findQuery="SELECT urlMes FROM ads WHERE message=='{text}'"

#create table
createPosDB=createTableQuery.replace('{nameDB}',tablePositive)
posCursor.execute(str(createPosDB))

createNegDB=createTableQuery.replace('{nameDB}',tableNegative)
negCursor.execute(createNegDB)


#functions
def AddElement(dbName, clientTypeMessage, clientMessage):
    insertDB=insertQuery.replace('{nameDB}',dbName)
    curentTime=datetime.datetime.now()
    insertDB=insertDB.replace('{curTime}',str(curentTime))
    insertDB=insertDB.replace('{typeMessage}',str(clientTypeMessage))
    insertDB=insertDB.replace('{curMessage}',str(clientMessage))
    if dbName==tablePositive:
        posCursor.execute(insertDB)
        posConnect.commit()
    elif dbName==tableNegative:
        negCursor.execute(insertDB)
        negConnect.commit()

def FindAds(clientMessage):
    findDB=findQuery.replace('{text}',clientMessage)
    adsCursor.execute(findDB)
    tempRes=adsCursor.fetchall()
    if tempRes:
        return tempRes[0][0]
    return ''
