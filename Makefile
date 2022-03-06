CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g

hinfosvc: hinfo.o HTTPServer.o Request.o Response.o SysInfo.o
	$(CXX) $(CXXFLAGS) -o $@ $^	

run: hinfosvc
	./hinfosvc 12345

.PHONY: clean
clean:
	rm -rf *.o hinfosvc