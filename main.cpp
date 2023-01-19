#include <iostream>
#include <map>
#include <string>
#include <set>

void print_multimap(const std::multimap<std::string, std::string>& m1){
    std::cout << std::endl;
    for (auto iter = m1.cbegin(); iter != m1.cend(); iter++){
        std::cout << "(" << iter->first << ", " << iter->second << ")" << std::endl;
    }
    std::cout << "Total:" << m1.size() << std::endl;
}

//Функция, изменяющая номер под единый стандарт
std::string transform_number(const std::string& num){
    std::string str = num;
    std::string chars_to_delete = " -+_";
    for (char c: chars_to_delete){
        str.erase(std::remove(str.begin(), str.end(), c), str.end());
    }
    if (str.length() == 10){
        str.insert(0, 1, '7');
        str.insert(0, 1, '+');
        return str;
    }
    if (str.length() == 11 && str[0] == '7'){
        str.insert(0, 1, '+');
        return str;
    }
    //Случай: 8**********
    str.erase(0, 1);
    str.insert(0, 1, '7');
    str.insert(0, 1, '+');
    return str;
};

//Функция, которая удаляет дубликаты и возвращает новый контейнер multimap
std::multimap<std::string, std::string> delete_duplicates(
        const std::multimap<std::string, std::string>& m2){
    std::set<std::string> keys;
    for (auto iter = m2.cbegin(); iter != m2.cend(); iter++){
        keys.insert(iter->first);
    }
    std::multimap<std::string, std::string> new_multimap;
    std::set<std::string> num_set;
    for (auto name: keys){
        for (auto iter = m2.equal_range(name).first; iter != m2.equal_range(name).second; iter++){
            num_set.insert(transform_number(iter->second));
        }
        for (auto numbers: num_set){
            new_multimap.emplace(name, numbers);
        }
        num_set.clear();
    }
    return new_multimap;
}

int main() {
    //1-2 -> Создание и заполнение контейнера
    std::multimap<std::string, std::string> main ={
            {"Lemov", "8 925 326 21 45"}, {"Lemov", "8 923 111 11 01"},
            {"Kostynov", "+79175846536"}, {"Rinnova", "9182220110"},
            {"Lerova", "89175648978"}, {"Kostova", "+7 922 132 77 99"},
            {"Loktev", "8999 888 77 01"}, {"Yarova", "8977 555 10 32"},
            {"Lemov", "8 922 000 00 02"}, {"Aratynova", "+7 925 222 35 55"}
    };
    print_multimap(main);

    //3 -> Копия контейнера
    std::multimap<std::string, std::string> main_copy(main.begin(), main.end());
    print_multimap(main_copy);

    //4 -> удаление элемента по ключу
    main_copy.erase("Loktev");
    main_copy.erase("Yarova");
    main_copy.erase("Kostova");
    std::cout << std::endl << "After deleting:";
    print_multimap(main_copy);

    //5 -> Изменение номера по ключу
    auto iter = main_copy.find("Rinnova");
    iter->second = "999 654 32 10";
    print_multimap(main_copy);

    //6 -> Создание и добавление элементов в карту "Избранные контакты"
    std::multimap<std::string, std::string> favorite_contacts;
    std::string friends[] = {"Lemov", "Kostynov", "Kostova", "Lerova"};
    for(const std::string& name: friends){
        favorite_contacts.insert(std::make_pair(name, main.find(name)->second));
    }
    print_multimap(favorite_contacts);

    //7 -> Использование insert, emplace
    favorite_contacts.insert(std::make_pair("Kostonova", "+7 934 342 34 04"));
    favorite_contacts.insert({"Lerova", "8919 252 25 25"});
    favorite_contacts.insert({"Nikolaev", "8999 963 52 41"});
    favorite_contacts.emplace("Kostova", "8925 123 35 55");
    favorite_contacts.emplace("Lerova", "8919 252 25 25");
    favorite_contacts.emplace("Kostynov", "+79175846536");
    const char* name1 = "Nikolaev";
    const char* number1 = "8999 963 52 41";
    favorite_contacts.emplace(name1, number1);
    char name2[] = "Kornov";
    char number2[] = "8910 052 39 14";
    favorite_contacts.emplace(name2, number2);
    print_multimap(favorite_contacts);

    //8 -> Удаление дубликатов
    std::multimap<std::string, std::string> f_contacts;
    f_contacts = delete_duplicates(favorite_contacts);
    print_multimap(f_contacts);

    //9 -> Протестируем merge на main и f_contacts
    std::cout << "size of main is " << main.size() << std::endl;
    std::cout << "size of f_contacts is " << f_contacts.size() << std::endl;
    main.merge(f_contacts);
    std::cout << "size of merger multimap is " << main.size() << std::endl;
    print_multimap(main);
    return 0;
}
