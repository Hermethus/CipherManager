# -*- coding: utf-8 -*-

from Crypto.Cipher import AES
import hashlib

secret = "1234567891234567"

class CipherManager:

    
    def __init__(self, password, file_path=None, new=True):
        
        self.set_password(password)
        self.code_dict = dict()
        
        if new:
            if file_path:
                self.code_dict = read_plaintext(file_path)

        else:
            self.code_dict = read_and_decrypt(self.cipher, file_path)
                    
        
    def set_password(self, password):
        m = hashlib.md5()
        m.update(bytes(password, encoding="utf-8"))
        self.password = m.hexdigest()
        self.cipher = AES.new(self.password)
        
    def save(self, filename = 'MC.cipher'):
        s = encrypt(self.code_dict, self.cipher)
        with open(filename, 'wb') as f:
            f.write(s)
    
    def save_as_plain(self, filename = 'MC.txt'):
        with open(filename, 'w') as f:
            for item in self.code_dict.items():
                f.write(item[0]+" "+item[1][0]+" "+item[1][1]+"\n")
    
    def modify(self, key, value, name_or_password):
        #name_or_password = 0 修改用户名 name_or_password = 1 修改密码
        if key in self.code_dict:
            try:
                self.code_dict[key][name_or_password] = value
            except:
                print('输入错误')
        else:
            print("不存在{}".format(key))

    def add(self, key, username, password):
        if not key in self.code_dict:
            self.code_dict[key] = [username,password]
            return True
        else:
            return False
    
    def delete(self, key):
        self.code_dict.pop(key, '')
    
    def get(self, key):
        if key in self.code_dict:
            return self.code_dict[key]
        else:
            return None

    def print_item(self, key):
        if key in self.code_dict:
            print('{0:<16}| {1:<17}| pw: {2}'.format(key, self.code_dict[key][0], self.code_dict[key][1]))
        else:
            print("不存在{}".format(key))
    
    def search(self, word):
        if word=="*":
            word = ""
        result = []
        for item in self.code_dict:
            if word in item:
                result.append(item)
        return result


def read_cipher_text(filename):
    #读取密文文件
    try:
        with open(filename, 'rb') as f:
            s = f.read()
        return s
    except IOError:
        print("文件打开失败！")

def decrypt(s, cipher):
    #将密文解码为dict
    return eval(cipher.decrypt(s).decode())
#    return eval(str(cipher.decrypt(s))[2:-1].rstrip(' '))


def read_and_decrypt(cipher, filename):
    s = read_cipher_text(filename)
    return decrypt(s, cipher)


def padding(bytes_in):
    #填充明文使其长度符合16的倍数
    mod = len(bytes_in) % 16
    if mod != 0:
        bytes_in += b' '*(16-mod)
    return bytes_in


def encrypt(message, cipher):
    #加密，返回密文
    plaintext = str(message).encode()#使用utf-8
    plaintext = padding(plaintext)
    s = cipher.encrypt(plaintext) 	#输入需要加密的字符串，注意字符串长度要是16的倍数
    return s


def read_plaintext(file_path):
    #从格式化文件读入数据，转为dict
    code_dict = dict()
    with open(file_path, "r") as f:
        while True:
            tmp = f.readline().split()
            if len(tmp) == 0:
                break
            code_dict[tmp[0]] = tmp[1:]
    return code_dict

