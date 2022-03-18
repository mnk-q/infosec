from utils import emoji_convert, emoji_bring_back, monoalphabetic_key_generation

from random import shuffle
from algos import *

def fix_output(original, changed):
    changed = list(changed)
    for i in range(len(original)):
        if original[i] == " ":
            changed[i] = " "
    return ''.join(changed)


def main():
    ''' Main Event Loop '''
    s = '''The time taken for the three stages key generation, encryption and decryption processes using the proposed algorithm increases whenever the size of the plain text is Increased.' '''
    
    l = len(s)
    n = (l+1) // 2
    input_p1 = s[:n]
    input_p2 = s[n:]
    
    # Both of the parts would go to  3 layers of encryption seperately
    # Let's start with part 1
    input_p1_keys=["broomilda", "voldemort",7]
    input_p1_enc1 = odd_even_extraction_merging(input_p1, input_p1_keys[0], mode="encrypt")
    input_p1_enc2 = vigenere_cipher(input_p1_enc1, input_p1_keys[1],mode="encrypt")
    input_p1_enc3 = railFence(input_p1_enc2, input_p1_keys[2],mode="encrypt")
    
    input_p2_keys = [7, monoalphabetic_key_generation(),"JacksonVille", ]
    
    input_p2_enc1 = ceaser_cipher(input_p2, input_p2_keys[0],mode="encrypt") 
    input_p2_enc2 = monoalphabetic_substitution(input_p2_enc1, input_p2_keys[1], mode="encrypt")   
    input_p2_enc3 = odd_even_extraction_merging(input_p2_enc2, input_p2_keys[2],mode="encrypt")
    
    
    emoji_output_p1 = emoji_convert(input_p1_enc3)
    emoji_output_p2 = emoji_convert(input_p2_enc3)
    
    input_p1_dec3 = emoji_bring_back(emoji_output_p1)
    input_p1_dec2 = railFence(input_p1_dec3, input_p1_keys[2],mode="decrypt")
    input_p1_dec1 = vigenere_cipher(input_p1_dec2, input_p1_keys[1],mode="decrypt")
    input_p1_dec0 = odd_even_extraction_merging(input_p1_dec1, input_p1_keys[0], mode="decrypt")
    
    input_p2_dec3 = emoji_bring_back(emoji_output_p2)
    input_p2_dec2 = odd_even_extraction_merging(input_p2_dec3, input_p2_keys[2],mode="decrypt")
    input_p2_dec1 = monoalphabetic_substitution(input_p2_dec2, input_p2_keys[1],mode="decrypt")
    input_p2_dec0 = ceaser_cipher(input_p2_dec1, input_p2_keys[0], mode="decrypt")

    decrypted_s = fix_output(s, input_p1_dec0+input_p2_dec0)
    print(f'''
          Input : {s}
          ----------After - Encryption - Stage - 1
          Part 1 : {input_p1_enc1}      
          Part 2 : {input_p2_enc1} 
          
          --------- After Encryption - Stage - 2-
          Part 1 : {input_p1_enc2} 
          Part 2 : {input_p2_enc2}
          
          --------- After Encryption - Stage - 3-
          Part 1 : {input_p1_enc3} 
          Part 2 : {input_p2_enc3}
          
          ------ EMOJI Conversion ---------------
          Emoji Output 
          {emoji_output_p1 + emoji_output_p2}
          
          ----------------- Decryption Starts-----
          
          ------------------After Decryption - Stage - 1--
          Part 1 : {input_p1_dec3} 
          Part 2 : {input_p2_dec3}
          
          -----------------After Decryption - Stage - 2- --
          Part 1 : {input_p1_dec2} 
          Part 2 : {input_p2_dec2}
          
           -----------------After Decryption - Stage - 3- --
          Part 1 : {input_p1_dec1} 
          Part 2 : {input_p2_dec1}
          
           -----------------After Decryption - Stage - 4- --
          Part 1 : {input_p1_dec0} 
          Part 2 : {input_p2_dec0}
          
          ------------------- Final Output ------------------
          
          {decrypted_s}
          ''')
    
    
    
    
    
if __name__ == "__main__":

    main()