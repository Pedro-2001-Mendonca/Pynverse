from .inverse import inv_from_array

# def inv(x, *args, **kwargs):
#     if isinstance(x, str):
#         return inv_from_file(x, *args, **kwargs)
    
#     else:
#         return inv_from_array(x, *args)

def inv(x):
    return inv_from_array(x)

__all__ = ["inv"]