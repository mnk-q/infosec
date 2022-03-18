from utils import long_as_msg
def odd_even_extraction_merging(msg, k,mode="encrypt"):
    if mode == "encrypt":
        a=[[],[]]
        c=0
        for i in range(len(msg)):
            a[c].append(msg[i])
            c=1-c
        enc_msg = ''.join(a[0])+''.join(a[1])
        return enc_msg
    else :
        n = (len(msg)+1)//2
        a = [ list(msg[:n]), list(msg[n:])]
        if len(msg)%2:
            a[1].append('')
        dec=''
        for i in range(len(a[0])):
            dec += (a[0][i]+a[1][i])
        return dec

def vigenere_cipher(msg:str, key:str, mode='encrypt'):
    key = long_as_msg(key, len(msg))
    if mode == 'encrypt':
        cipher = []
        for m ,k in zip(msg, key):
            if m.isupper():
                k = k.upper()
                x = (ord(m)-65 + ord(k)-65)%26 + 65 
            
            else:
                k = k.lower()
                x = (ord(m)-97 + ord(k)-97)%26 + 97 
            cipher.append(chr(x))
        return ''.join(cipher)
    else:
        key = long_as_msg(key, len(msg))
        org = []
        for m,k in zip(msg, key):
            if m.isupper():
                k=k.upper()
                x = (ord(m)-65 - (ord(k)-65))%26 + 65
                
            else:
                k = k.lower()
                x = (ord(m)-97 - (ord(k)-97))%26 + 97
                
            org.append(chr(x))
        return ''.join(org)

def encryptRailFence(text, key):

    rail = [['\n' for i in range(len(text))]
                  for j in range(key)]
    dir_down = False
    row, col = 0, 0
     
    for i in range(len(text)):

        if (row == 0) or (row == key - 1):
            dir_down = not dir_down

        rail[row][col] = text[i]
        col += 1

        if dir_down:
            row += 1
        else:
            row -= 1

    result = []
    for i in range(key):
        for j in range(len(text)):
            if rail[i][j] != '\n':
                result.append(rail[i][j])
    return("" . join(result))

def decryptRailFence(cipher, key):

    rail = [['\n' for i in range(len(cipher))]
                  for j in range(key)]
     
    dir_down = None
    row, col = 0, 0

    for i in range(len(cipher)):
        if row == 0:
            dir_down = True
        if row == key - 1:
            dir_down = False

        rail[row][col] = '*'
        col += 1

        if dir_down:
            row += 1
        else:
            row -= 1

    index = 0
    for i in range(key):
        for j in range(len(cipher)):
            if ((rail[i][j] == '*') and
               (index < len(cipher))):
                rail[i][j] = cipher[index]
                index += 1
    result = []
    row, col = 0, 0
    for i in range(len(cipher)):
        if row == 0:
            dir_down = True
        if row == key-1:
            dir_down = False

        if (rail[row][col] != '*'):
            result.append(rail[row][col])
            col += 1
        if dir_down:
            row += 1
        else:
            row -= 1
    return("".join(result))


def railFence(msg, key, mode='encrypt'):
    if mode == "decrypt":
        return decryptRailFence(msg, key)
    return encryptRailFence(msg, key)


def ceaser_cipher(msg, key, mode = "encrypt"):
    msg = list(msg)
    if mode == "decrypt":
        key = 26-key
    key %= 26
    for i in range(len(msg)):
        base = 65 if msg[i].isupper() else 97
        msg[i] = chr(((ord(msg[i])-base)+key)%26+base) 
    return ''.join(msg)

def xor_strings(s, t) -> bytes:
    """xor two strings together."""
    if isinstance(s, str):
        # Text strings contain single characters
        return b"".join(chr(ord(a) ^ ord(b)) for a, b in zip(s, t))
    else:
        # Bytes objects contain integer values in the range 0-255
        return bytes([a ^ b for a, b in zip(s, t)])
    

def one_time_pad_xor(msg, key, mode="encryption"):
    key = long_as_msg(key, len(msg))
    text = xor_strings(msg.encode('utf-8'), key.encode('utf-8'))
    return text.decode('utf-8')


def monoalphabetic_substitution(msg,psr,mode='encrypt'):
    if mode == 'decrypt':
        dec=[]
        for m in msg:
            if m.isupper():
                dec.append(chr(psr.index(m.lower())+65))
            else:
                dec.append(chr(psr.index(m)+97))
        return ''.join(dec)
    else:
        enc = []
        for m in msg:
            if m.isupper():
                enc.append(psr[ord(m)-65].upper())
            elif m == " ":
                enc.append(" ")
            else:
                enc.append(psr[ord(m)-97])
        return ''.join(enc)
            