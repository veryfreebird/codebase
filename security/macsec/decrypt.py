#!/usr/bin/env python

from Crypto.Cipher import AES
import binascii

key = binascii.unhexlify('11111111111111111111111111111111')
data = binascii.unhexlify('843c1e9600323c90c01dd388155f1b39dcaef0a1e4d41cde6e456e6b269fb88689ee8cfb6017eb96b27dfd5dad99d3a6cb1ebb15b73704aef16c1a6f7c0c90ca0a7801b65db4d746423ca7ec12a4c41f61ecbf1e2b998fb697c5db76d4307536187234b340c5')
nonce, tag = data[:12], data[-16:]
cipher = AES.new(key, AES.MODE_GCM, nonce)
cipher.decrypt_and_verify(data[12:-16], tag)


