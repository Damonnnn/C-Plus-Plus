obj := chat_server.c
obj2 := chat_client_a.c
obj3 := chat_client_b.c
obj4 := chat_client_c.c

all:server client_a client_b client_c

server: $(obj)
	gcc -g $^ -o $@
client_a: $(obj2)
	gcc -g $^ -o $@
client_b:$(obj3)
	gcc -g $^ -o $@
client_c:$(obj4)
	gcc -g $^ -o $@

.PHONY: clean
clean:
	rm -f *.o server client_a client_b client_c

