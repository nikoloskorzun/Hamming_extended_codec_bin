# Hamming codec
hamming codec (or extended) realized with 2 matrix - generator and parity check matrixes

## Compile 
In /hamming_codec_lab/hamming_codec/init.h available 4 macros
### WIN_APP
This macro need for compile some functions in /hamming_codec_lab/hamming_codec/... necessary for the functioning of the App class
### WIN_COMPILE_DEBUG
This macro need for compile some code in /hamming_codec_lab/hamming_codec/... library-dependent C++ language for windows platform(or linux but not tested)
### MATRIX_PRINTING
This macro need for compile some code in /hamming_codec_lab/hamming_codec/mat.cpp responsible for outputting the matrix 
### HAMMING_EXTENDED_ON
This macro need for compile some functions in /hamming_codec_lab/hamming_codec/[hamming] necessary for the functioning of extended hamming codec
### HAMMING_CODER_OPTIMIZATION
This macro need for compile some code and functions in /hamming_codec_lab/hamming_codec/[hamming] allowing to speed up the code by creating a dictionary of codewords
Use this macro only for code with initial parameter of hamming codec <= 4
### MEM_COUNTING
This macro allow to enable counting of memory allocated in the heap for objects of Bit_matrix class
### DEBUG
This macro allows you to set the debug level. The higher the number, the more information will be displayed
### ARDUINO_COMPILE_OPT
This macro allow to compile /hamming_codec_lab/hamming_codec/... for arduino

## Coder

## Decoder
