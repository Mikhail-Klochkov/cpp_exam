// Асинхронизм в с++
// async, future, promise
// Мы рассмотрим вызов std::async что по сути позволят запускать программы на нескольких потоков одновременно
// Вернет она std::future - 

// Папаметры шаблонов по умолчанию
template <class T, class contsiner = std::vector<T>>
class MyClass;
MyClass<int> x1; // MyClass<int, std::vector<int>>


#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>

#include <stdexcept>
#include <limits>

// Любое значение переданное в идентификатор шаблона, воспринимается как значение без typename
template <class T>
class Myclass
{   
    public:
    void function(T & container){
		typename T::const_iterator first_el, last_el;
		typedef typename T::value_type type_container; 
		if(!container.empty()){
			first_el = container.cbegin();
			last_el = (--container.cend());
			std::cout << *first_el << "  " << *last_el << std::endl;
		}
		std::sort(container.begin(), container.end(), [](type_container & lhs, type_container & rhs){
		    return lhs < rhs;
		});
	std::copy(container.begin(), container.end(), std::ostream_iterator<type_container>(std::cout , "  "));
	
	}
};
namespace name_{
	class File;
	void foo(); // 
}
class Error{
	Error(){
		std::cout << "Exceptions is throw" << std::endl;
	}
};
void foo(){
	if(true){
		throw Error();
	}
}
int main(){
    Myclass<std::vector<int>> obj;
    std::vector<int> copy;
    typedef std::vector<int>::iterator it_vec;
    for(std::size_t iter = 0; iter < 5 ; iter++){
        copy.push_back(iter + 1);
    }
    obj.function(copy);
    foo();
    return 0;
}

std::pair<T1, T2> p; // Вообще объявлен в виде структуры, поэтому его члены открыты для преобразований
template <typename T1, typename T2>
std::ostream& operator << (std::ostream& strm, const std::pair<T1, T2>& p){
		return strm << "{" << p.first << "," << p.second << "}" << std::endl;
} // Такжее есть интерфейс, который ориентирован на кортежи, где мы получим вид:
std::get<0>(p); //c++11
std::get<1>(p);
typedef std::pair<int, double> Intdouble;
std::tuple_size<Intdouble>::value; // 2
std::tuple_element<Intdouble>::type ; // int

void f(std::pair<int , const char*>);
void g(std::pair<const int , std::string>);

void foo(){
	std::pair<int, const char*> p(42, "hello");
	f(p); // неявно генерирующий конструктор вызовется
	g(p); // необходимо вызвать шаблонный конструктор
}
// allocate просто по сути создают интерфейс для работы с данными объектами, где реализованы следующие операции:
namespace std{
template <class T>
class allocator;
}

a.allocate(num); // выделить память для num объектов 
a.construct(p,val); //  initialize object with pointer p and val - value
a.destroy(p); // уничтножает объекты на который ссылается указатель p
a.deallocate(p, num); // освободает память 

// Функциональность string 
 str.at();
 str.front();
 str.back();
 str.data(); // возвращает указатель на первый символ в строке
 std::stoi(); // преобразует в целове число нашу строку
 // Для типов контейнеров 
 // Каждый контейнерный класс имеет конструктор по умолчанию, копирующий конструктор и деструктор. 
 // Инициализация неупорядоченного множеста std::unordered_set
 std::unordered_set<std::string> w = {'hello', std::string(), " "};
 // У нас у set объектов вообще по определению представляет  собой ассоциативный контейнер с уникальным множеством ключей
// Поиск вставка и удаление объектов происходит за константное время  
std::vector<T> vector;
std::sort(vector.begin(), vector.end()); // faster then qsort in 20 times
conrainer;
sequence_type    assoc. sequence_type

std::vector  		std::set, std::multisetm, std::map, std::multimap 
std::list
std::deque

std::unordered_set<type>;  // реализована на Хэш таблицах
std::set<type> a;
a.insert(element, element_1, ...);
std::pair<std::iterator, bool> insert(const value_type & value);
// Сложность за логарифм от размера самомго контейнера и возвращает итератор на этот эелемент и идентификатор успешного или нет вставки
template <typename type>
std::iterator<type> insert(std::iterator<type> hint, const valyetype& value);
// Вообще говоря multiset поддерживает вхождения и одинаковых элементов
std::list<int> l;
std::vector<float> c(l.begin(), l.end());
//  По стандарту мы можем перемещать также используя итератор перемещания
std::list<std::string> l;
std::vector<std::string> c(std::make_move_iteraotr(l.begin()), 
											std::make_move_iteraotr(l.end()));
// Как же у нас реализован итератор перемещения 
std::array<std::string, N> coll = { ... };
std::array<int , N>, std::array<int, M> // anpoher type
std::list<type> list;
list.pop_front();
list.push_back();
list.pop_front();
// list.size() вроде как за линейное время.
std::forward_list<type> // не раеализованы операции push_back() and size() они очень долгие по сравнению с kist
{
	std::forward_list<long> coll = {...};
	coll.resize(10);
	coll.resize(10, 99); // Очень низкая производительность
	for(const auto elem : coll){
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}
//Ассоциативные контейнеры автоматически сортируют свои элементы в соответствии с определённым критерием
// Ассоциативные контейнеры, это просто бинарные деревья - скорее всего красно-черные деревья
// Как мы помнм изменять значение, которе находится в дереве, довольно дорого, так как придёться привести к неупорядоченому состоянию
// Множество - это коллекция в которой элементы сортируются в соттветствии с их значениями. Каждый элемент единственный в коллекции, дубликаты не допускаются
// Мультимножество - это такое множество допускающее дубликаты.
// map - отображение содержит пару (ключ-значение). Ключ нужен исключительно для сортировки элементов
// каждый ключ может входить в отображение только один раз, дубликаты не допускаются.
// Ассоциативный массив, где индекс имеет произвольный тип.
// Мульти отображение, по сути одинаковое то же самое с мультивмножетсвом. Несколлько дубликатов ключей.

std::multiset<std::string> cities = {"Volgograd", 'Samara', "Volgograd"};
for(const auto & elem: cities){
	std::cout << elem << " ";
}
std::cout << std::endl;

// insert очень обобщённая фигня, она бозваоляет вставлять из раных типов контейнеров в другие типы контейнеров
// Главное  следить за передаваемыми типами, чтобы шаблонный вывод не запутался
// Концепция initializer list озволяет нам сделать слудующее

std::container.insert(elem, first*, end*, {...});
// Также в map реализованы следующие элементы поиска
equal_range // возвращает набор элементов для конкретного ключ
// Unordered_set, unordered map
// Они реализованы на примере хэш- таблиц, где позиция конкретного элемента определяется его положением в ней
// Быстрый доступ к элементам, но поскольку объём требуемой памяти, для хранения элементов массива может быть очень большим
// Для экономии, мы храним элементы в таблице в виде связного списка, мы храним в одной ячейке сразу несколько элементов
// для использования обобщеннасти, чтобы код работал для всех видов итераторов, то стоит не исполтзовать следующий вид
for ( auto pos = coll.begin(), pos != coll.end(); ++pos){
	... // Тут для всех подойдёт
} 
for ( auto pos = coll.begin(), pos < coll.end(); ++pos){ //  только для итераторов произвольного доступа!
	... // не для всех типов контейнеров
} 
// ТО етсь не будет работать со списками множествами отображениями, которые определены только для двунаправленных итераторов
// set, multiset, map, multimap, list
// алгоритмы  - не элементы классов контейнепов, они есть глобальные функции работающие с итераторами!
//  парадигма функционального программирования
// Чтобы перезапись не происходила в несуществующие элемнты другого контейнера
// Надо использовать итераторы вставки
std::copy(coll1.begin(), coll1.end(), coll2.begin());
// для контейнеров list, deque, vector, forward_list, можно увеличивать на немного размер при разных операциях
coll2.resize(coll1.size());
std::deque<int> coll3(coll1.size());
std::copy(coll1.begin(), coll1.end(), coll3.begin());
// Щаблон класса
template <class T, class Allocator = std::allocator<T>> class vector;
// Определение шаблона класса бывает только глобальным
// последовательные итераторы unordered_map, forward_list, unordered set
// Двунаправленные потом list, set, map 
template<
    class Category, // Категория итератора 
    class T, // тип данных на что указывает итератор
    class Distance = std::ptrdiff_t, // Расстояние между итераторами
    class Pointer = T*, // тут понятно просто кказатель на тип данных 
    class Reference = T& //  ссылка
> struct iterator; // реализация обычного итаратора
// по сути iterator_traits - позволяет сделать такующаблонную надстройку, что позволит вывести все специфические типы(параметры шаблона класса class Itarator)
Category // по сути определяет тип итератора 
std::forward_iterator_tag 
std::input_iterator_tag
std::random_access_iterator_tag
std::bidirectional_iterator_tag  // по сути мы уже пробежались по таким видам итераторов, которые реализованы для разных типов данных
{
	typedef std::iterator_traits<itr> traits;
	if(typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag)){
		std::cout << "int* it's a random_access_iterator_tag" << std::endl;
	}
} // 

template <class Container>
std::insert_iterator<Container> inserter (Container &c, typename Container::iterator i){
	return std::insert_iterator<Container>(c, i); // Как мы видим просто есть шаблонная вспомогательная функция для вывода типа итератора вставки
}
// операция для std::forward_list<> не имеет операции push_back так как она оч дорогая
// push_front, pop_front также как и нет операции вставки в конец, то и нет вставки в произвольнгое место - дорогая операция за линейное время
// В ассоциативном контейнере нет смысла передавать какую-то позицию для вставки ибо элементы расположены по размному в ней
// для итераторов потока, просто мы рассматриваем поток, как коллекцию аналогично тому как это делают обычные иттераторы 
// Работать с двунаправленными итераторами и произвольного доступа можно как инверсного итератора 
std::set<>, std::unordered_set, std::unordered_mapm std::map std::unordered_map
// С такими контейнерами нельзя делать инферсные иттераторы
std::copy(coll.crbegin(), coll.crend(),
	std::ostream_iterator<int>(std::cout, "  ")); 
*coll.crend() // оно не определено
// erase с ассоциативными контейнерами 
set.erase(value)-> returned a number of deleted elements
class X{
	public:
		return_value operator()( ... ) const;
		...
};
X fo;
fo(arg1, arg2)
// equalent 
fo.operator()(arg1, arg2)

std::for_each(begin, end, functor()); // операция functor() - создаёт временный объект класса X который передан алгоритму в качестве некоторого аргумента
namespace std{
	template <typename Iterator, typename Operation>
	Operation for_each(Iterator act, Iterator end, Operation op){
		while(act != end){
			op(*act); // X::operator()(*act)
			++act;
		}
		return op;
	}
}
// У нас есть также стандартные функциональные объекты для STL
std::set<int, std::greater<int>> // include <functional>
std::set<int, std::less<int>>
std::negate<int>() // Унитарный функциональынй объект а не бинарный
std::multiplies<int>() // binary functional object
std::transform(coll1.begin(), coll1.end(), coll2.begin(), // first, second, point of where is we want to add elements
							coll1.begin(),
							std::multiplies<int>());
// Лямбда функции более интуитивные пользоваталю, но они определны неявно и быстрее, в отличии от многих функциональных объектов
// Нет внутреннего состояния, некуда записывать, падает вариативность
// Контейнеры, итераторы и алгоритмы по определению являются шаблонными

// 1) Элементы контейнеров должны неявно иметь копирующий и перемещающий конструктор
В контейнерах STL использована семантика значений, 
происходит копирования значения при создании объекта, нет семантики ссылок, 
но можно делать с помощью интелектуальных указателелей 
void Myfunc(int c){
	if(c > std::numeric_limits<char>::max()){
		throw std::invalid_argument("My funct argument too large");
	}
}
try{
		Myfunc(1);
	}catch(std::invalid_argument & e) // Мы тут отлавливаем конкретный тип ошибки, которая нам нужна
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

template <typename T>
class EqualComparable{

	public:
		friend bool operator != (const T & x1, const T &  x2){
			return !(x1 == x2);
		} 
};
class X : public EqualComparable<X>
{
public:
	friend bool operator != (const X & x1, const X & x2){
		// realizations of comparable of X class
	}	
};
template <typename T>
class Matrix{
	private:
		T arr[SIZE][SIZE];
		template <typename T>
		friend std::ostream & operator <<<T>(std::osteram & , const Matrix &); // Мы показываем, что это такое в качестве нашей реализации
		friend std::ostream &  operator >><T>(std::ostream & , const Matrix &);
};

template <typename T>
std::ostream &  operator >> (std::istream & strm, const Matrix<T> & matrix){
	...
}

template <typename T>
std::ostream &  operator << (std::ostream & strm, const Matrix<T> & matrix){
	...
}
[capture](type args...) mutable throw() -> return_value {
	     //something doing;
};
int m = 0;
int n = 0;
[&, n](int a){ m = ++n + a}(4);
std::cout << m << std::endl << n << std::endl;
m = 5
n = 0
//


template<typename T> // Пользовательский тип например
bool operator <= (const T & lsh, const T & rhs){
	// Мы подразумеваем, что они как-то перегружены
}


std::stable_sort(randIT, randIT, бинарный предикат(std::greater, std::less)) // Логарифм
template <typename T, typename T>
bool pred(const T& lhs, const T& rhs) const{ // Можно применять к иткраторам(контейнерам которые подразумевают итераторы общего доступа)
	return exxpress(lhs, rhs); // deque, vector, array, ///
} 
std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
 
std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
std::cout << "The median is " << v[v.size()/2] << '\n';
 // то есть сортировка только до определённого диапазона
std::nth_element(v.begin(), v.begin()+1, v.end(), std::greater<int>()); //  partial sorting algorithms
std::cout << "The second largest element is " << v[1] << '\n';
std::generate
std::generate_n(начало, сount, functional obj)
std::copy
std::copy_n // аналогично видимо тому как происходит в std::generate_n
std::copy_if // predicate
std::remove(begin, end, value)
std::remove(begin, end, predicate)
std::remove_copy //  (begin, end, begin_another , value) // value - те значения, которые не стоит копировать
std::remove_copy_if// (begin, end, begin_another , predicate) // аналогия полная 
std::move // Он только после перемещаения объекта вызывает его деструктор
////////////
std::set // функции члены для операций над set
// Все, что с поиском за log(n)
set.find(val)
// не меньше чем переданное значение по определению
set.lower_bound(val) // возвращает первый элемент(скорее всего указатель, со значением >= val)
set.count(val) // number of elements with value (val)
set.upper_bound // больше чем значение val
// all container(тут правда нет ни push_back ни pop.back, push.front, pop.front)
only set.insert()
set.earse()// iterator, or range, or key of value  
// Алгоритмы для сортировок разного рода последовательностей описание
// СОРТИРОВАННЫЕ ПОСЛЕДОВАТЕЛЬНОСТИ //
set::lower_bound(begin, end, value) // Основан на последовательном типе итераторов
// complexity of O(log(range)) not less then
set::upper_bound(begin, end, value) // greater then value
// Также такие штуки имеют compare объект, чтобы он был не дефолтный определённый реляционным итераторов
set::set_intersections(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v_intersections)) //  определяет множество пересечения
// Мы сюда передали оператор вставки в конец


// Требования к итераторам вывода!!!!!!!!!!!! 
// Иттераторы выовода могут только перемещаться вперёд, то есть для них определена только инкрементация и последовательное присвоение знаечния элементам посл-сти
// OUTPUT ITERATOR
// 1) 

// ... Завтра допишем

// АЛГОРИТМЫ РАБОТЫ С ПЕРЕСТАНОВКАМИ, СЛУЧАЙНОЕ УПОРЯДОЧИВАНИЕ
std::reverse(first, last) // Дожен соответствовать Bidir
std::reverse_copy(first, last, pointer_copy) // BIdir
std::rotate() // 
std::rotate_copy
std::next_permutation
std::prev_permutation
std::shuffle
std::random_shuffle

// Содержанеи заголовочного файла utility 
// 1) Содержи пространство имён rel_ops который имеет набор шаблонов, которые определяют поведение по умолчанию для 
// реляционных операторов > >= <= != на основе оперторов определённых пользователем == < 
// 2) Ну и для pair мы тоже можем всё рассказать - по сути это кортежи пространство кортежей с помощью этого типа определены пары ключ - значение в отображениях//


// ФУНКЦИОНАЛЬНОСТЬ UNORDERED_MAP
// 

// Иттераторы 
template < class Iterator > class iterator_traits;
template < class T > class iterator_traits<T*>;
template < class T > class iterator_traits<const T*>; // 

// Специализация шаблонов 
template <class T>  class vector{ //  Тут при объявлении может T иметь любой тип (ссылка, указатель, двойной указатель .. что угодно)
	...
};
template <class T>  class vector<T*>{ // То он сработает только на указатель
	...
}; 
template typename T1, typename T2>
class pair{
public:
	first;
	second; //  пользовательские
}
template <typename T1, typename T2> 
bool operator < (const T1& x_1, const T2& x_2){ // Для наших first and second должна быть определена  операция < == 
	return (x1.first < x2.first) || (!(x_1.first < x2.first) && x1.second < x2.second);
}  // аналггично мы построим отсальные
// в данном есть пространство имён rel_op std::rel_op // туда входят все шаблоны реляционных итераторов для шаблонов разных классов
// По сути они просто доопределяются раньше
template <typename T>
bool operator !=(const T & x, const T & y){
	return !(x == y);
}
// АЛЛОКАТОРЫ В ОПРЕДЕЛЕНИИ
#include <memory> // она может быть не стандартная new, delete освободение и тд 
const_pointer
const_reference
difference_type // целочисленный тип обозначающий разницу между указателями на тип объекта управляемого распрделеителем
pointer
reference // 
size_type  // Тип размера данных
value_type // ТИп управляемый распределителем памяти

// Функции 
address // адрес объекта значение которого задано
!allocate // malloc там не вызывает конструктор для элемента который под данный аллокатр Выделяет блок памяти для хранения элементов определённого размера
!construct // 
!deallocate
!destroy
max_size
rebind

construct // создаёт определённый тип объекта оп указанному адрему
void construct(pointer ptr, const Type & val); // lvalue
void construct(pointer ptr, Type&& val); // Чтобы поддерживать rvalue 

pointer address(reference val) const;
const_pointer address(const_reference val) const;
pointer allocate(size_type size, const void* _Hint); // Значение сколько элементов нам надо выделеить и есть в качестве помощника указатель, для поиска места в памяти
// либо вернёт все ноомально, либо null
std::uninitialised_copy(first, last, Forw_It) //  Что-то копируем вообще говоря в неинициализированные участки памяти--  очень быстро работает 

// Концепция виртуальных методов необходимма, чтобы у нас при наследовании базоваого класса другим(при определённом наследовании)
class Animal{
public:
	void move(){
		...
	}
	virtual void eat(){
		...
	}
	vitrual ~Animal(){} // destructor
};

class Wolf: public Animal{
	voif move(){
		...
	}
	void eat(void()){ // Он переопределён и также является виртуальным методом
		...
	}
}
int main(){ // виртуальрные методы работают независимо от типа какого указателся приводим
	Animal* zoo[] = {new Wolf(), new Animal()} ;
	for(Animal* a: zoo){
		a->move();
		a->eat(); // Будет вызвана реализация конкретно для того 
		delete a; // для каждого вызовется свой деструктор он тоже Виртуальный
	}
}
std::vector<int> v;
std::generate_n(std::back_insert_iterator<std::vector<int>>(v), 10, [n=0]() mutable{
	return ++n;
})
std::next(it, number_of_increments)
template <class Forw_It>
Forw_It next(Forw_It it,
	typename std::iterator_traits<Forw_It>::difference_type n = 1);

template <class InputIt>
Forw_It next(Forw_It it,
	typename std::iterator_traits<Forw_It>::difference_type n = 1);

// SMART POINTERS 
1. Предотвращают утечку памяти
2. Автоматическая Инициализация
3. Отсутствие проблем с указатеелями на уже удалённые объекты
4.С помощью них можно организовывать сборку мусора
5. Повысить эффективность кода

// std::unique_ptr 
// Его нельзя копировать 
// НО передачу можно осуществлять с помощью move семантики std::move
// При уничтожении объекта автоматически вызывается деструктор объекта(на который он ссылается)
std::unique_ptr<Someclass> unq(new Someclass(\...\)); // Тут в качестве аргумента конструктора передаётся указатель на только-что инстанцированный объект класса SomeClass
auto unq = std::make_unique<SomeClass>(/../);
// Класс Unique_ptr перегружает сам -> чтобы мы могли достучаться до публичных методов класса объекта
// У нас получается единоличное владение объектом 

template <class T, class Deleter = std::default_delete<T>> class unique_ptr;
// По выходу из области видимости создания данного указателя, просиходит разрушение объекта из области видимости
// По умолчанию объект удаляется std::default_deleter<T> // 
template <class T> class vector {
	...//неспециализированный шаблон
}
template <class T> class vector<T*>{
	... // Частично специализированный шаблон
}
template <class T> class vector<void*> // полность специализированный шаблон
template <typename Arg1, typename Arg2, typename Results > binary_function{
	typedef Arg1 first_argument;
	typedef Arg2 second_argument;
	typedef Results Result_type;;
}
struct compare : pyblic std::binary_function<int, int, bool> {
	bool operator() (int a , int b) {
		return a == b;
	}
}
template <typename T1, typename T2>