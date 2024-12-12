from collections import Counter, defaultdict

with open ("data.txt", 'r') as file:
    data = list(map(int, file.read().split()))

stones = defaultdict(int, Counter(data))

iterations = 75

def one_blink():
    for stone, count in list(stones.items()):    #list because the dictionary is modified during the loop
        if count == 0: continue                  #runtime is 80-90 ms
        if stone == 0:
            stones[1] += count
            stones[0] -= count
        
        elif len(str(stone)) %2 == 0:
            stone_str = str(stone)

            mid = len(stone_str) // 2

            lhs = int(stone_str[:mid])
            rhs = int(stone_str[mid:])

            stones[lhs] += count
            stones[rhs] += count

            stones[stone] -= count
        
        else:
            stones[stone * 2024] += count
            stones[stone] -= count

for i in range(iterations):
    one_blink()

print(sum(stones.values()))