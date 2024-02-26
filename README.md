# ft_printf 
This is a simple reimplementation of the [printf](https://en.cppreference.com/w/c/io/fprintf)
function.

The ft_printf is an individual project at [42](https://www.42sp.org.br) that
requires the recreation of a the printf function from the standard library with
the following specifiers.
- %c Prints a single character.
- %s Prints a string (as defined by the common C convention).
- %p The void * pointer argument has to be printed in hexadecimal format.
- %d Prints a decimal (base 10) number.
- %i Prints an integer in base 10.
- %u Prints an unsigned decimal (base 10) number.
- %x Prints a number in hexadecimal (base 16) lowercase format.
- %X Prints a number in hexadecimal (base 16) uppercase format.
- %% Prints a percent sign.

#### Objectives
- Unix logic

#### Skills
- Rigor
- Algorithms & AI

## Getting started
**Follow the steps below**

1- Clone the repo.
```bash
git clone https://github.com/darlen-silva/ft_printf_42sp && cd ft_printf_42sp
```

2- Generate the libftprintf.a running the 'make' command.
```bash
make
```

3- Compile a main file with the linked lib.
```bash
cc main.c -L. -lftprintf && ./a.out
```
### A main.c example:
```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, World!\n");
    return (0);
}
```

## Bonus
- Combination of the following flags: ’-0.’
- Field minimum width
- All the following flags: ’# +’

---

Made by:<br />
Darlen Silva 👋 [See my linkedin](https://www.linkedin.com/in/darlen-silva/)
