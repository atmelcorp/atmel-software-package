#!/bin/bash

# DES, Electronic Code Book mode
t=des-ecb; openssl enc -$t -nopad -K 67452301EFCDAB89 -e -in example.txt -out $t.tdes

# DES, Cipher Block Chaining mode
t=des-cbc; openssl enc -$t -nopad -K 67452301EFCDAB89 -iv 4433221188776655 -e -in example.txt -out $t.tdes

# Triple DES, Electronic Code Book mode
t=des-ede3; openssl enc -$t -nopad -K 67452301EFCDAB891032547698BADCFEAA55AA5555AA55AA -e -in example.txt -out $t.tdes

# Triple DES, Cipher Block Chaining mode
t=des-ede3-cbc; openssl enc -$t -nopad -K 67452301EFCDAB891032547698BADCFEAA55AA5555AA55AA -iv 4433221188776655 -e -in example.txt -out $t.tdes
