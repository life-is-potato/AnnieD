use:
- make > build.log 2>&1 : compilation errors into a log file for easier bug fixes
- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./AnnieD > valgrind_log.txt 2>&1 : memory leaks full log for better memory management
- #include <gc.h> GC_INIT(); <- once at the beginning, GC_MALLOC(); instead of malloc, it's a garbage collector, manages memory on it's own and frees it
* sudo apt install valgrind -y : if not already installed