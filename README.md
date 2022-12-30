# NoOS MP

Note:<br>
There is no License attached to this repository.<br>
Hence, as stated in [GitHub documentation about Licensing](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository#choosing-the-right-license), default copyright laws apply.

## Introduction

This is a project which allows users to run programs directly on hardware without needing to rely on any OS running on the hardware.<br>
It aims to simplify the process of running parallel algorithms directly on hardware.<br>

Users can write parallel algorithms in a format similar to Open MP and CUDA programs.<br>
A UEFI Application created as part of this project will run the user's program on the required number of cores on the hardware.<br>
This project also implements a small library with features which users may need to use.

### Setup Instructions

The target hardware must support UEFI and its MP Service Protocol for the parallel programs written using this project to work.

If you wish to compile the UEFI Application or make UEFI calls from your program, then you must install [GNU-EFI](https://sourceforge.net/projects/gnu-efi/).<br>
Please check the README in the folders named LIB and DEP for further details on this setup.

### Usage Instructions

Please check the README in the folder named CODE for details on using this project.

You can also check the folder named EXAMPLES for some sample parallel algorithms written using this project.
