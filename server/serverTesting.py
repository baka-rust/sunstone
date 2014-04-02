import socket

players = {}

class Server:
	
	port = 666

	def __init__(self):
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.sock.bind(("", self.port))
	
	def run(self):
		
		while True:
			try:
				data, addr = self.sock.recvfrom(2048)
				data = data.split(",")
			
			except:
				print "data recv error"
			
			if data[0] == "1":
				if not data[1] in players.keys():
					print data[1] + " joined the server"
					players[data[1]] = Player(data[1], 1, 1, "down", addr)
					for player in players:
						if player != data[1]:
							#tell other player about new one
							packet = "1," + players[data[1]].name + "," + str(players[data[1]].x) + "," + str(players[data[1]].y) + "," + players[data[1]].direction + ","
							self.sock.sendto(packet, (players[player].addr[0], players[player].addr[1])) 
							
							#tell new one about other player
							packet = "1," + players[player].name + "," + str(players[player].x) + "," + str(players[player].y) + "," + players[player].direction + ","
							self.sock.sendto(packet, (players[data[1]].addr[0], players[data[1]].addr[1]))
						
			elif data[0] == "2":
				print "position update from " + data[1] + " at " + data[2] + ", " + data[3] + " facing " + data[4]
				players[data[1]].x = int(data[2])
				players[data[1]].y = int(data[3])
				players[data[1]].direction = data[4]
				for player in players:
					if player != data[1]:
						packet = "2," + players[data[1]].name + "," + str(players[data[1]].x) + "," + str(players[data[1]].y) + "," + players[data[1]].direction + ","
						self.sock.sendto(packet, (players[player].addr[0], players[player].addr[1])) 

class Player:
	
	def __init__(self, name, x, y, direction, addr):
		self.name = name
		self.x = x
		self.y = y
		self.direction = direction
		self.addr = addr
	
	def update(self, x, y, direction):
		self.x = x
		self.y = y
		self.direction = direction
		
server = Server()
server.run()