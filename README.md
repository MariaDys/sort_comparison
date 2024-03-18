# Sort comparison

**Постановка задачи**
В программе реализуется два метода сортировки массива чисел и проводится их экспериментальное сравнение.
Для сравнения используются методы быстрой и медленной сортировки, а именно, пирамидальная сортировка и сортировка методом «пузырька». Элементами массива являются 64-разрядные целые числа. В результате каждой из сортировок числа должны быть упорядочены по невозрастанию.


**Структура программы и спецификация функций**
Функция void _BubbleSort_(long long int *a, int n) - сортировка методом "пузырька". Параметры функции: a - указатель на сортируемый массив, n - количество элементов в массиве.
Функция void _HeapSort_ (long long int *a, int n) - пирамидальная сортировка. Параметры функции: a - указатель на сортируемый массив, n - количество элементов в массиве.
Функция static void _sift_(long long int *a, int n, int i) - просеивание элементов через кучу. Параметры функции: a - указатель на сортируемый массив, n - количество элементов в массиве, i - корневой узел поддерева, которое преобразовывается в двоичную кучу.
Функция void _swap_ (long long int *a, long long int *b) - обмен значениями. Параметры функции: a - указатель на первую переменную, b - указатель на вторую переменную. 
Функции-компараторы _cmp1_ и _cmp2_ для встроенной функции qsort. Прототип функции: int cmp1(const void *a, const void *b). Параметры функции: a, b - указатели на элементы массива.
Функция void _gen_ (int n, int MassivType) - генерация массива тремя способами, в зависимости от введенного параметра. Параметры функции: n - длина массива, MassivType - целое число, задающее порядок построения элементов в массиве.
В качестве счетчиков числа сравнений и перемещений для каждой из сортировок использовались глобальные переменные: long long int _comp_ и long long int _mov_. Для средних значений этих показателей использовались глобальные переменные: long double _compB_, _movB_, _compP_, _movP_.
