<h3 align="center"><img src=https://user-images.githubusercontent.com/12807776/172698180-9a5df392-656e-4c80-91d2-468d6b38e238.png alt="onload" title="onload example" height="125px"></h3>

<p align="center">Command-line system information tool written in C<p>

<h1 align="left">Getting Started</h1>
<p>This is my take on my own command-line system information tool written in C. I personally felt that a command-line information tool should be written in the language that is closest to the machine i.e C. Since C has many libraries to interface nativly with Linux it can be quite flexiable and fast depending on your system hardware. I went for a simple approach without anything to flashy, a colour bar, and the output. The name onload comes from a habit of typically putting other system info tools into a .bashrc and having the program run on terminal load i.e onload.</p>

<h2 align="left">Prerequisites</h2>
Installation of these packages varys depending on which package manager you're using. So, just find which package matches these versions or the latest.

  * gcc >= 10.2.1
  * lsb-release (most systems have this already)
  * make

<h2 align="left">Installation</h2> 
Follow these steps to install

1. Clone the repository 
   ```sh
   git clone "https://github.com/wnstdrr/onload.git
   ```
2. Change into the new directory and run
   ```sh
   sudo make install
   ```
   or if you already have installed this software and want to update the sources run
   ```sh
   sudo make clean install
   ```

<h2 align="left">Configuration</h2>

To configure onload you can modify the definitions located in
`config.h` and `colours.h` then recompile with the provided Makefile and instructions to clean the previous install.

The shared object libraries are stored in the `/usr/lib/onload` directory and the header files can either be found in `onload/include` or `/usr/include/onload`.

The project hierarchy

```
onload
├── include
│   ├── colourbar
│   │   ├── colourbar.c
│   │   └── colourbar.h
│   └── onload
│       ├── onload.c
│       └── onload.h
```

Modify the `time_fmt` definition in onload.h to change the default time settings.
 
Percent formatters used in `time_fmt` are parsed by *strftime* see [Linux manual page](https://man7.org/linux/man-pages/man3/strftime.3.html) for help on formatting.

```c
#define time_fmt "%a %b %d %I:%M:%S %Y"
```
 
<h2 align="left">blkstruct as defined in colourbar.h</h2>
<details>
<summary>blkstruct</summary>

```c
                          /* background     style  endline*/
blk blkstruct = { .blk = { { dark,          block, reset },
                           { light_red,     block, reset },
                           { dark_green,    block, reset },
                           { dark_yellow,   block, reset },
                           { dark_blue,     block, reset },
                           { dark_magenta,  block, reset },
                           { dark_cyan,     block, reset },
                           { light_white,   block, reset },
                           { light,         block, reset },
                           { dark_red,      block, reset },
                           { light_green,   block, reset },
                           { light_yellow,  block, reset },
                           { light_blue,    block, reset },
                           { light_magenta, block, reset },
                           { light_cyan,    block, reset },
                           { dark_white,    block, reset } } };
```
</details>

<h3 align="left">out_array as defined in onload.c under onload_output()</h3>

Customizing this array allows for you to create your own results look and feel.
Just make sure you change the `max_row` definition to account for the new array length.

<details>
<summary>out_array</summary>

```c
const char *out_array[][max_row] = {
        {completion, " ", "OS     ", seperator_colour, seperator, reset, " ", info->dist},
        {completion, " ", "Kernel ", seperator_colour, seperator, reset, " ", info->kernel},
        {completion, " ", "Term   ", seperator_colour, seperator, reset, " ", info->term},
        {completion, " ", "Date   ", seperator_colour, seperator, reset, " ", info->date},
        {completion, " ", "Uptime ", seperator_colour, seperator, reset, " ", info->sysup},
        {completion, " ", "Desk   ", seperator_colour, seperator, reset, " ", info->desk},
        {completion, " ", "Pkgs   ", seperator_colour, seperator, reset, " ", info->pkgs},
};
```
</details>

<h2 align="left">Note</h2>

This project is far from complete and needs a lot of work to be a complete
command line system information tool.
I fully intend to make this program a complete library and tool but school and work are a priority.
