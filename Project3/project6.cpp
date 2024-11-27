//Project 6
//Author: Sujata Sahu

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
                                        // we want to retain the ordering of arr for shell sort 
    for(int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
	int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last
	
    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i) 
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                            // the if condition where the comparison happens each time
                if(numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;


        while ((j >= 0) && (arr[j] > temp))
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arr; // return the not necessarily sorted array = approximately sorted array
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
	return arr;
}

//Return Inversion Result
int inversionCalc(int n, int *bubbleSorted){
    int *lessCount = new int[n]; //stores the count of number less than current number in array
    for (int i = 0; i < n; i++)
    {
        lessCount[i] = 0; // initializing with 0 for every element
    }
    
    int inversion = 0;
    for (int i = 0; i < n; i++) //loop to pick an element
    {
        for (int j = i+1; j < n; j++) // loop to compare the picked element with next elements in array
        {
            if (bubbleSorted[j] < bubbleSorted[i]) //checking if next element is less
            {
                lessCount[i] = lessCount[i] + 1; // increase the count with one
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        inversion = inversion + lessCount[i];
    }
    return inversion;
}

//Returns Chebyshev Distance
int ChebyshevDist(int n, int *bubbleSorted, int *fullySorted){
    int distance = 0; //initialize distance
    for (int i = 0; i < n; i++) // loop to pick an element
    {
        for (int j = 0; j < n; j++) // loop to find the position of picked element in fully sorted array
        {
            if(fullySorted[i] == bubbleSorted[j]){
                int temp = abs(j-i); // calculate the distance by doing minus of two positions
                if(temp > distance) // check if current element's distance if greater than previous one
                    distance = temp; //assign temp to distance as it is maximum for now
            }
        }
    }
    return distance;
}

//main function
int main()
{   
    int *A; // stores unique unsorted elements
    int *fullySorted; //stores fully sorted elements
    int *bubble; //stores elements sorted with bubble sort with D comparisons
    int *shell; //stores elements sorted with shell sort with D comparisons
	int n; //Number of elements
    int addedNumbers = 0; //counter to add elements to array A
	cin >> n; // read the number of elements
	cout << "Number of elements: " << n << endl;

	int s, l, u, D;
	
	cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

	// generate n random elements with the seed s, within the lower and upper range
    srand(s);
    // store the randomly generated UNIQUE set of elements in an array 'A'
    A = new int[n];
    // you may use the unordered set to help generate unique elements
    unordered_set<int> unA;
    while (unA.size() < n)
    {
        int currand = rand(); //randome number generation
        currand = currand % (u-l+1) + l; // range
        unA.insert(currand); // insertion        
    }
    for (std::unordered_set<int>::iterator itr = unA.begin(); itr!=unA.end(); ++itr) // loop to add numbers to array
    {
        A[addedNumbers] = *itr; //assign current number to position in a array
        addedNumbers++; //increment the counter of array
    }
    
	cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
	// display the array A
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " "; //prints element
        if(i == (n-1)) // check if last element
            cout << endl; //end the current line
    }
    cout << endl;

    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 

    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
	// display the completely sorted array 

    fullySorted = bubbleSort(A,n, n*n); //gets the fully sorted array
    for (int i = 0; i < n; i++) // loop to display elements
    {
        cout << fullySorted[i] << " ";//prints element
        if(i == (n-1)) // check if last element
            cout << endl; //end the current line
    }
    cout << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;
    bubble = bubbleSort(A, n, D); //gets the sorted array with D comparisons with bubble sort
    // display bubResult
    for (int i = 0; i < n; i++)// loop to display elements
    {
        cout << bubble[i] << " "; //prints element
        if(i == (n-1)) // check if last element
            cout << endl; //end the current line
    }
    cout << endl;
    // find both the quality metrics for bubResult
    cout << "Number of inversions in bubResult: " << inversionCalc(n, bubble) << endl; //prints the inversion metric for bubble sort
    cout << "Chebyshev distance in bubResult: " << ChebyshevDist(n, bubble, fullySorted) << endl; //prints the chebyShev distance metric for bubble sort
    cout << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    shell = shellSort(A, n, D); //gets the sorted array with D comparisons with shell sort
    // display bubResult
    for (int i = 0; i < n; i++) // loop to display elements
    {
        cout << shell[i] << " "; //prints element
        if(i == (n-1)) // check if last element
            cout << endl;//end the current line
    }
    cout << endl;
    // display shellResult
    cout << "Number of inversions in shellResult: " << inversionCalc(n, shell) << endl; //prints the inversion metric for bubble sort
    cout << "Chebyshev distance in shellResult: " << ChebyshevDist(n, shell, fullySorted) << endl; //prints the chebyShev distance metric for shell sort
    cout << endl;
    // find both the quality metrics for shellResult

    return 0;
}
