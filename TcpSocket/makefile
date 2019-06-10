all : server client
muti_thr_server:muti_thr_server.cpp
	g++ $^ -o $@ -lpthread
muti_pro_server:muti_pro_server.cpp
	g++ $^ -o $@
server:server.cpp
	g++ $^ -o $@
client: client.cpp
	g++ $^ -o $@
