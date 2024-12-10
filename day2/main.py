# reports = [[7, 6, 4, 2, 1],
# [1, 2, 7, 8, 9],
# [9, 7, 6, 2, 1],
# [1, 3, 2, 4, 5],
# [8, 6, 4, 4, 1],
# [1, 3, 6, 7, 9]
# ]
reports = []
with open("data.txt", 'r') as file:
    for line in file:
        numbers = list(map(int, line.split()))
        reports.append(numbers)

def inc_or_dec_only(level: list[int]) -> bool:
    return level == sorted(level) or level == sorted(level, reverse=True)

def atleast1_atmost3(level: list[int]) -> bool:
    for i in range(0, len(level) -1):
        _ = abs(level[i] - level[i+1])
        if _ > 3 or _ < 1:
            return False
    return True

count = 0

for level in reports:
    if inc_or_dec_only(level) and atleast1_atmost3(level):
        count += 1

print(count)