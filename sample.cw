--pong 128

--ball
var ballx = 64
var bally = 64
var dx = 1 --true
var dy = 1 --true

-- peddle left
var lx = 5
var ly = 1
var lw = 5
var lh = 10

-- peddle right
var rx = 118
var ry = 1
var rw = 5
var rh = 10

var gameloop = 1 --true
while gameloop
	update()
	draw()
end

action draw()
	circle(ballx,bally,4) --(x,y,radius)
	rect(lx,ly,lw,lh) --(x,y,width,height)
	rect(rx,ry,rw,rh) --(x,y,width,height)
	line(64,0,64,128)
end

action update()
	if dx --if true
		ballx += 1
	else
		ballx -= 1

	if dy --if true
		bally += 1
	else
		bally -= 1

	if ballx < 1 || ballx > 127
		dx = !dx
	if bally < 1 || bally > 127
		dy = !dy

	if bally < ly
		ly -= 1
	elseif bally > ly+lh
		ly +=1

	if bally < ry
		ry -= 1
	elseif bally > ry+rh
		ry +=1

	if ballx > lx && ballx < lx+lw && bally > ly && bally < ly+lh
		dx = 1 --true 
	if ballx > rx && ballx < rx+rw && bally > ry && bally < ry+rh
		dx = 0 --false
end