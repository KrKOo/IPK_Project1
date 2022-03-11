CXX = g++
CXXFLAGS = -Wall -Wextra -Werror
# Default port
PORT = 12345

hinfosvc: main.o HTTPServer.o Request.o Response.o SysInfo.o
	$(CXX) $(CXXFLAGS) -o $@ $^

run: hinfosvc
	./hinfosvc $(PORT)

.PHONY: clean
clean:
	rm -rf *.o hinfosvc
