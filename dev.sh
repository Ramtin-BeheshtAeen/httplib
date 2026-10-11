S=dev
DIR=~/project            # change to your project folder

tmux has-session -t $S 2>/dev/null && exec tmux attach -t $S

tmux new-session  -d -s $S -n code -c $DIR
tmux send-keys    -t $S:code 'emacs .' C-m

tmux new-window   -t $S -n run -c $DIR
tmux split-window -h -t $S:run   -c $DIR    # right half
tmux split-window -v -t $S:run.1 -c $DIR    # split right half: server / client

tmux select-window -t $S:code
exec tmux attach -t $S
