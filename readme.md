<h3 align="center"><img src=https://user-images.githubusercontent.com/12807776/172697062-e698a475-cebc-4856-836c-de510664f225.png alt="onload" height="125px"></h3>

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

To configure onload you can customize the headers located in
include/colourbar and include/onload. This allows for you to control output given in results,
configure the colour bar settings (if you dont like the current look), and set custom time string
along with being able to write your own methods if you so like.


The example colourbar `BLOCK_ARRAY` defined in colourbar.h

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

The example output `RESULT` defined in onload.h

```c
char *RESULT[MAX_RESULT_COL][MAX_RESULT_ROW] = {
    {CHECK, " Terminal ", ARROW, " ",  info -> Terminal},
    {CHECK, " Kernel   ", ARROW, " ",  info -> Kernel},
    {CHECK, " Desktop  ", ARROW, " ",  info -> Desktop},
    {CHECK, " Time     ", ARROW, " ",  info -> Time}
};
```

To change the time format modify the `TIME_FMT` definition in include/colourbar header.

```c
#define TIME_FMT "%a %b %d %I:%M:%S %Y"
```

<h2>Note</h2>

This project is far from complete and needs a lot of work to be a complete
command line system information tool.
I fully intend to make this program a complete library and tool but school and work are a priority.
