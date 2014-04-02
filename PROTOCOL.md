# Network Protocol

Sever acts as a "relay" of sorts (while still checking stuff is valid)
All strings are UTF null terminated ("\0")

Mobs are treated by the client as differet "types" of players,
types are also classes and the like (for drawing)

Join:
	Client:	1,{username},{type},
	Server:	1,{username},{type},{x},{y},

Movement Update:
	Client: 2,{username},{x},{y},
	Server: 2,{username},{x},{y},
	
Map Request/Report:
	Client: 3,
	Server: 3,{seed},
	(maps assumed to be 128x128)

Attack: - (assuming can only attack 1 square, subject to change)
	Client: 4,{username},{direction},
	Server: 4,{username},{direction},

