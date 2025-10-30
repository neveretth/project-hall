cdef extern from "host.c":
    int hall_read(float* buf);
    int arduino_init();
    int arduino_finalize();

# Read without performing math.
cpdef read(float[:] buf):
    return hall_read(&buf[0])

cpdef init():
    return arduino_init()

cpdef end():
    return arduino_finalize()
