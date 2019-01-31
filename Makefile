all:
	$(CXX) main.cpp sujson.cpp -O -std=c++11 -o test
run:
	.\test
  
