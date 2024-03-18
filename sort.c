#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// счетчики для средних значений показателей
long double compB, movB, compP, movP;
// счетчики числа сравнений и перемещений
long long int comp = 0; // сравнения
long long int mov = 0; // перемещения


// Функция обмена значениями двух переменных
void swap (long long int *a, long long int *b){
    long long int x = *a;
    *a = *b;
    *b = x;
    mov += 1; // увеиличиваем счетчик перемещений
}

/* Метод медленной сортировки (метод «пузырька») */
void bubble_sort(long long int a[], int n){
    comp = 0; mov = 0;
    // проходим по всем элементам
    for (int i = 0; i < n - 1; i++){
        // проходим по всем элементам после i-ого
        for (int j = (n - 1); j > i; j--){
            comp+=1;
            // если предыдущий элемент меньше, то меняем их местами
            if (a[j - 1] < a[j]){
                swap(&a[j-1], &a[j]);
            }
        }
    }
    // добавляем к общим счетчикам compB и movB значения показателей comp и  mov
    compB += comp;
    movB += mov;
    printf("BubbleSort: количество перестановок - %lld,количество сравнений - %lld\n", mov, comp);
}

/* Метод быстрой сортировки (пирамидальная сортировка) */
static void sift(long long int *a, int n, int i) {
    int root = i; // в качестве корня - наименьший элемент
    int l = 2*i + 1; // левый потомок
    int r = 2*i + 2; // правый потомок
    
    // если левый потомок меньше корня, то присваиваем корню его значение
    if (l < n){
        comp+=1;
        if (a[l] < a[root]){
        root = l;
        comp += 1;
        }
    }
    
    // если правый потомок меньше наименьшего элемента, то присваиваем корню его значение
    if (r < n){
        if (a[r] < a[root]){
        root = r;
        comp += 1;
        }
    }
    
    // если наименьший элемент не корень, то меняем значения этого элемента и корня
    if (root != i){
        comp += 1;
        swap(&a[i], &a[root]);
        sift(a, n, root); // так же преобразуем поддерево в кучу
    }
    else comp+=1;
}

void heap_sort(long long int *a, int n){
    comp = 0; mov = 0;
    if (n > 1){
        int i;
        // Формирование кучи
        for (i = n/2 - 1; i >= 0; i --)
            sift(a, n, i);
        // Просвеиваем элементы, извлекая элементы из кучи
        for (i = n-1; i >= 0; i--) {
            // корень перемещаем в конец, тем самым уменьшая кучу для просеивания
            swap(&a[0], &a[i]);
            // просеивание на уменьшенной куче
            sift(a, i, 0);
        }
    }
    else if (n==1){
        comp = 0;
        mov = 0;
    }
    // добавляем к общим счетчикам compP и movP значения показателей comp и  mov
    compP += comp;
    movP += mov;
    printf("HeapSort: количество перестановок - %lld,количество сравнений - %lld\n", mov, comp);
}
// функция-компаратор для qsort (неубывание)
int cmp1(const void *a, const void *b){
    if (*(long long int *)a - *(long long int *)b < 0)
        return -1;
    if (*(long long int *)a - *(long long int *)b > 0)
        return 1;
    return 0;
}
// функция-компаратор для qsort (невозрастание)
int cmp2(const void *a, const void *b){
    if (*(long long int *)b - *(long long int *)a < 0)
        return -1;
    if (*(long long int *)b - *(long long int *)a > 0)
        return 1;
    return 0;
}

void gen(int n, int MassivType){
    long long int *massiv = malloc(sizeof(long long int) * n);
    for (int k = 0; k < n; k++){
        massiv[k] = rand()*rand()*rand()*rand()*rand();
    }
    long long int *massiv_1 = malloc(sizeof(long long int) * n);
    long long int *massiv_2 = malloc(sizeof(long long int) * n);
    long long int *massiv_3 = malloc(sizeof(long long int) * n);
    long long int *massiv_4 = malloc(sizeof(long long int) * n);
    memcpy(massiv_3, massiv, n*sizeof(long long int));
    memcpy(massiv_4, massiv, n*sizeof(long long int));
    
    if (MassivType == 1){
        printf("Элементы массива упорядочены по неубыванию, длина массива равна %d:\n", n);
        qsort(massiv, n, sizeof(long long int), cmp1);
        memcpy(massiv_1, massiv, n*sizeof(long long int));
        bubble_sort(massiv, n);
        heap_sort(massiv_1, n);
    }
    else if (MassivType == 2){
        printf("Элементы массива упорядочены по невозрастанию, длина массива равна %d:\n", n);
        qsort(massiv, n, sizeof(long long int), cmp2);
        memcpy(massiv_2, massiv, n*sizeof(long long int));
        bubble_sort(massiv, n);
        heap_sort(massiv_2, n);
    }
    else if (MassivType == 3 || MassivType == 4){
        printf("Элементы массива не упорядочены, длина массива равна %d:\n", n);
        bubble_sort(massiv_3, n);
        heap_sort(massiv_4, n);
    }
    else {
        printf("Длина массива равна %d\n", n);
        printf("Средние значения показателей сравнений:\nBubbleSort:%Lf\nHeapSort:%Lf\n", compB/4, compP/4);
        printf("Средние значения показателей перемещений:\nBubbleSort:%Lf\nHeapSort:%Lf\n", movB/4, movP/4);
    }
    printf("\n");
}

int main(int argc, const char *argv[]) {
    int n;
    srand(time(NULL));
    if (argc > 1 && (!strcmp(argv[1], "-h"))){
        printf("\nСправочная информация:\nДанная программа сортирует массивы длины n двумя методами: пирамидальной сортировкой и методом «пузырька».\nМассивы генерируются тремя разными способами:\n1) первый массив с упорядоченными по неубыванию элементами\n2) второй массив с упорядоченными по невозрастанию элементами\n3,4) третий и четвертый массивы со случайной расстановкой элементов\nПрограмма выводит количество сравнений и перемещений элементов в массивах при каждой из двух сортировок, а также среднее значение этих показателей.\n\n-h - вывести справочную информацию\nn - указать количество элементов в массиве\n\n");
        return 0;
    }
    if (argc == 1) n = 1;
    else {
        n = atoi(argv[1]);
        if (n < 1) printf("В качестве длины массива необходимо ввести натуральное число!\n");
        //  иначе - генерация всех видов массивов и вывод показаний счетчиков и их средних значений
        else{
            for (int r = 1; r < 6; r++){
                gen(n, r);
            }
        }
    }
    return 0;
}
