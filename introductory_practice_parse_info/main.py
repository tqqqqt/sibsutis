import requests
from bs4 import BeautifulSoup

# name - kKpPOn
# symb - coin-item-symbol
# price - HgnCe
# market - gqomIJ

def pars():
    try:
        url = 'https://coinmarketcap.com'
        
        full_page = requests.get(url)
        soup = BeautifulSoup(full_page.text, 'html.parser')

        coin_name = soup.find(class_="cmc-table").find_all(class_="kKpPOn")
        coin_symb = soup.find(class_="cmc-table").find_all(class_="coin-item-symbol")
        coin_price = soup.find(class_="cmc-table").find_all(class_="HgnCe")
        coin_market = soup.find(class_="cmc-table").find_all(class_="gqomIJ")

        coin_info = []
        for i in range(10):
            new_element = coin_name[i].text, coin_symb[i].text, coin_price[i].text, coin_market[i].text
            coin_info.append(new_element)
        return coin_info
    except requests.exceptions.ConnectionError:
        print("Не удалось подключиться к сайту.")
        exit()
        

def prin_list(coin_list):
    print("Name\t\tSymb\t\tPrice\t\tMarketPrice")
    for element in coin_list:
        print(f"{element[0]:16} {element[1]:14} {element[2]:14} {element[3]:14}")

def main_menu(coin_list):
    function_exit = 0
    input_chose = ''
    while function_exit==0:
        input_chose = input("\n f - Найти элемент\n q - Выход \n ---> ")
        if input_chose == 'f':
            found = input("\n Введи для поиска -> ")
            found_in_list(found,coin_list)
        elif input_chose == 'q':
            function_exit += 2
        else:
            print(" Неизвестная кнопка. Попробуй еще раз. ")

def found_in_list(need_found, coin_list):
    print("\nName\t\tSymb\t\tPrice\t\tMarketPrice")
    for element in coin_list:
        if element[0].find(need_found) != -1:
            print(f"{element[0]:16} {element[1]:14} {element[2]:14} {element[3]:14}")

def main():
    list_data = []
    list_data = pars()
    prin_list(list_data)
    main_menu(list_data)


if __name__ == '__main__':
    main()
