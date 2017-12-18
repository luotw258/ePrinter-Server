rm ./app
clear
g++ -o app main_thread.cpp connect_thread.cpp server_net.cpp sql.cpp connect.cpp -std=c++0x -lmysqlclient -Wall -O2 -pthread > out.txt 2>&1

cat out.txt | grep "error"
./app

ps -aux | grep "./app"
