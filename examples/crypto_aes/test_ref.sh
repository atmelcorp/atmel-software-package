#!/bin/bash

t=aes-128-ecb; openssl enc -$t -nopad -K 67452301EFCDAB891032547698BADCFE -e -in example.txt -out $t.aes

t=aes-128-cbc; openssl enc -$t -nopad -K 67452301EFCDAB891032547698BADCFE -iv 44332211887766552222111144443333 -e -in example.txt -out $t.aes
