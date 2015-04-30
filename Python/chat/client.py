'''
KTN-project 2014
Very simple client implementation
Group 75
'''
import socket
from threading import Thread
import json
import sys
import MessageWorker

class Client(object):

    def __init__(self):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def start(self, host, port):
        msg = ''
        connected = False
        while not connected:
            try:
                self.connection.connect((host, port))
                connected = True
            except socket.error:
                print 'Server not online!'
                ans = ''
                while ans != 'y' and ans != 'n':
                    ans = raw_input('Try again?(y/n): ')
                    if ans == 'n':
                        print 'Bye!'
                        sys.exit(0)
                    elif ans == 'y':
                        continue
                    else:
                        print 'Type y or n.'

        username = self.login()

        self.messageWorker = MessageWorker.ReceiveMessageWorker(client, self.connection)
        self.messageWorker.start()

        while True:
            msg = raw_input()
            if msg == 'quit':
                self.logout(username)
                break
            else:
                data = {'request': 'message','message': msg}
            data = json.dumps(data)
            self.send(data)
        self.connection_closed()
        print 'Disconnected!'

    def message_received(self, message):
        response = json.loads(message)
        try:
            print response['message']
        except:
            pass

    def connection_closed(self):
        self.messageWorker.finished = True
        self.connection.close()

    def send(self, data):
        self.connection.sendall(data)

    def force_disconnect(self):
        pass
    
    def login(self):
        while True:
            nick = raw_input('Enter your username: ')
            data = {'request': 'login', 'username': nick}
            self.send(json.dumps(data))
            response = self.connection.recv(1024).strip()
            response = json.loads(response)

            if response.has_key('error'):
                print response['error']
            else:
                print 'Logged in!'
                if response['messages']:
                    print response['messages']
                return nick
		
    def logout(self, username):
        data = {'request': 'logout'}
        self.send(json.dumps(data))

if __name__ == "__main__":
    client = Client()
    client.start('localhost', 9999)
