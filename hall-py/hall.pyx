cdef extern from "host.c":
    int hall_read(float* buf);

# Read without performing math.
cpdef read_raw(float[:] buf):
    return hall_read(&buf[0])

# TODO: The math adjusted stuff
# cpdef ???????(double[:] dest, int size):
#     return 
