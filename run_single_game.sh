#!/bin/bash

function trap_ctrlc ()
{
    # perform cleanup here
    echo "Exiting..."
	killall chess
	killall flask
	killall python
    exit 2
}

#trap "trap_ctrlc" 2
DIRECTORY=`dirname $0`
cd "$DIRECTORY"

source web/venv/bin/activate
echo "Running application"
echo "Open your browser http://127.0.0.1:$2 to play chess"
echo "Open your browser http://127.0.0.1:$3 to play chess"
{
#	killall chess
	./build/chess $1 &
	cd web
	python app.py -p $2 -s $1 -c white &
	python app.py -p $3 -s $1 -c black
} &> /dev/null
#}
echo "Error running application"
