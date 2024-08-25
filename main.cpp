#include "containers/bidirectional_list_container.hpp"
#include "containers/dynamic_container.hpp"
#include "containers/fixed_size_container.hpp"
#include <iostream>
#include <vector>

template <typename T> void print_container(BaseContainer<T> &container) {
  for (size_t i = 0; i < container.size(); ++i) {
    std::cout << container[i] << ' ';
  }
  std::cout << std::endl << std::endl;
}

template <typename T> void test_container(T &container, char *name) {
  std::cout << "===== Test \"" << name << "\"===== \n";

  std::cout << "1. Добавление в контейнер десяти элементов (0, 1 … 9)\n";
  for (int i = 0; i < 10; ++i) {
    container.push_back(i);
  }
  print_container(container);

  std::cout << "2. Вывод размера контейнера\n";
  std::cout << container.size() << std::endl;
  std::cout << std::endl;

  std::cout << "3. Удаление третьего (по счёту), пятого и седьмого элементов\n";
  std::vector<size_t> arr{3, 5, 7};
  for (int i = 0; i < arr.size(); i++) {
    container.erase(arr[i] - (i + 1));
  }
  print_container(container);

  std::cout << "4. Добавление элемента 10 в начало контейнера\n";
  container.push_front(10);
  print_container(container);

  std::cout << "5. Добавление элемента 20 в середину контейнера\n";
  container.insert(4, 20);
  print_container(container);

  std::cout << "6. Добавление элемента 30 в конец контейнера\n";
  container.push_back(30);
  print_container(container);

  std::cout << "7. Итератор с мат. операциями\n";
  auto it = container.begin();
  std::cout << *it << std::endl;
  std::cout << *(++it) << std::endl;
  std::cout << *(++it) << std::endl;
  std::cout << *it << std::endl;
  std::cout << *(--it) << std::endl;
  std::cout << *(--it) << std::endl;
  std::cout << *(it + 2) << std::endl;
  std::cout << *((it + 4) - 1) << std::endl;
  std::cout << *it << std::endl;
  std::cout << std::endl;

  std::cout << "8. Итератор в цикле\n";
  for (auto it = container.begin(); it != container.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << std::endl << std::endl;
}

int main() {
  FixedSizeContainer<int, 10> fixed_size_container;
  test_container(fixed_size_container, "FixedSizeContainer<int, 10>");

  DynamicContainer<int> dynamic_container;
  test_container(dynamic_container, "DynamicContainer<int>");

  BidirectionalListContainer<int> bidirectional_list_container;
  test_container(bidirectional_list_container,
                 "BidirectionalListContainer<int>");

  std::cout << "===== Test Copy ===== \n";
  DynamicContainer<int> dynamic_container_2{dynamic_container}; // Copy ctor
  dynamic_container_2 = dynamic_container; // Copy assignment operator

  std::cout << "===== Test Move ===== \n";
  DynamicContainer<int> dynamic_container_3{
      std::move(dynamic_container)}; // Move ctor

  dynamic_container_3 =
      std::move(dynamic_container_2); // Move assignment operator

  return 0;
}