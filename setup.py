from setuptools import setup, Extension
import numpy as np

ext = Extension(
    "pynverse._native.core",
    sources=[
        "src/pynverse/_native/core.c",
        "src/pynverse/_native/matriz.c",
        "src/pynverse/_native/matrix_api.c",
    ],
    include_dirs=[np.get_include(), "src/pynverse/_native"],
    extra_compile_args=["-O3"]
)

setup(
    ext_modules=[ext]
)
