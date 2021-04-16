#include <iostream>
#include <time.h>
void stack_dynamic_array();
void static_array();
void explicit_heap_dynamic_array();

const int ITERATIONS = 100000;
const int ARRAY_SIZE = 10000;

int main() {

  //time for stack stack_dynamic_array
  clock_t begin = clock();
  for(int i = 0; i < ITERATIONS; i++)
    stack_dynamic_array();
  
  //stop timer
  clock_t end = clock();
  double stackTime = (double)(end-begin)/CLOCKS_PER_SEC;
  // print time
std::cout << "Time it took for stack: " << stackTime <<"\n";

  //time for stack static_array
  begin = clock();
  for(int i = 0; i < ITERATIONS; i++)
    static_array();
  //stop timer
  end = clock();
  // print time
   double staticTime = (double)(end-begin)/CLOCKS_PER_SEC;
  std::cout << "Time it took for static: " << staticTime <<"\n";

  //time for stack explicit_heap_dynamic_array
  begin = clock();
  for(int i = 0; i < ITERATIONS; i++)
    explicit_heap_dynamic_array();
  //stop timer
  end = clock();
  // print time
   double heapTime = (double)(end-begin)/CLOCKS_PER_SEC;
  std::cout << "Time it took for heap: " << heapTime <<"\n";
}

void stack_dynamic_array(){
  int stack_dynamic_array[ARRAY_SIZE];
}

void static_array(){
  static int static_array[ARRAY_SIZE];
}

void explicit_heap_dynamic_array(){
  int *explicit_heap_dynamic_array = new int[ARRAY_SIZE];
  delete[] explicit_heap_dynamic_array;
}
