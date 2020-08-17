import sqlite3
import sys

if len(sys.argv) != 2:
    print("Usage: python roster.py House_Name")
else:
    conn = sqlite3.connect("students.db")
    curs = conn.cursor()
    curs.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", (sys.argv[1],))
    result = curs.fetchall()
    conn.close()
    students_list = []
    try:
        for person in result:
            if person[1] == None:
                student_info = person[0] + " " + person [2] + ", born " + str(person[3])
            else:
                student_info = person[0] + " "+ person[1] + " " + person [2] + ", born " + str(person[3])
            students_list.append(student_info)
        for i in students_list:
            print(i)
    except:
        pass