from setuptools import setup, Extension

include_dirs = ['/usr/include/freetype2', 
                '/usr/include/freetype2/freetype', 
                '/data/deploy/opencv-3.4.0/include',
                '/home/niuwenhao/anaconda3/pkgs/python-3.7.3-h0371630_0/include/python3.7m/',
                '.'
                ]

extra_compile_args =  ['-std=c++11',
                       '-lfreetype', 
                       '-lopencv_core',
                       '-lopencv_highgui',
                       '-lopencv_highgui',
                       '-lopencv_imgcodecs',
                       '-L/usr/local/lib'
                       '-L/data/deploy/opencv-3.4.0/lib'
                      ]

opencv_puttext_support_cn_module = Extension(
        'opencv_puttext_support_cn',
        sources=['pytest.cpp', 'CvxText.cpp'],
        include_dirs = include_dirs,
        extra_compile_args=extra_compile_args,
)


setup(name='OpenCVputTextSupportCN',
      description='A package.',
      ext_modules=[opencv_puttext_support_cn_module],
)
