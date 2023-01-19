#include <iostream>
#include <map>

void print_multimap(const std::multimap<std::string, std::string>& m1){
    std::cout << std::endl;
    for (auto iter = m1.cbegin(); iter != m1.cend(); iter++){
        std::cout << "(" << iter->first << ", " << iter->second << ")" << std::endl;
    }
    std::cout << "Total:" << m1.size() << std::endl;
}

int main() {
    //1-2 Создание и заполнение контейнера
    std::multimap<std::string, std::string> main ={
            {"Lemov", "8 925 326 21 45"}, {"Lemov", "8 923 111 11 01"},
            {"Kostynov", "+79175846536"}, {"Rinnova", "9182220110"},
            {"Lerova", "89175648978"}, {"Kostova", "+7 922 132 77 99"},
            {"Loktev", "8999 888 77 01"}, {"Yarova", "8977 555 10 32"},
            {"Lemov", "8 922 000 00 02"}, {"Aratynova", "+7 925 222 35 55"}
    };
    print_multimap(main);

    //3 - Копия контейнера
    std::multimap<std::string, std::string> main_copy(main.begin(), main.end());
    print_multimap(main_copy);

    //4 - удаление элемента по ключу
    main_copy.erase("Loktev");
    main_copy.erase("Yarova");
    main_copy.erase("Kostova");
    std::cout << std::endl << "After deleting:";
    print_multimap(main_copy);

    //5 - изменение номера по ключу
    auto iter = main_copy.find("Rinnova");
    iter->second = "999 654 32 10";
    print_multimap(main_copy);

    //6 Создание и добавление элементов в карту "Избранные контакты"
    std::multimap<std::string, std::string> favorite_contacts;
    std::string friends[] = {"Lemov", "Kostynov", "Kostova", "Lerova"};
    for(const std::string& name: friends){
        favorite_contacts.insert(std::make_pair(name, main.find(name)->second));
    }
    print_multimap(favorite_contacts);
    return 0;

    //7
}
