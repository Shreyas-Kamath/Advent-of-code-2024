reports = []

with open("data.txt", 'r') as file:
    for line in file:
        numbers = list(map(int, line.split()))
        reports.append(numbers)

def inc_or_dec_only(level: list[int]) -> bool:      # return true if each level is strictly increasing or decreasing
    return level == sorted(level) or level == sorted(level, reverse=True)

def atleast1_atmost3(level: list[int]) -> bool:
    for i in range(0, len(level) -1):               # iterate till the second to last element
        _ = abs(level[i] - level[i+1])
        if _ > 3 or _ < 1:
            return False
    return True

def remove_one(level: list[int]) -> bool:
    for i in range(len(level)):
        temp = list(level)
        del temp[i]
        if inc_or_dec_only(temp) and atleast1_atmost3(temp): return True
    return False

count = 0

for level in reports:
    if inc_or_dec_only(level) and atleast1_atmost3(level):
        count += 1                                  # increment count if both conditions hold
    elif remove_one(level):
        count += 1

print(count)