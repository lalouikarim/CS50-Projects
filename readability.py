import math
text = input("Text: ")
letters_number = 0
words_number = 0
sentences_number = 0
for c in text:
    if ord(c) >= 65 and ord(c) <= 90 or ord(c) >= 97 and ord(c) <= 122:
        letters_number += 1
    if ord(c) == 32:
        words_number += 1
    if ord(c) == 46 or ord(c) == 33 or ord(c) == 63:
        sentences_number += 1
words_number += 1
L = 100 * letters_number / words_number
S = 100 * sentences_number / words_number
Grade = 0.0588 * L - 0.296 * S - 15.8
tmp = math.floor(Grade)
tmp1 = math.ceil(Grade)
difference = Grade - tmp
difference_1 = tmp1 - Grade
if(difference < difference_1):
    Grade = tmp
else:
    Grade = tmp1
if Grade >= 16:
    print("Grade 16+")
elif Grade < 1:
    print("Before Grade 1")
else :
    print(f"Grade {Grade}")