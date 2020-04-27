

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdint.h>

// void * malloc(std::size_t size)
// void free(void * ptr)

// char bar[] = "hello" // read, write
// char foo* = "hello"; // read only
// Как бороться с фрагментацией
#define u8 uint8_t
#define u16 uint16_t
#define STACK_SIZE 32
#define HEAP_SIZE STACK_SIZE * 4
#define HEADER 4

static u16 IN_USE = 0; // Типо какого-то флага для дальнейшего использования

// Пусть мы хотим сделать произвольный аллокатор, который потсроен на куче и на стэке памяти и потом это использовать
typedef struct virtual_memory{
	u8 stack[STACK_SIZE]; // Размер Стэка фиксирован константой 32 // Тут хранятся только локальные переменные
	char ** unmapped;
	u8 heap[HEAP_SIZE]; // Аналогично м делаем его маленьким, сюда мы можем записывать только порядка 255 unsigned 
	// Мы инициализировали нашу кучу 128 байтами по определению

	struct 
	{
		char** data;
		char** bss; // read only data
		char** text; // 
		
	}data_t;
} virtual_memory;
//  Формально мы сделаем некоторую обёртку, чтобы не сразу обращаться к heap
typedef struct entity{
	u8* ptr; // Он возвращать формально будет указатель и размер данных куда мы хотим записать malloc
	u16 size;
}entity_t;

entity_t LIST[40]; //  Куда всё будет сбрасываться по умолчанию
// После вызова free
// Напишем метод на основе структуры данных entity_t который будеи искать свободное место для того, чтобы туда что-то положить
entity_t * new_entity(std::size size){ // std::size_t кроссплатформенный тип данных он гарантировано сможет обратиться к данных
	if(LIST[0].ptr == NULL && LIST[0].size == 0) // Пустые данные не инициализированные
	{
		static virtual_memory s_vm; // Позволяет в рамках этой функции быть вызвана один раз и существовать до конца завершения программы
		LIST[0].ptr = vm.heap;
		LIST[0].size = HEAP_SIZE; // Возможно он отслеживает состояние по отношению к запросу 
		IN_USE += 1;
	}
}

void* w_malloc(std::size_t size){ // Можно увеличивать heap
	assert(size <= HEAP_SIZE); // abborted dump
	size += HEADER; //  Какие - то методанные
	entity_t* e = new_entity(size);
}

void w_free(void * ptr){

}
void test(){
	int * a = w_malloc(sizeof(int));

}
int main(int argc, char const *argv[])
{
	
	return 0;
}