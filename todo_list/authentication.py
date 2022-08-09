class account:
    def __init__(self):
        import os 
        self.username = ""
        self.password = ""
        self.islogin = False
        self.path = os.path.dirname(__file__)
    def password_hash(self):
        if not self.islogin:
            raise Exception("Account isn't login yet")
        from hashlib import sha1
        return sha1(self.password.encode()).digest()[:16].hex()
    def adding_data(self):
        data = self.username + ' ' + self.password_hash()
        open(self.path + '\\userdata\\data.txt', 'a').write(data + '\n')
    def create_account(self, username, password):
        self.username = username
        self.password = password
        self.islogin = True
        self.adding_data()
    def login(self, username : str, password : str):
        from hashlib import sha1
        for i in open(self.path + '\\userdata\\data.txt').readlines():
            user, passwordhash = i.split()
            if user != username:
                continue
            pw = sha1(password.encode()).digest()[:16].hex()
            if pw != passwordhash:
                continue
            self.islogin = True 
            self.username = username
            self.password = password
            return
        raise Exception("Your account has not been registered!!!")

    
            