RSA PEM文件格式
1.PEM私钥格式文件
-----BEGIN RSA PRIVATE KEY-----
-----END RSA PRIVATE KEY-----

2. PEM公钥格式文件
-----BEGIN PUBLIC KEY-----
-----END PUBLIC KEY-----

3. PEM RSAPublicKey公钥格式文件
-----BEGIN RSA PUBLIC KEY-----
-----END RSA PUBLIC KEY-----

OpenSSL密钥相关命令
1. 生成密钥
openssl genrsa -out key.pem 1024
    -out 指定生成文件，此文件包含公钥和私钥两部分，所以即可以加密，也可以解密
    1024 生成密钥的长度

2. 提取PEM格式公钥
openssl rsa -in key.pem -pubout -out pubkey.pem
    -in 指定输入的密钥文件
    -out 指定提取生成公钥的文件(PEM公钥格式)

3. 提取PEM RSAPublicKey格式公钥
openssl rsa -in key.pem -RSAPublicKey_out -out pubkey.pem
    -in 指定输入的密钥文件
    -out 指定提取生成公钥的文件(PEM RSAPublicKey格式)

4. 公钥加密文件
openssl rsautl -encrypt -in input.file -inkey pubkey.pem -pubin -out output.file
    -in 指定被加密的文件
    -inkey 指定加密公钥文件
    -pubin 表面是用纯公钥文件加密
    -out 指定加密后的文件

5. 私钥解密文件
openssl rsautl -decrypt -in input.file -inkey key.pem -out output.file
    -in 指定需要解密的文件
    -inkey 指定私钥文件
    -out 指定解密后的文件

6. 私钥签名文件
openssl dgst -sign key.pem -sha1 -out plain.sign plain.txt

7. 公钥验证签名
openssl dgst -verify pubkey.pem -sha1 -signature plain.sign plain.txt
