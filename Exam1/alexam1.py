#Binary insertion sort has better time efficiency than normal insertion sort due to binary search being used to
#find the correct insertion point for each element. The normal insertion sort, however, uses linear search when finding
#an insertion point, resulting in O(n^2) time complexity in the worst-case scenario. Meanwhile, binary insertion sort reduces
#search time to O(log n) for each insertion, which results in an overall time complexity of O(n log n).

def insert_sort(array):
    for i in range(1, len(array)):
        j = i
        while j > 0 and array[j-1] > array[j]:
            array[j], array[j-1] = array[j-1], array[j]
            j -= 1
    return array

def bin_insert_sort(array):
    
    for i in range(1, len(array)):
        key = array[i]
        left = 0
        right = i - 1
        while left <= right:
            mid = (left + right) // 2
            if array[mid] > key:
                right = mid - 1
            else:
                left = mid + 1
        array.insert(left, key)
        del array[i + 1]
    return array

arr = [5, 3, 8, 2, 7, 4]
print("Original array:", arr)
print("Sorted array (insertion sort):", insert_sort(arr[:]))
print("Sorted array (binary insertion sort):", bin_insert_sort(arr[:]))
