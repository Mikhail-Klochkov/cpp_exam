#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <queue>
#include <functional>
#include <utility> // std::pair<> // std::move

template <class Container>
void print_seq(const Container & container){
    typedef typename Container::value_type type_cont;
    std::copy(container.begin(), container.end(), std::ostream_iterator<type_cont>(std::cout, " "));
    std::cout << std::endl;
} 
template <typename T> void print_queue(T & q){
    while(!q.empty()){
        std::cout << q.top() << " "; // аналогично посмореть вверх( голову )
        q.pop(); // only head 
    }
    std::cout << "\n";
}
struct Foo{
    Foo() {std::cout << "Foo::Foo\n";}
    ~Foo() {std::cout << "Foo::~Foo\n";}
    void bar() {std::cout << "Foo::bar\n";}
};
void f(const Foo& foo){
    std::cout << "f(const Foo&\n";
}
int main()
{
    std::vector<int> v1;
    std::vector<int>::iterator v1iter;
    std::vector<int>::allocator_type v1Alloc;
    int i;
    for ( i = 1 ; i <= 7 ; i++ )
    {
          v1.push_back( 2 * i );
    }
    std::cout << "The original vector v1 is:\n ( " ;
    for ( v1iter = v1.begin( ) ; v1iter != v1.end( ) ; v1iter++ )
           std::cout << *v1iter << " ";
    std::cout << ")." << std::endl;
    
    std::allocator<int>::const_pointer v1ptr;
    const int k = 8;
    v1ptr = v1Alloc.address(*std::find(v1.begin(), v1.end(), k)); // ПО идее он должен вернуть указатель, где в памяти расположен элемент с k = 8
    std::cout << *v1ptr << "\n";
    
    
    std::allocator<int> v1alloc; //  Шаблонный тип помогает понять, что нам надо распределить
    std::allocator<int>::pointer ptr_all;
    std::size_t N = 10;
    ptr_all = v1alloc.allocate(N);
    
    for( int i = 0; i < 10; ++i){
        ptr_all[i] = i;
    }
    std::copy(ptr_all, ptr_all + N, std::ostream_iterator<int>(std::cout , "  "));
    v1alloc.deallocate(ptr_all, N);
    const int ka = 6;
    const int kb = 7;
    std::allocator<int>::pointer it_f = v1Alloc.address(*std::find(v1.begin(), v1.end(), ka)); 
    v1Alloc.destroy(it_f);
    v1Alloc.construct(it_f, kb);
    print_seq(v1);
    std::priority_queue<int> q;
    for(int n : {1,8,5,6,3,4,0,9,7,2}){ // при вставке он ищет место в очереди то есть сложность будет логарифмическая
        q.push(n); // only tail of queue
    }
    print_queue(q); // Наверху будет максимальный элемент 
    std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(n);
 
    print_queue(q2); // В другой последовательности
    std::vector<int> v_n = {1,2,3,5,6};
    int n = 0;
    std::generate_n(std::back_insert_iterator<std::vector<int>>(v_n), 2, [&n](){
                           return ++n;
    });
    print_seq(v_n);
    n = 0;
    std::generate_n(std::insert_iterator<std::vector<int>>(v_n, std::next(v_n.begin(), 3)), 2, [&n](){
                                            return ++n;
    });
    print_seq(v_n);
    std::unique_ptr<Foo> p1(new Foo); // Создаст единственный объект 
    if(p1){
        p1->bar();
    }
    {
        // another block
        std::unique_ptr<Foo> p2(std::move(p1)); // move используется, чтобы решить может ли объект быть перемещён
        f(*p2);
        p1 = std::move(p2);
        std::cout << "destroying p2..\n";
    }
    if(p1) p1->bar();
    // Экземпляр foo уничтожен, когда пора покидать область видиости 
    // аларрвы
    return 0;
}
