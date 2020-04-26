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
#include <deque>
#include <sstream>
#include <cstdlib>


// Очень часто лямбда выражения более удобны, так как они избегают
// нагруженности и очень легко читаемы, они распознаются нами, как функциональный объект
class  Pred
{
private:
	int x;
	int y;
public:
	 Pred(int xx, int yy) : x(xx), y(yy) {}
	bool operator() (int i) const{
		return i > x && i < y;
	}
};
class Person{
private:
	std::string firstname;
	std::string lastname;
public:
	Person(const std::string & name_, const std::string & last_name_) : 
	   firstname(name_), lastname(last_name_) {}

	std::string firstname_ret() const{
		return firstname;
	}
	std::string lastname_ret() const{
		return lastname;
	}
	friend std::ostream & operator << (std::ostream & strm, const Person & person);
};
std::ostream & operator << (std::ostream & strm, const Person & person){
	strm << "name: " << person.firstname_ret() << "  lastname: " << person.lastname_ret() << std::endl;
	return strm; 
}

std::ostream & operator << (std::ostream & strm, const Person & person);

template <class Container>
void print_seq_container(const Container & container){
	typename Container::const_iterator it = container.cbegin();
	while(it != container.cend()){
		std::cout << *it++ << "  ";
	} 
	std::cout << std::endl;
}
template <class ForwardIt, class T>
ForwardIt remove_my(ForwardIt first, ForwardIt last, const T & value){
    ForwardIt results = first;
    for(; first != last; ++first){// последни элементы не меняются а те которые надо убрать просто сдвигом преобразуются
        if(!(*first == value)){
            std::cout << *results << " " << *first << "\n";
            *results++ = *first;
        }
    }
    return results;
} //проверка на простоту числа, сложность линейная от размера числа
bool isPrime(int number){ // Типичный пример бинарного предиката
	// bool p(const Type & value){... return boll(f(val))}
	number = std::abs(number); // only positive
	if(number == 1 || number == 0){
		return false;
	}
	int divisor;
	for(divisor = number / 2; number % divisor != 0; --number){
		;
	}
	return divisor == 1;
}
template <class Container>
void type_of_iterator(const Container& container){
	typedef typename std::iterator_traits<typename Container::iterator>::iterator_category itr_cat;
    typedef typename std::random_access_iterator_tag Itr_rand;
    typedef typename std::bidirectional_iterator_tag Itr_bidir;	
    typedef typename std::forward_iterator_tag Itr_forw;
	if(typeid(itr_cat) == typeid(Itr_rand)){
        std::cout << "category of iterator is: a Itr_rand" << std::endl;
	}else if(typeid(itr_cat) == typeid(Itr_bidir)){
        std::cout << "category of iterator is: a Itr_bidir" << std::endl;
	}else if(typeid(itr_cat) == typeid(Itr_forw)){
        std::cout << "category of iterator is: a Itr_forw" << std::endl;
	}else{
        std::cout << "category of iterator is: a Nonetype" << std::endl;		
	}
}
int main(){
	std::list<int> l = {1,2,3,4,5,6,67};
	std::vector<int> v;
	std::deque<int> d; 
	std::set<int> s;
	std::copy(l.cbegin(), l.cend(), std::back_inserter(v)); // push_back
	std::copy(l.cbegin(), l.cend(), std::front_inserter(d)); // push_front
	std::copy(l.cbegin(), l.cend(), std::inserter(s, s.begin())); // signature std::inserter(obj, and pos in obj)
	// ОН вообще говоря зависит от определенного типа контейнера 
	// Вообще говоря все эти функции это вспомогательный шаблон реализующий итераторы вставки
	print_seq_container(l);
	print_seq_container(v);
	print_seq_container(d);
	print_seq_container(s);
	std::vector<std::string> vec_str;
	// Он будет считывать пока не нападёт на ошибку
//	std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(),
//		                      std::back_inserter(vec_str));
	// По сути потоковый итератор трансформирует желение обработать какой-то эелемент из стандартного потока данных
	// оно трпнсформируется в std::cin >> строка
	// std::istream_iterator<std::string>() - вызывает конструктор конца потока 
	std::istringstream str("0.1 0.2 0.3 0.4");
	//std::copy(std::istream_iterator<double>(str), std::istream_iterator<double>(), 
//	                                                   std::ostream_iterator<double>(std::cout, " "));
    
	std::cout << std::endl;
	std::cout << *std::find_if(std::istream_iterator<double>(str), 
									std::istream_iterator<double>(), 
									[](double elem){
											return static_cast<int>(elem * 10) % 2 == 0;	
									}) << std::endl;
									
	std::string str_ = "some  text with several   spaces";
	str_.erase(std::remove(str_.begin(), str_.end(), ' '), str_.end());
	std::cout << str_ << "\n";
	std::list<int> list = {1,3,5,5,7,8};
	std::list<int>::iterator it_last_new = remove_my(list.begin(), list.end(), 5);
	std::cout << *it_last_new << std::endl;
	print_seq_container(list);// при удалении размер остается такой же только все элементы будут замены на  последующие  с сдвигом
    std::list<int> list_new(list.size() - std::distance(it_last_new, list.end()));
    std::copy(list.begin(), it_last_new , list_new.begin());
    std::list<int>::const_iterator ptr_first = list_new.cbegin();
    std::cout << "size: " << list_new.size() << std::endl;
    std::for_each(list_new.cbegin(), list_new.cend(), [&ptr_first](const int& elem){
    	    if(*ptr_first == elem){
    	    	std::cout << "print elements \n "; 
    	    }
    	    std::cout << elem << " ";
    });
    std::cout << std::endl;
    print_seq_container(list_new);
    print_seq_container(list);
    std::list<int> list_ = {1,3,5,5,7,8};
    list_.erase(std::remove(list_.begin(), list_.end(), 5), list_.end()); // низкая производительноть, поэтому луше работать с функциями членами
    print_seq_container(list_);
    // Заметим, что функция член remove не работает в ассоциатиыных контейнерах
    list_.remove(7); // Так как это список, то сдвигать элементы это очень дорого
	print_seq_container(list_);
	// Мы тут боремся  сдвумя разными проблемами, с одной стороны алгоритмы позволяют нами достичь обобщённости алгоритма по отношению к изменениям наших типов данных
	// Или самих контейнеров, с другой стороны мы должны ради быстродействия в основном пользоваться функциями - членами
	std::set<int> coll1;
	std::vector<int> coll2;
	for(int i = 1; i <= 9 ; ++i){
		coll1.insert(i);
	}
	print_seq_container(coll1);
	type_of_iterator(coll1);
	std::transform(coll1.begin(), coll1.end(), std::back_inserter(coll2), [](int elem){
		return elem * elem;
	});
	print_seq_container(coll2);
	// главное, чтобы критерием был некотороый фунциональный объект
	auto pos = std::find_if(coll1.begin(), coll1.end(), isPrime);
	if( pos != coll1.end()){
		std::cout << *pos << std::endl;
	}else {
		std::cout << "not found!" << std::endl;
	}
	std::deque<int> deq;
	type_of_iterator(deq); // random access 
	// рассмотрим как с помощью лямбда выражений определить критерий сортировки некоторых данных
	std::deque<Person> coll_person = {};
	coll_person.push_front(Person("Bob", "Dillan"));
	coll_person.push_front(Person("Mikhal", "Jordan"));
	print_seq_container(coll_person);
	std::sort(coll_person.begin(), coll_person.end(),
		[](const Person & p1, const Person & p2){
			return p1.lastname_ret() < p2.lastname_ret() || 
			(p1.lastname_ret() == p2.lastname_ret() &&
			 p1.firstname_ret() < p2.firstname_ret());	
		});
	print_seq_container(coll_person);
	auto cmp = [](const Person & p1, const Person & p2){
			return p1.lastname_ret() < p2.lastname_ret() || 
			(p1.lastname_ret() == p2.lastname_ret() &&
			 p1.firstname_ret() < p2.firstname_ret());	
		};
	std::set<Person, decltype(cmp)> coll_person_new(cmp);
	// Функция лямбда не имеет внутреннего состояния, которое бы могло сохраняться при повторных выводах нашего конструктора 
	// Функкциональные объекты могут это позврлить, по сути наши функторы
	// По сути функторы - это такие объекты, которые просто ведут себя как функция и не более
	//  функтор - это всё, что можно вызвать с помощью (args... ) и передаваемым объектам
	// Преимущества функциональных объектов:
	
	return 0;
}