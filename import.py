import sys
import pandas
import sqlite3

if len(sys.argv) != 2:
    print("Usage: python import.py csv_filename.csv")
else:
    df = pandas.read_csv(sys.argv[1])
    conn = sqlite3.connect("students.db")
    curs = conn.cursor()
    for full_name, house, birth in zip(df["name"], df["house"], df["birth"]):
        full_name_list = full_name.split()
        if len(full_name_list) == 3:
            curs.execute("INSERT INTO students VALUES (NULL, ?, ?, ?, ?, ?)", (full_name_list[0], full_name_list[1], full_name_list[2], house, birth))
        else:
            curs.execute("INSERT INTO students VALUES (NULL, ?, ?, ?, ?, ?)", (full_name_list[0], None, full_name_list[1], house, birth))
    conn.commit()
    conn.close()

