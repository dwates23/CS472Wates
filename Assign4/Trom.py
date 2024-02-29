import sys
#SURPRISE Python Time
def trom_tile(board, forbidden, size, row_start, col_start):
    print("Tromino tiling called with size: {}, starting at row: {}, and column: {}".format(size, row_start, col_start))
    if size == 2:
        for i in range(row_start, row_start + 2):
            for j in range(col_start, col_start + 2):
                if (i, j) != forbidden:
                    board[i][j] = 1
        return

    half = size // 2
    quad_is_missing = quad_find(forbidden, row_start, col_start, half)
    print("Missing quadrant determined to be: {}".format(quad_is_missing))

    for i in range(row_start, row_start + size):
        for j in range(col_start, col_start + size):
            if (i, j) != forbidden:
                board[i][j] = 1

    trom_tile(board, forbidden, half, row_start, col_start)  # Recursion starts here
    trom_tile(board, forbidden, half, row_start, col_start + half)
    trom_tile(board, forbidden, half, row_start + half, col_start)
    trom_tile(board, forbidden, half, row_start + half, col_start + half)

    if quad_is_missing[0] < row_start + half:
        if quad_is_missing[1] < col_start + half:
            board[row_start + half][col_start + half - 1] = 0
            board[row_start + half][col_start + half] = 0
        else:
            board[row_start + half][col_start + half] = 0
            board[row_start + half][col_start + half - 1] = 0
    else:
        if quad_is_missing[1] < col_start + half:
            board[row_start + half][col_start + half - 1] = 0
            board[row_start + half - 1][col_start + half - 1] = 0
        else:
            board[row_start + half][col_start + half] = 0
            board[row_start + half - 1][col_start + half] = 0

def quad_find(forbidden, row_start, col_start, size):
    forbidden_row, forbidden_col = forbidden

    if forbidden_row < row_start + size:
        if forbidden_col < col_start + size:
            return row_start + size, col_start + size - 1
        else:
            return row_start + size, col_start + size
    else:
        if forbidden_col < col_start + size:
            return row_start + size - 1, col_start + size
        else:
            return row_start + size - 1, col_start + size - 1

def main():
    print("Main function called") # Line used for debugging
    n = 4
    forbidden = (1, 2) 
    board = [[0] * n for _ in range(n)]

    trom_tile(board, forbidden, n, 0, 0)
    print("Tromino Board:")
    for row in board:
        print(' '.join(map(str, row)))

if __name__ == "__main__":
    sys.setrecursionlimit(10000)  # Recursion limit
    main()
