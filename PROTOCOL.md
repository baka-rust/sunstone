# Network Protocol

Sever acts as a "relay" of sorts (while still checking stuff is valid)
All strings are UTF null terminated ("\0")

Mobs are treated by the client as differet "types" of players,
types are also classes and the like (for drawing)

Join:
	Client:	1,{name},{x},{y},{direction},{type},
	Server:	1,{name},{x},{y},{direction},{type},

Movement Update:
	Client: 2,{name},{x},{y},{direction},
	Server: 2,{name},{x},{y},{direction},
	
Map Request/Report:
	Client: 3,
	Server: 3,{seed},
	(maps assumed to be 128x128)

Attack:
	Client: 4,{username}-{projcID},{x},{y},{direction},
	Server: 4,{username}-{projcID},{x},{y},{direction},

Cull Projectile:
	Client: N/A
	Server: 5,{username}-{projcID},
