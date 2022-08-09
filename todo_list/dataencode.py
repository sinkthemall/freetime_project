from authentication import account
def encodedata(data : str, acc: account) -> bytes:
    from hashlib import sha256
    from Crypto.Util.Padding import pad
    from Crypto.Cipher import AES
    data = pad(data.encode(), 16) 
    cipher = AES.new(sha256((acc.username + acc.password).encode()).digest()[:16], AES.MODE_ECB)
    newdata = cipher.encrypt(data)
    return newdata
def decodedata(data : bytes, acc : account) -> str:
    from hashlib import sha256
    from Crypto.Util.Padding import unpad
    from Crypto.Cipher import AES
    cipher = AES.new(sha256((acc.username + acc.password).encode()).digest()[:16], AES.MODE_ECB)
    newdata = unpad(cipher.decrypt(data), 16)
    return newdata.decode()
 