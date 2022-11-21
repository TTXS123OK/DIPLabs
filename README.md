# DIPLabs

### Introduction

* This is my implementation of the labs in our Digital Image Processing Course.

### File Structure

* assets: sample pictures, input and output of my labs
* out: executable files of by labs
* src: source code

### How to Compile and Run

1. Git clone to your local device
2. Ensure you have already installed gcc, g++ and cmake
3. Navigate into DIPLabs directory
4. `cmake -S . -B ./build` to init cmake directories
5. `cd ./build; cmake --build` to build this project
6. `make` to generate all executable files
7. `cd DIPLabs/out` and you can run the demo you want

### lab1

#### Requirement

1. Load and Save Bitmap without use library
2. Convert each pixel from rgb to yuv
3. Change bitmap into 8 bit grayscale and save
4. Change the value of Y channel of each pixel and save

#### Result

|             original image              |                grayscale image                |                 channel Y changed                 |
|:---------------------------------------:|:---------------------------------------------:|:-------------------------------------------------:|
| ![image-1-1](./assets/lab1/in/lena.bmp) | ![image-1-2](./assets/lab1/out/lena_gray.bmp) | ![image-1-3](./assets/lab1/out/lena_convertY.bmp) |

### lab2

#### Requirement

1. Implement the conversion of grayscale image to binary image
2. Implement the Morphological operation 'erosion'
3. Implement the Morphological operation 'dilation'
4. Implement the Morphological operation 'open'
5. Implement the Morphological operation 'close'

#### Result

* Morphological Operations

|              original image               |                   after erosion                   |                   after dilation                   |                   after open                   |                   after close                   |
|:-----------------------------------------:|:-------------------------------------------------:|:--------------------------------------------------:|:----------------------------------------------:|:-----------------------------------------------:|
| ![image-2-1](./assets/lab2/in/origin.bmp) | ![image-2-2](./assets/lab2/out/after_erosion.bmp) | ![image-2-3](./assets/lab2/out/after_dilation.bmp) | ![image-2-4](./assets/lab2/out/after_open.bmp) | ![image-2-5](./assets/lab2/out/after_close.bmp) |

* Border Detection

|               original image               |                   detect border                    |
|:------------------------------------------:|:--------------------------------------------------:|
| ![image-2-6](./assets/lab2/in/soldier.bmp) | ![image-2-7](./assets/lab2/out/soldier_border.bmp) |

### lab3

#### Requirement

1. Image logarithmic operation for visibility enhancement
2. Histogram equalization

#### Result

* Logarithmic Operation

|                  before logarithmic                   |                   after logarithmic                   |
|:-----------------------------------------------------:|:-----------------------------------------------------:|
| ![image-3-1](./assets/lab3/in/before_logarithmic.bmp) | ![image-3-2](./assets/lab3/out/after_logarithmic.bmp) |


* Histogram Equalization

|          before histogram equalization           |           after histogram equalization           |
|:------------------------------------------------:|:------------------------------------------------:|
| ![image-3-3](./assets/lab3/in/before_histeq.bmp) | ![image-3-4](./assets/lab3/out/after_histeq.bmp) |


### lab4

#### Requirement

1. Translation
2. Rotation
3. Scale
4. Shear
5. Mirror

#### Result

|                 origin                  |                   translation                   |                   rotation                   |
|:---------------------------------------:|:-----------------------------------------------:|:--------------------------------------------:|
| ![image-4-1](./assets/lab4/in/lena.bmp) | ![image-4-2](./assets/lab4/out/translation.bmp) | ![image-4-2](./assets/lab4/out/rotation.bmp) |


|                   scale                   |                   shear                   |                     mirror                      |
|:-----------------------------------------:|:-----------------------------------------:|:-----------------------------------------------:|
| ![image-4-4](./assets/lab4/out/scale.bmp) | ![image-4-5](./assets/lab4/out/shear.bmp) | ![image-4-6](./assets/lab4/out/mirror_by_x.bmp) |

### lab5

#### Requirement

1. Image mean filtering
2. Laplacian image enhancement

#### Result

|                 origin                  |                   mean filtering                   |                 laplacian enhancement                 |
|:---------------------------------------:|:--------------------------------------------------:|:-----------------------------------------------------:|
| ![image-5-1](./assets/lab5/in/lena.bmp) | ![image-5-2](./assets/lab5/out/mean_filtering.bmp) | ![image-5-2](./assets/lab5/out/laplacian_enhance.bmp) |
