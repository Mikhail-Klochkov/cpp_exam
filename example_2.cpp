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
#include <stdexcept>
#include <limits>

// Тут много будет алгоритмов для демонстрации их поведения
template <class ForwardIt, class Generator> // такая реализация может быть
void generate(ForwardIt first, ForwardIt last, Generator g){
	while(first != last){
		*first++ = g();
	}
}
template <class Container>
void print_seq_container(const Container & container){
	typename Container::const_iterator it = container.cbegin();
	while(it != container.cend()){
		std::cout << *it++ << "  ";
	} 
	std::cout << std::endl;
}
int main(){
		std::vector<int> v(5); // заранее определяем размер куда мы заполним элементы
		std::generate(v.begin(), v.end(), std::rand); // rand()
		print_seq_container(v);
		std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
	    auto lower = std::lower_bound(data.begin(), data.end(), 4);
	    auto upper = std::upper_bound(data.begin(), data.end(), 4);
	    std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
	    // Они реализованы для последовательных иттераторов то есть можно для любых типов контейнеров применять такие операции
	    std::vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	    std::fill_n(std::back_inserter(v2), 3, -1); //  (pos_insert, fill_value, value)
	    for (int & i : v2){               
	    	std::cout << i << " ";
	    }
	    std::cout << std::endl; // Напрмер пусть мы хотим заполнить только что инициализированный вектор, для которого мы вообще говоря не выделили память
	    // Далее мы хотим сгенерировать значения, которые его заполнят с конца, в таком случае мы получим
	   	std::vector<int> v3;//is empty by default
	   	int n = 0;
	   	std::generate_n(std::back_insert_iterator<std::vector<int>>(v3), 10, 
	   							[&n](){return ++n;});
	   	// Мы тут реализовали std::back_insert_iterator // Скорее всего позволяет создать определёный тип итератора, который инекрементируется вперёд
	   	print_seq_container(v3);
	   	std::vector<int> v4;//is empty by default
	   	n = 0;
	   	std::generate_n(std::back_inserter(v4), 10, // append конструкция реализована 
	   							[&n](){return ++n;});
	   	print_seq_container(v4);
	   	//std::back_insert_iterator<Container type>(continer) == std::back_inserter(container)
		// То есть просто шаблонная надстройка
		std::ostream_iterator<int> it(std::cout, " ");
		*it = 4;
		//std::cout << ((bool) &it == &it++ )<< std::endl;
		// алгоритмы работы с перестановками, случайное упорядочивание 
		std::rotate(v2.begin(), v2.begin() + 3, v2.begin()++);
		print_seq_container(v2);
	return 0;
}