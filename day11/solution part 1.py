

stones=[]
with open("data.txt", 'r') as file:
    stones = list(map(int, file.read().split()))

def update(stones: list[int]) -> list[int]:
    updated_stones = []
    for stone in stones:
        if stone == 0:
            updated_stones.append(1)
        elif len(str(stone)) %2 == 0:
            lhs, rhs = str(stone)[:len(str(stone))//2], str(stone)[len(str(stone))//2:]
            updated_stones.append(int(lhs))
            updated_stones.append(int(rhs))
        else:
            updated_stones.append(stone * 2024)
    return updated_stones

for i in range(25):
    stones = update(stones)

print(len(stones))