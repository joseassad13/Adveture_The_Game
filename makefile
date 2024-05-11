bin/adventure :  src/adventure_game.cpp
	g++ src/adventure_game.cpp -o bin/adventure -I include -lftxui-screen -lftxui-dom -lftxui-component -std=c++2a

run : bin/adventure
	./bin/adventure