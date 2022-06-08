<h3 align="center"><img src=https://user-images.githubusercontent.com/12807776/172698180-9a5df392-656e-4c80-91d2-468d6b38e238.png alt="onload" title="onload example" height="125px"></h3>

<p align="center">Command line system information tool written in C.<p>

<h2 align="left">Requirements</h2>

  * gcc
  * make

<h2 align="left">Installing</h2> 

<p>onload requires to be built from source. This makes it highly customiziable
and portable since you can configure settings through the headers.<p>

To install run
```console
make
sudo make install
```

<h2>Configuring</h2>

<p>To configure onload you can customize the headers located in
include/colourbar and include/onload. This allows for you to control output given in results,
configure the colour bar settings (if you dont like the current look), and set custom time string
along with being able to write your own methods if you so please.<p>


The project hierarchy

onload
├── include
│   ├── colourbar
│   │   ├── [colourbar.c](https://github.com/wnstdrr/onload/tree/main/include/colourbar/colourbar.c)
│   │   └── [colourbar.h](https://github.com/wnstdrr/onload/tree/main/include/colourbar/colourbar.h)
│   └── onload
│       ├── [onload.c](https://github.com/wnstdrr/onload/blob/main/include/onload/onload.c)
│       └── [onload.h](https://github.com/wnstdrr/onload/blob/main/include/onload/onload.h)

The example colourbar `BLOCK_ARRAY` defined in include/colourbar/colourbar.h

```c
const char *BLOCK_ARRAY[MAX_COLOUR_SIZE] {
    DRK_BAR,           BAR, RESET,
    RED_LGHT_BAR,      BAR, RESET,
    GREEN_DRK_BAR,     BAR, RESET,
    YELLOW_DRK_BAR,    BAR, RESET,
    BLUE_DRK_BAR,      BAR, RESET,
    MAG_DRK_BAR,       BAR, RESET,
    CYAN_DRK_BAR,      BAR, RESET,
    WHITE_LGHT_BAR,    BAR, RESET,
    LGHT_BAR,          BAR, RESET,
    RED_DRK_BAR,       BAR, RESET,
    GREEN_LGHT_BAR,    BAR, RESET,
    YELLOW_LGHT_BAR,   BAR, RESET,
    BLUE_LGHT_BAR,     BAR, RESET,
    MAG_LGHT_BAR,      BAR, RESET,
    CYAN_LGHT_BAR,     BAR, RESET,
    WHITE_DRK_BAR,     BAR, RESET
};
```
The example output `RESULT` defined in include/onload/onload.h

<p>Customizing this array allows for users to create their own results look and feel.<p>

```c
char *RESULT[MAX_RESULT_COL][MAX_RESULT_ROW] = {
    {CHECK, " Terminal ", ARROW, " ",  info -> Terminal},
    {CHECK, " Kernel   ", ARROW, " ",  info -> Kernel},
    {CHECK, " Pkgs     ", ARROW, " ",  info -> Packages},
    {CHECK, " Desktop  ", ARROW, " ",  info -> Desktop},
    {CHECK, " Time     ", ARROW, " ",  info -> Time}
};
```

To change the time format modify the `TIME_FMT` definition in include/onload header.

```c
#define TIME_FMT "%a %b %d %I:%M:%S %Y"
```

<h2>Note</h2>

This project is far from complete and needs a lot of work to be a complete
command line system information tool.
I fully intend to make this program a complete library and tool but school and work are a priority.
