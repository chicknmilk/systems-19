all: user.c worker.c
	gcc -o user user.c
	gcc -o worker worker.c

p:
	git add .
	git commit -m "push to comp"
	git push