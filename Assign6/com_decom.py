import heapq
import os
import sys
import json

class HuffmanNode:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq

def build_huffman_tree(text):
    frequency = {}
    for char in text:
        if char in frequency:
            frequency[char] += 1
        else:
            frequency[char] = 1

    priority_queue = []
    for char, freq in frequency.items():
        heapq.heappush(priority_queue, HuffmanNode(char, freq))

    while len(priority_queue) > 1:
        left_node = heapq.heappop(priority_queue)
        right_node = heapq.heappop(priority_queue)
        merged_node = HuffmanNode(None, left_node.freq + right_node.freq)
        merged_node.left = left_node
        merged_node.right = right_node
        heapq.heappush(priority_queue, merged_node)

    return priority_queue[0]

def build_encoding_table(root):
    encoding_table = {}
    def build_code(node, code):
        if node is None:
            return
        if node.char is not None:
            encoding_table[node.char] = code
            return
        build_code(node.left, code + '0')
        build_code(node.right, code + '1')
    build_code(root, '')
    return encoding_table

def huffman_encode(text):
    root = build_huffman_tree(text)
    encoding_table = build_encoding_table(root)
    encoded_text = ''.join(encoding_table[char] for char in text)
    return encoded_text, root

def huffman_decode(encoded_text, root):
    decoded_text = ''
    current_node = root
    for bit in encoded_text:
        if bit == '0':
            current_node = current_node.left
        else:
            current_node = current_node.right
        if current_node.char is not None:
            decoded_text += current_node.char
            current_node = root
    return decoded_text

def serialize_tree(node):
    if node is None:
        return None
    if node.char is not None:
        return {"char": node.char, "freq": node.freq}
    return {"freq": node.freq, "left": serialize_tree(node.left), "right": serialize_tree(node.right)}

def deserialize_tree(data):
    if data is None:
        return None
    if "char" in data:
        return HuffmanNode(data["char"], data["freq"])
    left_child, right_child = deserialize_tree(data["left"]), deserialize_tree(data["right"])
    return HuffmanNode(None, data["freq"], left_child, right_child)





def compress_file(input_file, output_file):
    with open(input_file, 'r') as file:
        text = file.read()
    encoded_text, root = huffman_encode(text)
    # Convert encoded text to bytes
    encoded_bytes = int(encoded_text, 2).to_bytes((len(encoded_text) + 7) // 8, byteorder='big')
    with open(output_file, 'wb') as file:
        # Write Huffman tree to file
        tree_data = json.dumps(serialize_tree(root)).encode('utf-8')
        file.write(tree_data)
        # Write separator
        file.write(b'\n')
        # Write encoded data
        file.write(encoded_bytes)


def decompress_file(input_file, output_file):
    with open(input_file, 'rb') as file:
        # Read Huffman tree from file
        root_data = json.loads(file.readline().decode('utf-8-sig'))
        root = deserialize_tree(root_data)
        # Skip separator
        file.readline()
        # Read encoded data from file
        encoded_bytes = file.read()
    # Convert bytes to binary string
    encoded_text = bin(int.from_bytes(encoded_bytes, byteorder='big'))[2:]
    decoded_text = huffman_decode(encoded_text, root)
    with open(output_file, 'w') as file:
        file.write(decoded_text)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python com_decom.py input_file")
        sys.exit(1)

    input_file = sys.argv[1]
    compressed_file = 'compressed.bin'
    decompressed_file = 'decompressed.txt'

    compress_file(input_file, compressed_file)
    decompress_file(compressed_file, decompressed_file)
