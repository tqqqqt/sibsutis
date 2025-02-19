#! /usr/bin/bash

curDate=$(date)
nameUser=$(whoami)
domainName=$(hostname)    #(dnsdomainname)
echo "Дата - $curDate"
echo "Имя пользователя - $nameUser"
echo "Доменное имя ПК - $domainName"

procModel=$(lscpu | grep "Model name" | sed '1 s/Model name://' | sed -r 's/\s + //g')
if [[ "$procModel" == "" ]]; then 
	procModel=$(lscpu | grep "Имя модели" | sed '1 s/Имя модели://' | sed -r 's/\ + //g') 
fi
procArchit=$(lscpu | grep "Architecture" | sed '1 s/Architecture://' | sed -r 's/\s + //g')
if [[ "$procArchit" == "" ]]; then
	procArchit=$(lscpu | grep "Архитектура" | sed '1 s/Архитектура://' | sed -r 's/\s + //g')
fi
procMax=$(lscpu | grep "CPU max MHz:" | awk '{print $4}')
if [[ "$procMax" == "" ]]; then
	procMax=$(cat /proc/cpuinfo | grep 'cpu MHz' | head -n 1 | awk '{print $4}')
fi
procTMHz=$(cat /proc/cpuinfo | grep 'cpu MHz' | head -n 1 | awk '{print $4}')
if [[ "$procTMHz" == "" ]]; then
	procTMhz=$(lscpu --output-all -e | grep ',' | head -n 1 | awk '{print $14}')
fi
numYader=$(cat /proc/cpuinfo | grep processor | wc -l)
kolPotokov=$(lscpu | grep 'per core' | sed '1 s/Thread(s) per core://' | sed -r 's/\s + //g')
procNag=$(top -bn 1 | awk '/Cpu/ {print $2}')
echo "Процессор:"
echo -e "\t Модель - $procModel"
echo -e "\t Архитектура - $procArchit"
echo -e "\t Тактовая частота максимальная - $procMax MHz"
echo -e "\t Тактовая частота текущая (используемая) - $procTMHz MHz" 
echo -e "\t Количество ядер - $numYader"
echo -e "\t Количество потоков на одно ядро - $kolPotokov"
echo -e "\t Загрузка процессора - $procNag %"

cacheL1=$(lscpu | grep 'L1d' | sed '1 s/L1d cache://' | sed -r 's/\s + //g')
cacheL2=$(lscpu | grep 'L2' | sed '1 s/L2 cache://' | sed -r 's/\s + //g')
cacheL3=$(lscpu | grep 'L3' | sed '1 s/L3 cache://' | sed -r 's/\s + //g')
memAll=$(free -h | awk '/^Mem:/ {print $2}')
memDost=$(free -h | awk '/^Mem:/ {print $4}')
echo "Оперативная память:"
echo -e "\t Cache L1 - $cacheL1"
echo -e "\t Cache L2 - $cacheL2"
echo -e "\t Cache L3 - $cacheL3"
echo -e "\t Всего - $memAll"
echo -e "\t Доступно - $memDost"

diskAll=$(df -h | grep '/$' | awk '{print $2}')
diskDost=$(df -h | grep '/$' | awk '{print $4}')
kolRazdel=$(df -h | grep '/' | wc -l)
diskFolder=$(df -h | grep '/$' | awk '{print $1}')
diskFree=$(df -h | grep $diskFolder | sed -n '1p' | awk '{print $4}')
swapAll=$(free -h | awk '/^Swap:/ {print $2}')
swapDost=$(free -h | awk '/^Swap:/ {print $4}')
echo "Жесткий диск:"
echo -e "\t Всего - $diskAll"
echo -e "\t Доступно - $diskDost"
echo -e "\t Количество разделов - $kolRazdel"
echo -e "\t \t Название  -  Всего  -  Доступно"
temp=0
for ttemp in $(df -h | grep '/')
do
	(( temp++ ))
	if (( temp == 1)); then
		tempName=$ttemp
	elif (( temp == 2)); then
		tempSize=$ttemp
	elif (( temp == 4)); then
		tempDost=$ttemp
	elif (( temp  == 6)); then
		temp=0
		echo -e "\t \t $tempName  -  $tempSize  -  $tempDost"
	fi
done
echo -e "\t Смонтировано в корневую директорию - $diskFolder"
echo -e "\t Объем неразмеченного пространства - $diskFree"
echo -e "\t SWAP всего - $swapAll"
echo -e "\t SWAP доступно - $swapDost"

kolInterface=$(ifconfig | grep 'mtu' | wc -l)
echo "Сетевые интерфейсы:"
echo -e "\t Количество сетевых интерфейсов - $kolInterface"
echo -e "\t \t Имя  -  адрес  -  мак  -  тип  -  скорость"
for ttemp in $(ip address show | awk '/^[0-9]+:/ {print $2}' | sed 's/://g')
do
	ipAdres=$(ip address show $ttemp | grep 'inet' | awk 'NR==1{print $2}')
	macAdres=$(ip address show $ttemp | grep 'link' | awk 'NR==1{print $2}')
	if [[ "$ttemp" != "lo" ]]; then
	       	speed=$(cat "/sys/class/net/$ttemp/speed")
	fi
	nnum=0
	type=""
	for tttemp in $(ethtool $ttemp | grep 'baseT' | head -n 3)
	do
		(( nnum++ ))
		if ((nnum > 3)) then 
			type+=" $tttemp" 
		fi	
	done
	echo -e "\t \t $ttemp  -  $ipAdres  -  $macAdres  -  $type  -  $speed "
done

