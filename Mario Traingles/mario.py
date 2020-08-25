import cs50
height = cs50.get_int("Height: ")
while height < 1 or height > 8:
    height = int(input("Height: "))
space_counter = height - 1
for i in range(height):
    print(" " * space_counter , end = "")
    print("#" * (i+1))
    space_counter -= 1




