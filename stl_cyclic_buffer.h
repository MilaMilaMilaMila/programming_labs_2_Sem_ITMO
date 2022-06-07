#include <iostream>
#include <algorithm>
#include <vector>
#include <ostream>

template <class Tp, class Allocator = std::allocator<Tp>>
class CyclicBuffer
{
private:
    // size_t это как unsigned int
    Tp *_buffer; // pointer on array type Tp
    size_t _head = 0; // индекс первого элемента
    size_t _tail = 0; // индекс элемента после последннего
    size_t _max_size; // максимальное количество элементов в буфере
    Allocator _alloc; // for work with memory

    // we use random_access_iterator_tag bcs it corresponds to
    // LegacyRandomAccessIterator, which can be moved to point to any element in constant time.
    //(перемещать, чтобы указывать на любой элемент)
    struct iterator : std::iterator<std::random_access_iterator_tag, Tp>
    {
        int index; // current index
        friend class Cyclic_Buffer; // friend allow use private member
        CyclicBuffer *cyc_buf; // container which use iterator

        iterator(size_t index, CyclicBuffer *cyc_buf) : index(index), cyc_buf(cyc_buf) {} // constructor

        Tp &operator*() const { return cyc_buf->_buffer[index]; } // разыменовываем итератор - работаем со значением элемента по ссылке

        Tp *operator->() const { return cyc_buf->_buffer[index]; } // получаем значене элемента из указателя

        iterator operator++(int) // index post-increment
        {
            auto before = *this;
            ++(*this);
            return before;
        }

        iterator &operator++() // index pre-increment
        {
            index = (index + 1) % cyc_buf->_max_size;
            return *this;
        }

        iterator &operator+=(int n) // increase inedx on n
        {
            index = (index + n) % cyc_buf->_max_size;
            return *this;
        }

        iterator operator--(int) // index post-decrement
        {
            auto before = *this;
            --(*this);
            return before;
        }

        iterator &operator--() // index pre-decrement
        {
            index = index > 0 ? index - 1 : cyc_buf->_max_size - 1;
            return *this;
        }

        iterator &operator-=(int n) { return *this += -n; } // decrease index on n

        Tp &operator[](int n) const { return cyc_buf->_buffer[n]; } // det value by index
    };

    struct const_iterator : std::iterator<std::random_access_iterator_tag, const Tp>
    {
        size_t index;
        friend class Cyclic_Buffer;
        CyclicBuffer *cyc_buf;

        const_iterator(size_t index, CyclicBuffer *cyc_buf) : index(index), cyc_buf(cyc_buf) {}

        const_iterator(iterator it) : const_iterator(it.index, it.cyc_buf) {}

        const Tp &operator*() const { return cyc_buf->_buffer[index]; } // not allow change value from reference

        const Tp *operator->() const { return cyc_buf->_buffer[index]; } // not allow change value from reference

        const_iterator operator++(int)
        {
            auto before = *this;
            ++(*this);
            return before;
        }

        const_iterator &operator++()
        {
            index = (index + 1) % cyc_buf->_max_size;
            return *this;
        }

        const_iterator &operator+=(int n)
        {
            index = (index + n) % cyc_buf->_max_size;
            return *this;
        }

        const_iterator operator--(int)
        {
            auto before = *this;
            --(*this);
            return before;
        }

        const_iterator &operator--()
        {
            index = index > 0 ? index - 1 : cyc_buf->_max_size - 1;
            return *this;
        }

        const_iterator &operator-=(int n) { return *this += -n; }

        const Tp &operator[](int n) const { return cyc_buf->_buffer[n]; }
    };

public:

    explicit  CyclicBuffer(size_t max_size, Allocator allocator = std::allocator<Tp>()) : _max_size(max_size + 1), _alloc(allocator)//
    {
        _buffer = allocator.allocate(max_size + 1); // allocates uninitialized storage
    };

    // copy operator
    CyclicBuffer(const CyclicBuffer<Tp> &cyc_buf) : CyclicBuffer(cyc_buf._max_size - 1)
    {
        _alloc = std::allocator_traits<Allocator>::select_on_container_copy_construction(_alloc); // obtains(получает) the allocator to use after copying a standard container
        for (size_t i = 0; i <= _max_size; ++i) _alloc.construct(_buffer + i, cyc_buf._buffer[i]); // constructs an object in allocated storage
    };

    // add {array} in back
    //call as constructor Cyclic_ Buffer cyc_buf{, , , }
    CyclicBuffer(std::initializer_list<Tp> list) : CyclicBuffer(list.size())
    {
        for (auto el : list) push_back(el);
    }

    ~CyclicBuffer() { _alloc.deallocate(_buffer, _max_size); }

    // оператор присваивания
    CyclicBuffer &operator=(const CyclicBuffer<Tp> &cyc_buf)
    {
        if (this == &cyc_buf)
            return *this;

        Tp *new_cyc_buf = _alloc.allocate(cyc_buf._max_size); // выделили память нового размера
        size_t old_size = _max_size; // запомнили старый размер
        _max_size = cyc_buf._max_size; // обновили разммер

        for (size_t i = 0; i < _max_size; ++i)// проходимся по новым объектам
        {
            _alloc.construct(new_cyc_buf + i, cyc_buf._buffer[i]); // копирование новых объектов в новую память
            _alloc.destroy(_buffer + i); // уничтожение старых объектов
        }

        _alloc.deallocate(_buffer, old_size); // освобождение старой памяти
        _buffer = new_cyc_buf; // присваиваем нашему буферу новую памятьс новыми значениями
        return *this;
    }

    void push_back(Tp item)
    {
        if (is_full()) throw std::runtime_error("Error: Buffer is full!!!");
        _alloc.construct(_buffer + _tail, item); // создание нового объекта в конце буфера
        _tail = (_tail + 1) % _max_size; // обновление длины хвоста
    }

    void push_front(Tp item)
    {
        if (is_full()) throw std::runtime_error("Error: Buffer is full!!!");
        size_t new_head = _head > 0 ? _head - 1 : _max_size - 1; // если голова в нуле, то записываем с конца блока памят
        // если голова сдвинулась вправо, то записываем левее на 1
        _alloc.construct(_buffer + new_head, item);
        _head = new_head;
    }

    Tp pop_front()
    {
        if (is_empty()) throw std::runtime_error("Error: Buffer is empty!!!");
        Tp destroyed = _buffer[_head]; // запоминаем уничтожаемый объект
        _alloc.destroy(_buffer + _head); // уничтожаем
        _head = (_head + 1) % _max_size; // обновляем голову
        return destroyed; // возвращаем уничтоженный первый объект
    }

    Tp pop_back()
    {
        if (is_empty()) throw std::runtime_error("Error: Buffer is empty!!!");
        size_t new_tail = _tail > 0 ? _tail - 1 : _max_size - 1; // считаем индекс удаляемого элемеента с конца
        Tp destroyed = _buffer[new_tail]; // запоминаем уничтожаемый объект
        _alloc.destroy(_buffer + new_tail); // уничтожаем
        _tail = new_tail; // обновляем хвост
        return destroyed;
    }

    size_t size()
    {
        if (_tail >= _head) return _tail - _head;
        return _max_size - (_head - _tail);
    }


    void change_max_size(size_t new_max_size)
    {
        new_max_size++;
        if (new_max_size < size())  throw std::runtime_error("Error: You cannot make the buffer size smaller than the current number of elements in it!");
        if (_max_size == new_max_size) return;

        Tp *new_cyc_buf = _alloc.allocate(new_max_size);
        for (size_t i = 0; i < size(); ++i)
        {
            _alloc.construct(new_cyc_buf + i, operator[](i)); // копируем старые элементы в новую память
            _alloc.destroy(_buffer + ((_head + i) % new_max_size));// уничтожаем старые эллементы в старой памяти
        }

        _head = 0;
        _tail = size() + 1;
        _alloc.deallocate(_buffer, _max_size); // освобождаем старую память
        _buffer = new_cyc_buf; // обновляем контейнер
        _max_size = new_max_size; // обновляем размер
    }

    friend std::ostream &operator<<(std::ostream &out, CyclicBuffer &_buffer)
    {
        out << "\nBuffer Stat:";
        out << "\nSize/Max_Size: " << _buffer.size() << " / " << _buffer._max_size - 1 << '\n';
        if (_buffer.size() == 0)
        {
            out << '\n';
            return out;
        }

        out << "Elements in buffer: ";
        for (size_t i = 0; i < _buffer.size(); ++i)
            out << _buffer[i] << (i == _buffer.size() - 1 ? "\n\n" : " ");
        return out;
    }

    Tp &operator[](size_t index) { return _buffer[(_head + index) % _max_size]; } // взятие по индексу по ссылке

    const Tp &operator[](size_t index) const { return _buffer[(_head + index) % _max_size]; }  // взятие по индексу по конст ссылке

    bool is_empty() const { return _head == _tail; } // проверка что пустой

    bool is_full() const { return (_tail + 1) % _max_size == _head; } // проверка что полный

    const Tp &front() const { return _buffer[_head]; } // взятие первого элемента по ссылке

    const Tp &back() const { return _buffer[_tail > 0 ? _tail - 1 : _max_size - 1]; } // взятие последнего элемента по ссылке


    iterator begin() { return iterator(_head, this); } // возаращает итератор на первый элемент

    iterator end() { return iterator(_tail, this); } // возаращает итератор на последний элемент

    const_iterator begin() const { return const_iterator(_head, this); }

    const_iterator end() const { return const_iterator(_tail, this); }

    friend bool operator==(const iterator &lhs, const iterator &rhs) { return lhs.index == rhs.index; } // индексы равны

    friend bool operator!=(const iterator &lhs, const iterator &rhs) { return !(lhs == rhs); } // индексы не равны

    friend bool operator<(const iterator &lhs, const iterator &rhs) // !!!!
    {
        if (lhs.index > lhs.cyc_buf->_head && rhs.index > rhs.cyc_buf->_head) return lhs.index < rhs.index; // оба правее головы
        else if (lhs.index > lhs.cyc_buf->_head) return true; // левый правее головы, а правый в хвосте(правый больше)
        else if (rhs.index > rhs.cyc_buf->_head) return false; // правый правее головы, а левый в хвосте(левый больше)
        else return lhs.index < rhs.index; // оба в хвосте - можно просто сравнить
    }

    friend bool operator<=(const iterator &lhs, const iterator &rhs) { return !(rhs > lhs); }

    friend bool operator>(const iterator &lhs, const iterator &rhs) { return rhs < lhs; } // как < только лево и право поменяли

    friend bool operator>=(const iterator &lhs, const iterator &rhs) { return !(lhs < rhs); } // больше или равно == не меньше

    void swap(iterator &a, iterator &b) { std::swap(a.index, b.index); } // меняем местами индексы итераторов - то есть первый итератор будет указыват на второй и наоборот

    void swap(const_iterator &a, const_iterator &b) { std::swap(a.index, b.index); } // меняем местами индексы итераторов - то есть первый итератор будет указыват на второй и наоборот

    friend iterator operator+(iterator it, int n)
    {
        it += n; // += переопределено в struct iterator
        return it;
    }

    friend iterator operator-(iterator it, int n)
    {
        it -= n; // -= переопределено в struct iterator
        return it;
    }

    friend iterator operator+(int n, iterator it) { return it + n; }

    friend int operator-(const iterator &lhs, const iterator &rhs) // !!
    {
        int l = lhs.index >= lhs.cyc_buf->_head ? lhs.index - lhs.cyc_buf->_head : lhs.cyc_buf->_max_size - (lhs.cyc_buf->_head - lhs.index); // считаем фактический номер элемента
        int r = rhs.index >= rhs.cyc_buf->_head ? rhs.index - rhs.cyc_buf->_head : rhs.cyc_buf->_max_size - (rhs.cyc_buf->_head - rhs.index); // считаем фактический номер элемента
        return l - r; // ищем разницу
    }

    // все то же самое для конст итераторов
    friend bool operator==(const const_iterator &lhs, const const_iterator &rhs)
    {
        return lhs.index == rhs.index;
    }

    friend bool operator!=(const const_iterator &lhs, const const_iterator &rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const const_iterator &lhs, const const_iterator &rhs)
    {
        if (lhs.index > lhs._buffer->_head && rhs.index > rhs._buffer->_head)
            return lhs.index < rhs.index;
        else if (lhs.index > lhs._buffer->_head)
            return true;
        else if (rhs.index > rhs._buffer->_head)
            return false;
        else
        {
            return lhs.index < rhs.index;
        }
    }

    friend bool operator>(const const_iterator &lhs, const const_iterator &rhs) { return rhs < lhs; }

    friend bool operator<=(const const_iterator &lhs, const const_iterator &rhs) { return !(rhs > lhs); }

    friend bool operator>=(const const_iterator &lhs, const const_iterator &rhs) { return !(lhs < rhs); }

    friend const_iterator operator+(const_iterator it, int n)
    {
        it += n;
        return it;
    }

    friend const_iterator operator+(int n, const_iterator it) { return it + n; }

    friend const_iterator operator-(const_iterator it, int n)
    {
        it -= n;
        return it;
    }

    friend int operator-(const const_iterator &lhs, const const_iterator &rhs)
    {
        int l = lhs.index >= lhs._buffer->_head ? lhs.index - lhs._buffer->_head : lhs._buffer->_max_size - (lhs._buffer->_head - lhs.index);
        int r = rhs.index >= rhs._buffer->_head ? rhs.index - rhs._buffer->_head : rhs._buffer->_max_size - (rhs._buffer->_head - rhs.index);
        return l - r;
    }
};
