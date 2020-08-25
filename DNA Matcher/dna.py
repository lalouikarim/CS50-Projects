import sys
import csv
def equal_lists(list1, list2):
    for i in range(len(list1)):
        if list1[i] == list2[i]:
            equal = True
        else:
            return False
    return True
if not len(sys.argv) == 3:
    print("Usage: python dna.py data.csv sequence.txt")
with open(sys.argv[1]) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=",")
    str_number = 0
    tmp = []
    tmp2 = []
    tmp3 = []
    mydict = {}
    for index, c in enumerate(csv_reader):
        for index_1 , i in enumerate(c):
            if index == 0:
                if index_1 > 0:
                    tmp.append(i)
            else:
                if index_1 ==  0:
                    f = i

                else:
                    i = int(i)
                    tmp3.append(i)
        if index > 0:

            mydict[f] = tmp3
        tmp3 = []
    sequence = open(sys.argv[2], "r")
    sequence_reader = sequence.read()
    tmp1 = []
    for s in tmp:
        counter = []
        counter_2 = []
        counter_1 = 0
        n = 0
        i = 0
        j = len(s)
        summ = 0
        k = 0
        while n < len(sequence_reader):
            if sequence_reader[i : j] == s:
                counter_1 += 1
                i = j
                j += len(s)
                k = 0
            else:
                if k == 0:
                    counter.append(counter_1)
                    counter_1 = 0
                    k = 1
                i += 1
                j += 1
            n += 1
        tmp1.append(max(counter))
    found = False
    n = 0
    for name in mydict:
        if(equal_lists(mydict[name], tmp1)):
            print(name)
            found = True
        else:
            if not found and n == len(mydict)-1:
                print("No match")
        n += 1



