/*-------------------------------------*/


/*-------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define size_threshold 50


/* Swap two given numbers */

void swap(int *a, int *b){

    int tmp = *a;
    *a = *b;
    *b = tmp;

}

/* Sort a list of elements by iteratively inserting the next element
    in a progressively growing sorted array */

void insertion_sort(int list[], int input_size){
    int i, j, tmp;
     for(i = 1; i < input_size; i++){
        tmp = list[i];
        j = i;
        while((j > 0) && (tmp < list[j - 1])){
            list[j] = list[j-1];
            j--;
        }
        list[j] = tmp;
    }
}


int partition(int list[], int left, int right){
    int pivot, i;

    pivot = left;

    for(i = left; i < right; i++){
        if(list[i] < list[right]){
            /* Move the pivot element */
            swap(&list[i], &list[pivot]);
            pivot++;
        }
    }
    swap(&list[pivot], &list[right]);

    return pivot;

}

void quick_sort(int list[], int left, int right){
    int pivot;

    if(right - left > 0){
        /* Divide-and-conquer startegy */

        /* Select a pivot element, and then divide the array into two subarrays */
        pivot = partition(list, left, right);

        /* Sort each subarray recursively */
        quick_sort(list, left, pivot - 1);
        quick_sort(list, pivot + 1, right);

    }
}

void medianof3(int list[], int left, int mid, int right){

    /* Sort the numbers that middle number be in the list[mid] */
    if(list[left] > list[mid]) swap(&list[left], &list[mid]);
    if(list[mid] > list[right]) swap(&list[mid], &list[right]);
    if(list[left] > list[mid]) swap(&list[left], &list[mid]);
}

void m_sort(int list[], int left, int right){
    int i, j, pivot;

    int mid = left + (right-left)/2;

    /* Sort the three elements */
    medianof3(list, left, mid, right);

    /* Sort if the size of the list is over 3 */
    if(right - left + 1 > 3){

        /* Select the medianof3 to the pivot */
        pivot = list[mid];

        /* Same as the Quick Sort */
        swap(&list[mid], &list[right - 1]);
        i = left;
        j = right - 1;
        while(1){
            while(list[++i] < pivot && i < right);
            while(list[--j] > pivot && left < j);
            if(i >= j) break;
            swap(&list[i], &list[j]);
        }
        swap(&list[i], &list[right-1]);
        /* Divide-and-conquer strategy*/
        m_sort(list, left, i -1);
        m_sort(list, i+1, right);
    }


}


void merge(int list[], int left, int middle, int right, int input_size){
    int merging[input_size];
    
    /* Copy the original list from the left */
    memcpy(merging + left, list + left, sizeof(int) * (right - left + 1));

    int i, j, cur;
    i = left;
    j = middle + 1;
    cur = left;

    /* Compare the two separate lists and put the smaller one into the original list */
    while((i <= middle) && (j <= right)){
        if(merging[i] < merging[j]) list[cur++] = merging[i++];

        else list[cur++] = merging[j++];
    }

    /* Put the remaining elements into the original list */
    while(i <= middle) list[cur++] = merging[i++];
    while(j <= right) list[cur++] = merging[j++];

}

void merge_sort(int list[], int left, int right, int input_size){

    int middle;

    if(right - left > 0){
        middle = (left + right)/2;
        /* Divide-and-conquer strategy*/

        /* Divide the array into two subarrays each with ~n/2 items.
            Conquer each subarray by sorting it recursively */
        merge_sort(list, left, middle, input_size);
        merge_sort(list, middle + 1, right, input_size);
        
        /*Combine the solutions to the subarrays by merging them into a single sorted array. */
        merge(list, left, middle, right, input_size);
    }
}

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("usage: %s input_filename algorithm_index.\n", argv[0]);
        return 0;
    }


    char input_filename[200];
    strcpy(input_filename, argv[1]);

    int algorithm_index = atoi(argv[2]);
    int input_size = 0;
    int i, j, tmp;
    int left, right;

    FILE *infile;
    infile = fopen(input_filename, "r");
    if(infile == NULL){
        printf("Error: input file cannot be opened.\n");
        return 0;
    }

    /*------- Get data from the input file -------*/

    fscanf(infile, "%d", &input_size);
    int list[input_size];

    for(i = 0; i < input_size; i++){
        fscanf(infile, "%d ", &list[i]);
    }

    fclose (infile);

    clock_t start_time = clock();
    
    switch(algorithm_index){
        case 1:
        /*------- Insertion Sort  -------*/
           
            insertion_sort(list, input_size);

            break;

          
        case 2:
        /*------- Quick Sort -------*/
            left = 0;
            right = input_size - 1;
            quick_sort(list, left, right);

            break;

        case 3:
        /*------- Merge Sort-------*/
            left = 0;
            right = input_size - 1;
            merge_sort(list, left, right, input_size);

            break;

        case 4:
        /*------- User Defined Sort-------*/
            left = 0;
            right = input_size - 1;
            m_sort(list, left, right);
            break;

        default:
            printf("You should choose 1 or 2 or 3 or 4 algorithm index.\n");
            return 0;
    }

    clock_t end_time = clock();

    
    /*------- Context of output file (result_inputfilename) -------*/
    FILE *resultfile;
    char temp_index[200];
    char result_filename[200] = "result_";
    sprintf(temp_index, "%d", algorithm_index);
    strcat(temp_index, "_");
    strcat(temp_index, input_filename);
    strcat(result_filename, temp_index);

    resultfile = fopen(result_filename, "w");
    
    fprintf(resultfile, "%s\n", input_filename); //input file name
    fprintf(resultfile, "%d\n", algorithm_index); // algorithm index
    fprintf(resultfile, "%d\n", input_size); // input size (the number of elements in the original list)
    fprintf(resultfile, "%.6f\n", (double)(end_time - start_time)/CLOCKS_PER_SEC); // running time in seconds
    for(i = 0; i < input_size; i++){
       fprintf(resultfile, "%d ", list[i]); // the sorted list
    }
    fprintf(resultfile, "\n");
    fclose(resultfile);

    return 0;

}
