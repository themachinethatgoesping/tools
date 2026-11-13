
def clear_memory():
    import gc
    gc.collect()
    
    # Trim cache of gcc libc library
    try:
        import ctypes
        libc = ctypes.CDLL("libc.so.6") # clearing cache 
        libc.malloc_trim(0)
    except:
        pass