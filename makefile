all:
	clear
	# gcc tetris.c proc_grafico.s -o exe
	gcc casos_teste.c proc_grafico.s -o exe
	sudo ./exe
