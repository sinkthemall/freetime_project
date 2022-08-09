class TodoList:
    from authentication import account
    
    def __init__(self, acc : account) -> None:
        import os 
        self.todo = []
        self.path = os.path.dirname(__file__)
        self.user = acc
        if self.user.islogin:
            from dataencode import decodedata
            enc = b''
            try:
                enc = open(self.path + '\\securedata\\' + self.user.username, 'rb').read()
            except:
                enc = b''
            if enc == b'':
                return 
            data = decodedata(enc, self.user)
            data = data.split('\n')
            self.todo = []
            for i in data:
                if i != '':
                    self.todo.append(i)
    """
    def get_user(self, acc : account):
        self.user = acc
        if self.user.islogin:
            from dataencode import decodedata
            enc = b''
            try:
                enc = open(self.path + '\\securedata\\' + self.user.username, 'rb').read()
            except:
                enc = b''
            if enc == b'':
                return 
            data = decodedata(enc, self.user)
            data = data.split('\n')
            self.todo = []
            for i in data:
                self.todo.append(i)
    """
    def list_to_do(self):
        if not self.user.islogin:
            raise Exception("You have to login first!!!")
        return self.todo
    
    def append(self, name):
        if not self.user.islogin:
            raise Exception("You have to login first!!!")
        if name in self.todo:
            raise Exception("Task is already in todo list!!!")   
        self.todo.append(name)

    def remove(self, name):
        if not self.user.islogin:
            raise Exception("You have to login first!!!")
        if not name in self.todo:
            raise Exception("Task isn't in todo list!!!")
        self.todo.remove(name)
        
    def record(self):
        if not self.user.islogin:
            raise Exception("You have to login first!!!")
        data = '\n'.join(self.todo)
        from dataencode import encodedata
        data = encodedata(data, self.user)
        open(self.path + '\\securedata\\' + self.user.username, 'wb').write(data)
    
    