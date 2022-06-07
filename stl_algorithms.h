namespace _algorithms
{
    template <typename _InputIterator, typename _Predicate>
    inline bool all_of(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
        return __last == std::find_if_not(__first, __last, __pred); // find_if_not searches for an element for which predicate __pred returns false
    }

    template <typename _InputIterator, typename _Predicate>
    inline bool any_of(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
        return !std::none_of(__first, __last, __pred); // none_of Returns true if pred returns false for all the elements
        // in the range [first,last) or if the range is empty, and false otherwise.
    }

    template <typename _InputIterator, typename _Predicate>
    inline bool none_of(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
        return __last == std::find_if(__first, __last, __pred); // find_if searches for an element for which predicate p returns true
    }

    template <typename _InputIterator, typename _Predicate>
    bool one_of(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
        _InputIterator i = std::find_if(__first, __last, __pred); // ищем первый элемент удовлетворяющий __pred
        if (i == __last)
            return false;
        return std::none_of(++i, __last, __pred); // проверяем, есть  ли еще хоть один такой элемент
    }

    template <typename _ForwardIterator, typename _Compare>
    inline bool is_sorted(_ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
    {
        return std::is_sorted_until(__first, __last, __comp) == __last; // is sorted until - return верхнюю границу отсортированного диапазона от __first до upper bound
    }

    template <typename _InputIterator, typename _Predicate>
    inline bool is_partitioned(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
        __first = std::find_if_not(__first, __last, __pred);// first element which return false in __pred
        // все до first true
        if (__first == __last)
            return true;
        ++__first;
        return std::none_of(__first, __last, __pred); // если все после first == false то first - разделитель
    }

    template <typename _InputIterator, typename _Type>
    _InputIterator find_not(_InputIterator __first, _InputIterator __last, const _Type &value)
    {
        while (__first != __last)
        {
            if (*__first != value)
                return __first;
            __first++;
        }
        return __last;
    }

    template <typename _InputIterator, typename _Type>
    _InputIterator find_backward(_InputIterator __first, _InputIterator __last, const _Type &value)
    {
        auto temp_last_it = __last;
        while (temp_last_it != __first)
        {
            temp_last_it--;
            if (*temp_last_it == value)
                return temp_last_it;
        }
        return __last;
    }

    template <typename _InputIterator, typename _Predicate>
    bool is_palindrom(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
        while (__first != __last)
        {
            __last--;
            if (!__pred(*__first, *__last))
                return false;
            if (__first == __last)
                return true;
            __first++;
        }
        return true;
    }
}