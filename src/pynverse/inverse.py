import numpy as np
import re
import math
from typing import Annotated
from numpy.typing import NDArray
from pathlib import Path
from ._native import core

SquareMatrix = Annotated[
    NDArray[np.float32],
    "shape: (n, n)"
]

class NumbersNotFoundException(Exception):
    pass

class InvalidMatrixException(Exception):
    pass

def _check_perfect_square(number_elements : int) -> bool:
    sqrt = number_elements**(0.5)

    upper_bound = math.ceil(sqrt)
    lower_bound = math.floor(sqrt)

    return True if lower_bound == upper_bound else False

def _check_dimension(origin_arr) -> np.ndarray:

    """If the type of the passed array is a numpy array, just check for the case
        where the array is 1-dimensional, other cases numpy takes care of possible errors"""
    if isinstance(origin_arr, np.ndarray):

        if origin_arr.ndim == 1:

            elements = len(origin_arr)
            if not _check_perfect_square(elements):

                raise InvalidMatrixException("Could not convert the matrix into a square matrix.")
        
        return origin_arr

    """If the type of the passed array is a list containing floats or integers, just check if
        the number of elements forms a perfect square (square matrix)"""
    
    """If the type of the passed array is a list of lists containing floats or integers,
        just return the np.array of that list, numpy takes care of possible errors"""
    if isinstance(origin_arr, list):

        if not isinstance(origin_arr[0], list):
            elements = len(origin_arr)

            if not _check_perfect_square(elements):
                raise InvalidMatrixException("Could not convert the matrix into a square matrix.")
            
            return origin_arr
        
        return origin_arr


    """If the type of the passed array is the path to a text file containing the array,
        we first have to check if the array only has one row, in that case we need to verify
        if the number of elements forms a perfect square. In the case where we have more than
        one row, just iterate over the lines storing the values in a temporary array, at the
        end return a numpy array of that temporary array, numpy takes care of any dimensional
        errors."""
    if isinstance(origin_arr, str):

        path = Path(origin_arr)

        if not path.is_absolute():
            path = Path.cwd() / path

        with open(path, 'r') as arq:
           lines = arq.readlines()
        
        len_lines = len(lines)
        
        if len_lines == 1:

            line = lines[0].strip().replace(',','.')

            numbers = re.findall(r'-?\d+\.?\d*', line)

            if numbers:

                elements = len(numbers)

                if not _check_perfect_square(elements):
                    raise InvalidMatrixException("Could not convert the matrix into a square matrix.")
                
                return [num for num in numbers]
            
            raise NumbersNotFoundException("Could not identify numbers in the text file.")
        
        tmp_array = []

        for line in lines:
            line = line.strip().replace(',','.')
            numeros = re.findall(r'-?\d+\.?\d*', line)

            if numeros:
                if len(numeros) == len_lines:
                    tmp_array.append([num for num in numeros])
                    continue
                
                raise InvalidMatrixException("Could not convert the matrix into a square matrix")

            raise NumbersNotFoundException("Could not identify numbers in the text file.")

        return tmp_array
    
    raise InvalidMatrixException("The given matrix is not supported.")


def inv(origin_arr : list[float | int] | np.ndarray[list[float | int]] | str | list[list[float | int]]) -> SquareMatrix:      
            
    origin_arr = np.ascontiguousarray(_check_dimension(origin_arr), np.float32)

    return core.inv_from_array(origin_arr)