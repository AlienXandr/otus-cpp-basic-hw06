Реализованы все доп. задания.

Все контейнеры наследуются от базового класса.

Реализована шаблонная функция print_container(BaseContainer<T> &container),
которая использует базовый класс.

# Проблема 1

Реализована шаблонная функция test_container(T &container, char *name)
Хотел использовать в этом шаблоне тоже базовый класс BaseContainer<T>,
однако, в контейнерах не получилось использовать базовый класс итератора.
Т.к. у разных контейнеров разные типы итераторов.
Например, в базовом классе объявлено, что метод begin() вернёт BaseIterator
virtual BaseIterator<T> begin() = 0;
А в контейнере приходится возвращать нужный тип итератора
VectorIterator<T> begin() { return VectorIterator(&data_[0]); };

# Проблема 2

Не смог понять как починить.
Если в базовом классе в перегрузке оператора [] указать в конце const
virtual const T &operator[](const size_t pos) const = 0;

и соответственно в контейнере BidirectionalListContainer
const T &operator[](const size_t pos) const override

то при сборке возникает ошибка:
/home/alexandr/Work/C++/Otus_basic/hw06/solution/containers/bidirectional_list_container.hpp: In instantiation of ‘const T& BidirectionalListContainer<T>::operator[](size_t)
const [with T = int; size_t = long unsigned int]’:
/home/alexandr/Work/C++/Otus_basic/hw06/solution/containers/bidirectional_list_container.hpp:132:12:   required from here
/home/alexandr/Work/C++/Otus_basic/hw06/solution/containers/bidirectional_list_container.hpp:140:15: error: passing ‘const BidirectionalListContainer<int>’ as ‘this’ argument
discards qualifiers [-fpermissive]
140 | return get(pos)->get_data();
|            ~~~^~~~~
/home/alexandr/Work/C++/Otus_basic/hw06/solution/containers/bidirectional_list_container.hpp:22:29: note:   in call to ‘BidirectionalDataNode<T>* BidirectionalListContainer<T>::
get(size_t) [with T = int; size_t = long unsigned int]’
22 | BidirectionalDataNode<T> *get(size_t pos) {
| ^~~

Если убрать в конце const в базовом классе и контейнере, то работает.
