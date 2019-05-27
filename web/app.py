from flask import Flask, render_template, request
import socket
import sys

app = Flask(__name__)

board = []
# store all squares on board
message = "White turn!"
# wrong_move = False

def updateMessage(staus):
	return False;


def updateBoard(recived_data):
	global board
	status = recived_data[0:6]
	board_data = recived_data[7:]
	updateMessage(status)

	# update board
	board = []
	square = board_data.split(';')
	# print ('SQUARE', square)
	for el in square:
		field = el.split(',')
		square_col = field[0]
		figure_col = field[1]
		figure = field[2]
		position = field[3]
		code = field[4]

		if figure_col == '':
			figure_col = 'None'
			figure = 'None'
			code = 'None'

		board.append({
			'square_color' : square_col,
			'color' : figure_col,
			'figure' : figure,
			'position' : position,
			'code' : code
		})

	for el in board:
		print (el)
	return True



def sendData(move):
	print ('send move: ', move)
	# send data to cpp socket
	HOST = '0::1'    # The remote host
	PORT = 8001      # The same port as used by the server
	try:
		s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
		s.connect((HOST, PORT))
		if move != None:
			move = move.encode()
		else:
			return False
		print ('Send data function')
		s.send(move)
		data = s.recv(2048)			# Return data from server in binary stream
		# print('Received from server:', data)
		server_resp = str(data, 'utf-8')
		# print ("RECIVED", server_resp) # in string form
		# updateData(move, server_resp)
		updateBoard(server_resp)
		s.close()

	except socket.error as e:
	    print ("Socket error({0}): {1}".format(e.errno, e.strerror))
	except:
	    print ("Unexpected error:", sys.exc_info()[0])
	    raise
	return

def printer():
	for el in board:
		print (el)

start_game = True

@app.route("/", methods = ['GET', 'POST'])
def function():
	global start_game
	if start_game == True:
		print ('Start game')
		start_game = False
		move = 'e6' # i send wrong move to synchronize database
		sendData(move)

	if request.method == 'POST':
		move = request.form.get('move')
		print ("move:" , move)
		print ('type move before function', type(move))
		if move != '':
			if sendData(move) == False:
				print ('Could not send string')
		# printer()
		return render_template("index.html", board = board, len = len(board), message = message)
	else:
		return render_template("index.html", board = board, len = len(board), message = message)


if __name__ == "__main__":
	app.run()
