CFLAGS          = -g
CXXFLAGS        = -Wall -g
OBJS            = main.o termbox.o utf8.o Player.o Input.o
testtb: $(OBJS)
	$(CXX) -o $@ $(OBJS)
