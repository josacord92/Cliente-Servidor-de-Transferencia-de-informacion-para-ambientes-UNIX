bftp: fttp.c Base64Encode.c Base64Decode.c comodin.c
	gcc -w fttp.c Base64Encode.c Base64Decode.c  comodin.c -lcrypto -lm -lpthread -o bftp
