import optimize

print(optimize.linprog([1, 1, 1], [[1, 2, 0], [0, 1, 0], [0, 0, 1], [1, 1, 2], [1, 0, 0]], [2, 3, 1, 10, 0]))