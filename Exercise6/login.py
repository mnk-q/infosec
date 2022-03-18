# To harness the power of python and avoid implementing the md5 from scrath,
# We will go with python. This App implements a Login and Registration service made on console, and it keeps all the
# data in a csv format.
# we could go with sqlite but we want to see md5 in action in a browsable way

import csv
from hashlib import md5
import sys
import time
from getpass import getpass

def hashit(msg:str):
    return md5(msg.encode()).hexdigest()

class Person:
    def __init__(self, uname, pwd, email):
        self.uname = uname
        self.pwd = pwd
        self.email = email
        
    
    def save(self):
        with open("database.csv",'a', newline='') as f:
            writer = csv.writer(f)
            writer.writerow([self.uname, self.pwd, self.email])


def progressBar(iterable, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    
    total = len(iterable)
    
    def printProgressBar (iteration):
        percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
        filledLength = int(length * iteration // total)
        bar = fill * filledLength + '-' * (length - filledLength)
        print(f'\r{prefix} |{bar}| {percent}% {suffix}', end = printEnd)
   
    printProgressBar(0)
    
    for i, item in enumerate(iterable):
        yield item
        printProgressBar(i + 1)
    
    print()

def hack():
    print(" ---- Dark Side ! -----")
    print("Attempting to Hack the system")
    items = list(range(0, 10))

    
    for item in progressBar(items, prefix = 'Hacking:', suffix = 'Done', length = 50):
        
        time.sleep(0.1)
        
    print("\nSystem Compromised")
    
    while True:
        print("-----------------------")
        print("1. Breach Entire Database")
        print("2. Obtain user's data")
        print("3. Back to Main Menu")
        
        ip = int(input("Option >> "))
        
        if(ip == 1):
            print("Dumping Entire Database")
            print()
            time.sleep(0.5)
            with open("database.csv", 'r') as f:
                reader = csv.reader(f)
                for row in reader:
                    print(' | '.join(row))
            
        elif ip == 2:
            u = input("Enter the user's name >> ")
            print("Printing All records containing "+u+" in them")
            print()
            time.sleep(0.5)
            with open("database.csv", 'r') as f:
                reader = csv.reader(f)
                for row in reader:
                    if row and u in row[0] or u in row[2]:
                        print(f"User : {row[0]}, Password :{row[1]}, Email :{row[2]}")
        else:
            return

def verified_user(uname, pwd):
    pwd = hashit(pwd)
    count = 0
    data = []
    with open('database.csv', 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            
            if row and row[0] == uname and row[1]==pwd:
                count += 1
                data = [row[0], row[2]]
    return count , data
    


def run_login():
    print("------------ Log in -----------------")
    uname = input("Enter the username >> ")
    pwd = getpass("Enter the Password >> ")
    status, data = verified_user(uname, pwd)
    if status==1:
        print("You are logged in! ")
        print("welcome "+data[0]+" Your Email is "+data[1])
        
        # Do Something after log in
        
        print("Logging out! press any key to continue")
        input()
    else:
        print("Wrong Username / Password Combo! Returning Back to Main Menu!")


def run_register():
    print("------------- Register ------------------")
    uname = input("Enter your preferred username >> ")
    email = input("Enter your Email >> ")
    pwd = hashit(getpass("Enter your password >> "))
    user = Person(uname, pwd, email)
    c = input("Are you sure you want to register [y/n] >> ")
    if c.lower() == 'y':
        user.save()
        print("Registration Successfull ! Please Login")
    else:
        print("Going back to Main Menu")
        

# Main Event Loop
while True:
    print(" ----------- Welcome ---------------")
    print("Login ")
    print("Register")
    print("Hack")
    print("Exit")
    
    ip = int(input( ">> " ))
    if (ip == 1):
        run_login()
    elif ip == 2:
        run_register()
    elif ip == 3:
        hack()
    else:
        sys.exit(0)
    
    
            