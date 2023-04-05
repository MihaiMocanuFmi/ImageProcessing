# ImageProcessing
This app is an image processing application that can process plain ppm, pgm or pbm file formats.

## Abilities
* Brightness and contrast adjustment. 
* Gamma correction. 
* Image convolutions: 
  * Mean blur
  * Gaussian blur
  * Horizontal Sobel
  * Vertical Sobel
* Cropping.
* Basic drawing.

## Dependencies
* CMake
* Catch2v3 (for tests)
* AddressSanitizer (Debugging)
* Doxygen (For documentation generation)
* C++20 (recommended)

## Generate Documentation
Run `doxygen` in a terminal to generate html and latex documentation.
They will be found in the `Docs/` directory

## Notes
This was only tested on Linux, format of file paths might pose a problem in Windows.