use-gpg
=======

## 生成密钥

使用如下命令生成密钥

```sh
gpg --gen-key
```

回车后，会出现如下信息：

```txt
uso@u-os:~$ gpg --gen-key
gpg (GnuPG) 1.4.20; Copyright (C) 2015 Free Software Foundation, Inc.
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

gpg: keyring `/home/uso/.gnupg/secring.gpg' created
Please select what kind of key you want:
   (1) RSA and RSA (default)
   (2) DSA and Elgamal
   (3) DSA (sign only)
   (4) RSA (sign only)
Your selection?`
```
前面是版权声明，然后让用户选择加密算法。默认选择第一个，表示加密和签名都使用RSA算法。

上面选择后，系统就会问你密钥的长度，如下信息：

```txt
RSA keys may be between 1024 and 4096 bits long.
What keysize do you want? (2048)
```

密钥越长越安全，推荐使用4096。
接着会询问密钥的有效期，出现如下信息：

```txt
Please specify how long the key should be valid.
         0 = key does not expire
      <n>  = key expires in n days
      <n>w = key expires in n weeks
      <n>m = key expires in n months
      <n>y = key expires in n years
Key is valid for? (0)
```
如果密钥只是个人使用，并且你很确定可以有效保管私钥，建议选择第一个选项，即永不过期。
回答完上面三个问题以后，系统让你确认。

```txt
Is this correct? (y/N)
```

输入y，系统就要求你提供个人信息，出现如下信息：

```txt
You need a user ID to identify your key; the software constructs the user ID
from the Real Name, Comment and Email Address in this form:
    "Heinrich Heine (Der Dichter) <heinrichh@duesseldorf.de>"

Real name:
Email address:
Comment:
```

"真实姓名"填入你姓名的英文写法，"电子邮件地址"填入你的邮件地址，"注释"这一栏可以空着。
然后，你的"用户ID"生成了。

```txt
You selected this USER-ID:
    "zhenquan.qiu <gnsyxiang@163.com>"
```

我的"真实姓名"是zhenquan.qiu，"电子邮件地址"是gnsyxiang@163.com，
所以我的"用户ID"就是"zhenquan.qiu <gnsyxiang@163.com>"。系统会让你最后确认一次。

```txt
Change (N)ame, (C)omment, (E)mail or (O)kay/(Q)uit?
```

输入O表示"确定"。
接着，系统会让你设定一个私钥的密码。这是为了防止误操作，或者系统被侵入时有人擅自动用私钥。

```txt
You need a Passphrase to protect your secret key.

Enter passphrase: Gpg@2017_?
```

经过几分钟之后，系统提示密钥已经生成了，如下信息：

```txt
gpg: key F6E7A091 marked as ultimately trusted
public and secret key created and signed.

gpg: checking the trustdb
gpg: 3 marginal(s) needed, 1 complete(s) needed, PGP trust model
gpg: depth: 0  valid:   1  signed:   0  trust: 0-, 0q, 0n, 0m, 0f, 1u
gpg: next trustdb check due at 2017-08-19
pub   4096R/F6E7A091 2017-08-17 [expires: 2017-08-19]
      Key fingerprint = 9671 08FA 04B5 A137 98A2  57E8 823B 3612 F6E7 A091
uid                  zhenquan.qiu <gnsyxiang@163.com>
sub   4096R/A3866CE6 2017-08-17 [expires: 2017-08-19]
```

请注意上面的字符串"F6E7A091"，这是"用户ID"的Hash字符串，可以用来替代"用户ID"。
这时，最好再生成一张"撤销证书"，以备以后密钥作废时，可以请求外部的公钥服务器撤销你的公钥。

```txt
uso@u-os:~$ gpg --gen-revoke [用户ID]

sec  4096R/F6E7A091 2017-08-17 zhenquan.qiu <gnsyxiang@163.com>

Create a revocation certificate for this key? (y/N) y
Please select the reason for the revocation:
  0 = No reason specified
  1 = Key has been compromised
  2 = Key is superseded
  3 = Key is no longer used
  Q = Cancel
(Probably you want to select 1 here)
Your decision? 
Enter an optional description; end it with an empty line:
> 
Reason for revocation: Key has been compromised
(No description given)
Is this okay? (y/N) y

You need a passphrase to unlock the secret key for
user: "zhenquan.qiu <gnsyxiang@163.com>"
4096-bit RSA key, ID F6E7A091, created 2017-08-17

ASCII armored output forced.
Revocation certificate created.

Please move it to a medium which you can hide away; if Mallory gets
access to this certificate he can use it to make your key unusable.
It is smart to print this certificate and store it away, just in case
your media become unreadable.  But have some caution:  The print system of
your machine might store the data and make it available to others!
-----BEGIN PGP PUBLIC KEY BLOCK-----
Version: GnuPG v1
Comment: A revocation certificate should follow

iQIfBCABAgAJBQJZlTyJAh0CAAoJEII7NhL256CRa40P/itFuSzEqC53PDwaoSRs
el6F3jnl9ZIgHW5BFGIOd3TGj5AJLqkuXQnGKmAaCDs87nKBo/6dQxjosnR4zkRJ
vOpSAhHpC7cAhF1TmDmQdnKNIizb9G/LCMgBlXNQrHPi/NwSXLSMIGavObWQ8+ow
GoXYAwJYWLdfwh1CYMuax7RSeQ2+3PMfU2lwVkTpv2qY4tXcObpfJZdXCW0cGSkK
YSoEnHK4ivNZeBvwu6u2WQvVvXZuERvSN9bbyYVCEYWY0+bGGc+AlWSNoQrVB+oD
qreBbHP7VkbHBOrCA6XVvC+3y0tbh00vvaa3K1M9BP//TYgKzLrNp+cZ46CZtXVd
vjjtohnX63ZKJJv9djsBomaVT/YGAiYm8wvJ5ZxI1Bmqfv30J7krfdx0qG3i1zyz
MYS9OPuT0PwAeUdQw5LxBTQ3f1g4D3Yw0fbGkNpnW7/lspgBHcHaJn4sNOny10aO
+L/Pah9SpitCzp6AD1KKyVJjeNCCrJha+BDv40bJIIkxEyWvx7hM2Es3skspZqUs
QUuTfQ5mJO86Qtvxluuw//JbQEFvJpTPAU279QUar673aqQU8xD9YSih0h0k9NYB
sQ1RyO/y522astainSGDjfgEpWd+Twa5n4xm4LGaeIkTes3JRh9etJ9KVLVQ+d2s
pevFX+RgV5WipgMyjrO2aA/Y
=CqCw
-----END PGP PUBLIC KEY BLOCK-----
```

> note: 用户ID，指邮件地址或者Hash字符串（以下同）

## 密钥管理

### 查看密钥

```sh
uso@u-os:~$ gpg --list-key
/home/uso/.gnupg/pubring.gpg
----------------------------
pub   4096R/F6E7A091 2017-08-17 [expires: 2017-08-19]
uid                  zhenquan.qiu <gnsyxiang@163.com>
sub   4096R/A3866CE6 2017-08-17 [expires: 2017-08-19]

```
第一行显示公钥文件名（pubring.gpg）  
第二行显示公钥特征（4096位，Hash字符串，生成时间和到期时间）  
第三行显示"用户ID"  
第四行显示私钥特征  

### 删除密钥

```sh
gpg --delete-key [用户ID]
```

### 输出密钥

```sh
gpg --armor --output public-key.txt --export [用户ID]
```
公钥文件（.gnupg/pubring.gpg）以二进制形式储存，armor参数可以将其转换为ASCII码显示。







