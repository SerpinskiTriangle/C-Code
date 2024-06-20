#include <stdlib.h>
#include <stdio.h>

void quicksort(int arrlen, int *arr);
void swap(int *ptr1, int *ptr2);    

int main(int argc, char *argv[]){
    int array[argc-1];
    for (int i = 1; i < argc; i++){
        array[i-1] = atoi(argv[i]);
    }
    quicksort(argc, array);
    for (int i = 0; i < argc - 1; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}

void swap(int *ptr1, int *ptr2){
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void quicksort(int arrlen, int *arr){
    switch (arrlen){
        case 0:
            return;
        case 1:
            return;
        case 2:
            if(arr[0]>arr[1]){
                swap(arr, arr+1);
            }
            return;
        default:
            int pivot = *arr;
            int* marcherLeft = arr;
            int* marcherRight = arr+arrlen-1;
            __uint8_t lockStates = (*marcherLeft >=  pivot) + ((*marcherRight < pivot) << 1);

            while (marcherLeft != marcherRight){//pear four mince or something
                if (lockStates & 1 && lockStates & 2){
                    swap (marcherLeft, marcherRight);
                    lockStates = 0;
                    continue;
                }
                marcherLeft += !(lockStates & 1);
                if (marcherLeft == marcherRight){
                    break;
                }
                marcherRight -= !(lockStates & 2);
                lockStates = (*marcherLeft >= pivot) + ((*marcherRight < pivot) << 1);
            }
            quicksort(marcherLeft-arr+(*marcherLeft <= pivot),arr);
            quicksort(arr+arrlen-marcherLeft - (*marcherLeft <= pivot), marcherLeft+(*marcherLeft <= pivot));
    }
}