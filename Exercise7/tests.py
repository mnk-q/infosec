from colorama import Fore, Style
from algos import monoalphabetic_substitution
from utils import monoalphabetic_key_generation

def unit_test(fun):
    # Designing Unit tests to find out the the stuff
    testcases=[
        "a",
        "hello",
        "HELLO",
        "MaNiSh",
        "qwertyuiopasdfghjklzxcvbnm",
        "JJJJJJJJjjjjjjjj",
        "MANISH"
    ]
    keys = ["i", "marss", "JUMBO", "TigerShraff",'bsdwale','abcxyz',"DONKEY"]
    keys = [monoalphabetic_key_generation() for i in range(len(testcases))]
    n=len(testcases)
    encrypted = [ fun(t, k, mode='encrypt') for t ,k in zip(testcases, keys)]
    decrypted = [ fun(t,k, mode='decrypt') for t,k in zip(encrypted,keys)]
    for i, a, b, c in zip(list(range(1, n+1)),testcases, encrypted, decrypted):
        if a==c:
            print(Fore.GREEN+str(i)+"/"+str(n)+" Testcase Passed"+Style.RESET_ALL)
        else:
            print(Fore.RED+str(i)+"/"+str(n)+" Testcase Failed"+Style.RESET_ALL+" Encrypted to : " +b+" Expected : " + a+", Got "+c)
if __name__ == "__main__":
    f = monoalphabetic_substitution
    unit_test(f)