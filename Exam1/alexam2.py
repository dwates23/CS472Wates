import math

def close_distance(pairs, distance_function):
    
    mindist = float('inf') 
    n = len(pairs)

    for i in range(n - 1):
        for j in range(i + 1, n):
            dist = distance_function(pairs[i], pairs[j])
            mindist = min(mindist, dist)

    return mindist

def euclidean(pair1, pair2):
    return math.sqrt((pair1[0] - pair2[0]) ** 2 + (pair1[1] - pair2[1]) ** 2)

def hamming(pair1, pair2):
    return bin(pair1[0] ^ pair2[0] | pair1[1] ^ pair2[1]).count('1')

pairs = [(1, 2), (3, 4), (5, 6), (7, 8)]
print("Closest pair distance (Euclidean):", close_distance(pairs, euclidean))
print("Closest pair distance (Hamming):", close_distance(pairs, hamming))
