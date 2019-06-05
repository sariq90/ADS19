#include "sorting.h"


namespace sorting {

	//************
	// QuickSort *
	//************

	void QuickSort(vector<int> &arr, int left, int right)
	{
		if (left < right)
		{
			int pIndex = Partition(arr, left, right);
			QuickSort(arr, left, pIndex - 1);
			QuickSort(arr, pIndex + 1, right);
		}
	}

	int Partition(vector<int> &arr, int left, int right)
	{
		//Median-3 Presort (slows down quicksort)
		//if (right > left + 1)
		//{
		//	int center = left + (right - left) / 2;
		//	if (arr[right] < arr[left])
		//		swap(arr[right], arr[left]);
		//	if (arr[center] < arr[left])
		//		swap(arr[center], arr[left]);
		//	if (arr[center] < arr[right])
		//		swap(arr[center], arr[right]);
		//}

		int pivot = arr[right];
		int pIndex = left;
		for (int i = left; i < right; ++i)
		{
			if (arr[i] < pivot)
			{
				swap(arr[pIndex], arr[i]);
				++pIndex;
			}
		}
		swap(arr[pIndex], arr[right]);
		return pIndex;
	}

	//************
	// MergeSort *
	//************

	void Merge(vector<int> &a, int low, int pivot, int high)
	{
		int lSize = pivot + 1 - low;
		int rSize = high - pivot;

		// Split-copy main vector to left and right vectors
		vector<int> lArr(lSize);
		vector<int> rArr(rSize);
		for (int i = 0; i < lSize; ++i)
			lArr[i] = a[low + i];
		for (int i = 0; i < rSize; ++i)
			rArr[i] = a[pivot + 1 + i];
		
		// Merge back sorted sub-vectors
		int lIndex = 0, rIndex = 0, aIndex = low;
		while (lIndex < lSize && rIndex < rSize)
		{
			if (lArr[lIndex] <= rArr[rIndex])
			{
				a[aIndex] = lArr[lIndex];
				++lIndex;
			}
			else
			{
				a[aIndex] = rArr[rIndex];
				++rIndex;
			}
			++aIndex;
		}

		// Deal with remaining stragglers
		while (lIndex < lSize)
		{
			a[aIndex] = lArr[lIndex];
			++aIndex; ++lIndex;
		}
		while (rIndex < rSize)
		{
			a[aIndex] = rArr[rIndex];
			++aIndex; ++rIndex;
		}
	}

	void MergeSort(vector<int> &a, int low, int high)
	{
		if (low < high)
		{
			int middle = low + (high - low) / 2;
			MergeSort(a, low, middle);
			MergeSort(a, middle + 1, high);
			Merge(a, low, middle, high);
		}
	}

	//************
	// Heapsort  *
	//************

	void HeapSort(vector<int> &a, int n)
	{
		
		// Build maxheap, start with row above leaf-level
		for (int i = n / 2 - 1; i >= 0; --i)
			PercDown(a, n, i);

		// For each element: Swap max to end of vector, recurse through tree without last element
		for (int i = n - 1; i >= 0; --i)
		{
			swap(a[0], a[i]);
			PercDown(a, i, 0);
		}
	}

	void PercDown(vector<int> &a, int size, int index)
	{
		int max = index;
		int lc = 2 * index + 1;
		int rc = 2 * index + 2;

		// Pick max of parent and children
		if (lc < size && a[lc] > a[max])
			max = lc;
		if (rc < size && a[rc] > a[max])
			max = rc;

		if (max != index)
		{
			// Swap max to parent, recurse through subtree of swapped element
			swap(a[index], a[max]);
			PercDown(a, size, max);
		}
	}

	//************
	// Shellsort *
	//************

	void ShellSort(vector<int> &a, int n)
	{
		// Hibbard
		int gap = 1;
		while (gap < n)
			gap = 2 * gap + 1;
		gap /= 2;

		while (gap > 0)
		{
			for (int i = gap; i < n; ++i)
			{
				int tmp = a[i];
				int j = i;
				while (j >= gap && tmp < a[j - gap])
				{
					a[j] = a[j - gap];
					j -= gap;
				}
				a[j] = tmp;
			}
			gap /= 2;
		}
	}


	void randomizeVectorH(vector<int> &array, int n)
	{
		array.resize(n);

		for (unsigned int i = 0; i < array.size(); i++)
			array[i] = rand() % 501 + 1000;
	}

	void randomizeVector(vector<int> &array, int n) {
		array.resize(n);

		for (unsigned int i = 0; i < array.size(); i++)
			array[i] = rand() % 1000000;
	}

	void swap(int &a, int &b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}

}





