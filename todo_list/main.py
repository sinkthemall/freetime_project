from authentication import account
from todo import TodoList
class TodoListInterface:
    def __init__(self) :
        self.curAcc = account() 
        self.command = {"reg" : self.register_account, "login" : self.login_account, "remove" : self.removetask, "complete" : self.completetask, "add" : self.addtask, "list" : self.task_list, "help" : self.Help}
    def register_account(self):
        username = input("Enter your username you want to register: ")
        password = input("Enter your password you want to register: ")
        self.curAcc.create_account(username, password)
        print("You have registered successfully!!!")

    def login_account(self):
        username = input("Enter your username: ")
        password = input("Enter your password: ")
        try:
            self.curAcc.login(username, password)
        except:
            print("Your account has not been registered!!!")
            return
        print("You have login successfully!!!")

    def task_list(self):
        if not self.curAcc.islogin:
            print("You have to login first!!!")
            return 
        print("############################################")
        print("TODO LIST:")
        for i,j in enumerate(TodoList(self.curAcc).list_to_do()):
            print(i + 1, ")", j)
        print("############################################")

    def addtask(self):
        if not self.curAcc.islogin:
            print("You have to login first!!!")
            return 
        taskname = input("Enter your task name: ")
        task_todo = TodoList(self.curAcc)
        try:
            task_todo.append(taskname)
        except:
            print("Task already existed!!!")
            return
        task_todo.record()
        print("Task update succeed!!!")

    def removetask(self):
        if not self.curAcc.islogin:
            print("You have to login first!!!")
            return
        self.task_list()
        tasknum = int(input("Enter task number you want to remove: "))
        task = TodoList(self.curAcc).list_to_do()
        if tasknum > len(task):
            print("Sorry, your task number doesn't exist!!!")
            return
        taskname = task[tasknum - 1]
        task_todo = TodoList(self.curAcc)
        try:
            task_todo.remove(taskname)
        except:
            print("Something went wrong!!!")
            return
        task_todo.record()
        print("Successfully remove the task!!!")
    
    def completetask(self):
        if not self.curAcc.islogin:
            print("You have to login first!!!")
            return
        self.task_list()
        tasknum = int(input("Enter your task number to complete: "))
        task = TodoList(self.curAcc).list_to_do()
        if tasknum > len(task):
            print("Sorry, your task number doesn't exist!!!")
            return
        taskname = task[tasknum - 1]
        task_todo = TodoList(self.curAcc)
        try:
            task_todo.remove(taskname)
        except:
            print("Something went wrong!!!")
            return
        task_todo.record()
        print("You have completed the task! Congratulations!!!")
    
    def Help(self):
        print("Current command's list")
        print("reg : register account")
        print("login : login account")
        print("remove : remove task (you have to login to be able to remove task)")
        print("complete : complete task (you have to login to be able to complete task)")
        print("add : adding a task (you have to login to be able to add task)")
        print("list : listing all task (you have to login to be able to list tasks)")
        print("exit : exit program")
        input("Press enter key to finish manual!!!")
        print("")
    def interface(self):
        print("WELCOME TO TODO LIST PROGRAM (beta test v1.0)")
        print("If you are new here, type 'help' for more information.")
        while True:
            cmd = input(">>> ")
            if not cmd in self.command:
                print("Your command is not valid!!!")
            elif cmd == "exit":
                exit(0)
            else:
                self.command[cmd]()


program = TodoListInterface()
program.interface()

