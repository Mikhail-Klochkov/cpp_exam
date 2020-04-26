
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <iterator>
#include <ostream>
#include <algorithm>
#include <vector>
#include <list>
#include <typeinfo>

template <typename T>
void enter_set(const std::multiset<T>&  mset){
    typename std::multiset<T>::const_iterator it = mset.cbegin();
    for(; it != mset.cend(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <class Container>
void enter_container(const Container & C){
    typename Container::const_iterator it = C.cbegin();
    while(it != C.cend()){
        std::cout << *it++ << " ";
    }
    std::cout << std::endl;
}

template <class Container>
void enter_map(const Container & C){
    // we can use map and multimap  
    typename Container::const_iterator it = C.cbegin();
    while(it != C.cend()){
        std::cout << "{" << it->first << " : " << it->second << "} ";
        it++;
    }
    std::cout << std::endl;
}
template <typename key_type, typename T, class Map>
void insert_vector_into_map(const std::vector< std::pair< key_type, T > > & vec, Map & M){
    typename std::vector< std::pair<key_type, T > >::const_iterator it_vec = vec.cbegin();
    while(it_vec != vec.cend()){
        M.insert(*it_vec);
        it_vec++;
    }
    return;
}
template <class Container>
void enter_common(const Container & container){
    typedef typename Container::value_type type;
    std::copy(container.cbegin(), container.cend(), std::ostream_iterator<type>(std::cout , " "));
    std::cout << std::endl;
}
//typedef std::pair<const Key, T> value_type; // this implementation of value_type a map
template <typename T1, typename T2>
std::ostream & operator << (std::ostream & stream, const std::pair<T1, T2> & pair){
    stream << "{" << pair.first << " : " << pair.second << " }" << " ";
    return stream;
}
//  попробуем с помощью контекста traits написать метод реверсирования при этом не конкретизируя какая категория итераторов нам попалась
template <class BidiIt>  // Bi direction iterator
void my_reverse(BidiIt first, BidiIt last){ // Мы принимаем типы значений как итератор 
    typename std::iterator_traits<BidiIt>::difference_type n = std::distance(first, last);
    --n; // Переместится но не прыгнуть в конец last
    while(n > 0){ // по сути мы тут реализовываем swap 
        typename std::iterator_traits<BidiIt>::value_type tmp = *first;
        *(++first) = *--last; // Мы обменяли
        *last = tmp;
        n -= 2;
    }
    typedef typename std::iterator_traits<BidiIt>::iterator_category it_cat;
    typedef typename std::random_access_iterator_tag Itr_rand;
    typedef typename std::bidirectional_iterator_tag Itr_bidir;
    if(typeid(it_cat) == typeid(Itr_rand)){
        std::cout << "category of iterator is: a random_access_iterator_tag " << std::endl;
    }else if(typeid(it_cat) == typeid(Itr_bidir)){
        std::cout << "category of iterator is: a bidirectional_iterator_tag " << std::endl;        
    }else{
        std::cout << "category of iterator is: a Nonedefault" << std::endl;                
    }
}

int main(){
    
    std::multiset<std::string> cities = {"Volgograd", "Samara", "Volgograd"};
    // здесь не создаётся дополнитеоьного объекта при копировании
    for(const auto & elem: cities){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    cities.insert({"London", "Volgograd"});
    enter_set(cities);
    enter_container(cities);
    // log complexity
    std::copy(cities.cbegin(), cities.cend(), std::ostream_iterator<std::string>(std::cout, " ") ); 
    std::cout << std::endl;
    
    ///map///
    std::multimap<int, std::string> coll;
    coll = {
        {5, "fife"}, {2, "a"}, {3, "this"}, {5, "second"} // список инициализации оно обзе для всех способов создания объектов с помощью конструкторов
    };
    for(const auto elem: coll){
        std::cout << elem.second << " ";
    }
    std::cout << std::endl;
    enter_map(coll);
    std::vector<std::pair<int, std::string>> insert_map = {{19, "Misha"}, {20, "!"}};
   // coll.insert(insert_map);
  // coll.insert(insert_map);
    coll.insert(std::pair<int, std::string>({3, "hello"}));
    enter_map(coll);
    //insert_vector_into_map(insert_map, coll);
    //enter_map(coll);
    coll.insert(insert_map.cbegin(), insert_map.cend());
    enter_map(coll);
    coll.insert({12, "appdate"});
    enter_map(coll);
   // coll.erase();
    insert_map.erase(insert_map.begin());
    //enter_common(insert_map);
    std::cout << std::pair<int, std::string>({5, "-"}) << std::endl;
    std::vector<int> v = {1,3,4,5,5,10,12,9};
    // erase, sort, reverse, find, max_element, min_element, 
    std::vector<int>::const_iterator minpos = std::min_element(v.begin()
                                        ,v.end());
        // в с++98  нет списка инициализации
    // каждый алгоритм обрабатывает полудиапазон!
    // момент чтобы найти нужный эелемент, который может быть и последним в качестве позиции для рассмотрения
   // std::max_element(pos_1, ++pos2); // Чтобы он захватил и последний pos2
    // Иногда можно и итераторную арифметику, но для типо deque vector
    std::list<int> list_;
    for(int i = 0 ; i < 6 ; ++i){
        list_.push_back(i * 10);
    }
    std::list<int>::iterator pos10 = std::find(list_.begin(), list_.end(), 10);
    auto pos40 = std::find(list_.begin(), list_.end(), 40);
    ++pos40;
    auto pos30 = std::find(list_.begin(), list_.end(), 30);
    if(pos30 == pos40){
        std::cout << "no" << std::endl;
    }else{
        std::cout << "yes" << std::endl; 
    }
    typedef std::list<int>::iterator IntItList;
    IntItList pos10_ = std::find(list_.begin(), list_.end(), 10);
    IntItList pos30_ = std::find(list_.begin(), pos10_, 30);
    if(pos10_ != list_.end() && pos30_ != pos10_){
        std::cout << "correct: [pos30, pos10)" << std::endl;
    }else{
        pos30_ = std::find(pos10_, list_.end(), 30);
        if(pos30_ != list_.end()){
            std::cout << "pos10 < pos35" << std::endl;
        }else{
            std::cout << " не найдены !" << std::endl;            
        }
    }
    auto pos = std::find_if(list_.begin(), list_.end(), [](int i){
        return i == 20 || i == 30;
    });
    if(pos == list_.end()){
        std::cout << "pos 20 or 30 не обнаружен" << std::endl;
    }
    //  где мы определяем несколько диапазонов 
    //std::equal(coll.begin(), coll.end(), coll_another.begin());
    //  Но размеры второго диапазона должны быть не меньшк чем у первого
    // Чтобы перезапись не происходила в несуществующие элемнты другого контейнера
    std::vector<int> b{1,2,4,5,5,6,8,0};
    my_reverse(b.begin(), b.end());
    for (auto & el: b){
        std::cout << el << " ";
    }
    std::list<int> c = {1,3,4,5,5,87,8};
    my_reverse(c.begin(), c.end());
    for (auto & el: c){
        std::cout << el << " ";
    }
    return 0;
}



