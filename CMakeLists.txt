#设置项目名称
PROJECT(system)

#要求CMake的最低版本为2.8
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#添加头文件搜索路径
INCLUDE_DIRECTORIES(/usr/local/include)

#添加库文件搜索路径
LINK_DIRECTORIES(/usr/local/lib /usr/lib)


ADD_LIBRARY(errorFunc lib/error_functions.c lib/get_num.c)


#用于指定从一组源文件 source1 source2 … sourceN(在变量DIR_SRCS中定义)
#编译出一个可执行文件且命名为CMake_Tutorial1
ADD_EXECUTABLE(mkstemp mkstemp.c)
ADD_EXECUTABLE(tmpfile tmpfile.c)

ADD_EXECUTABLE(copy chapter4_general_io_model/copy.c)
TARGET_LINK_LIBRARIES(copy errorFunc)


ADD_EXECUTABLE(unlink chapter18_directory_and_link/unlink.c)
TARGET_LINK_LIBRARIES(unlink errorFunc)


ADD_EXECUTABLE(symlink chapter18_directory_and_link/symlink.c)
TARGET_LINK_LIBRARIES(symlink errorFunc)


ADD_EXECUTABLE(inotify chapter19_monitor_file_events/inotify.c)
TARGET_LINK_LIBRARIES(inotify errorFunc)


ADD_EXECUTABLE(signal chapter20_signal_basic_concept/signal.c)
TARGET_LINK_LIBRARIES(signal errorFunc)

ADD_EXECUTABLE(intquit chapter20_signal_basic_concept/intquit.c)
TARGET_LINK_LIBRARIES(intquit errorFunc)

ADD_EXECUTABLE(scanProcessID chapter20_signal_basic_concept/scan_process_id.c)
TARGET_LINK_LIBRARIES(scanProcessID errorFunc)

ADD_EXECUTABLE(sigset chapter20_signal_basic_concept/sigset.c)
TARGET_LINK_LIBRARIES(sigset errorFunc)

ADD_EXECUTABLE(nonreentrant chapter21_signal_signal_handler/nonreentrant.c)
TARGET_LINK_LIBRARIES(nonreentrant errorFunc crypt)

ADD_EXECUTABLE(siginfo chapter21_signal_signal_handler/siginfo.c)
TARGET_LINK_LIBRARIES(siginfo errorFunc)

ADD_EXECUTABLE(settimer chapter23_timer_and_sleep/settimer.c)
TARGET_LINK_LIBRARIES(settimer errorFunc)

ADD_EXECUTABLE(timedRead chapter23_timer_and_sleep/timed_read.c)
TARGET_LINK_LIBRARIES(timedRead errorFunc)

ADD_EXECUTABLE(fork_stdio_buf chapter25_termination_of_the_process/fork_stdio_buf.c)
TARGET_LINK_LIBRARIES(fork_stdio_buf errorFunc)


ADD_EXECUTABLE(pthread_join_self chapter29_pthread_intro/pthread_join_self.c)
TARGET_LINK_LIBRARIES(pthread_join_self errorFunc pthread)

ADD_EXECUTABLE(pthread_mutex chapter30_thread_synchronization/pthread_mutex.c)
TARGET_LINK_LIBRARIES(pthread_mutex errorFunc pthread)

ADD_EXECUTABLE(simple_pipe chapter44_pipe_and_fifo/simple_pipe.c)
TARGET_LINK_LIBRARIES(simple_pipe errorFunc)

ADD_EXECUTABLE(pipe_sync chapter44_pipe_and_fifo/pipe_sync.c)
TARGET_LINK_LIBRARIES(pipe_sync errorFunc)

ADD_EXECUTABLE(getaddrinfo chapter59_internet_domain_socket/getaddinfo.c)
TARGET_LINK_LIBRARIES(getaddrinfo errorFunc)

ADD_EXECUTABLE(inet_ntop chapter59_internet_domain_socket/inet_ntop.c)
TARGET_LINK_LIBRARIES(inet_ntop errorFunc)

ADD_EXECUTABLE(inet_pton chapter59_internet_domain_socket/inet_pton.c)
TARGET_LINK_LIBRARIES(inet_pton errorFunc)