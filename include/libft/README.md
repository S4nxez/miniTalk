# Libft

¡Bienvenido a mi Libft!

Este proyecto forma parte del plan de estudios de Campus42 y consiste en crear tu propia biblioteca estándar de C, que incluye funciones comunes para trabajar con cadenas, caracteres, memoria y listas.

En 42, estamos limitados en el uso de algunas bibliotecas estándar en nuestros proyectos, por lo que debemos agregar constantemente nuevas funciones a nuestra propia biblioteca a medida que avanzamos en el programa.

## Contenido

La biblioteca se organiza en varios archivos, cada uno conteniendo un conjunto de funciones relacionadas. Aquí tienes una breve descripción de los archivos y sus contenidos:

- `libft.h`: Archivo de cabecera que contiene los prototipos de todas las funciones de la librería.
- `libft.a`: Biblioteca estática que incluye todas las implementaciones de las funciones de la librería.

Libc         | Funciones Adicionales | Funciones Bonus
:----------- | :-----------: | :-----------: |
memset		| ft_memalloc	| ft_lstnew		|  
bzero		  | ft_memdel		| ft_lstdelone|  
memcpy		| ft_strnew		| ft_lstdel		|   
memccpy		| ft_strdel		| ft_lstadd		|   
memmove		| ft_strclr		| ft_lstiter	|    
memchr		| ft_striter	| ft_lstmap		| 
memcmp		| ft_striteri	|				      |
strlen		| ft_strmap		|				      |
strdup		| ft_strmapi	|				      | 
strcpy		| ft_strequ		|				      |
strncpy		| ft_strnequ	|			        |
strcat		| ft_strsub		|             | 
strlcat		| ft_strjoin	|             |
strchr		| ft_strtrim	|             |
strrchr		| ft_strsplit	|             |
strstr		| ft_itoa		  |             | 
strnstr		| ft_putchar	| 
strcmp		| ft_putstr		| 
strncmp		| ft_putendl	| 
atoi		  | ft_putnbr		  | 
isalpha		| ft_putchar_fd	| 
isdigit		| ft_putstr_fd	| 
isalnum		| ft_putendl_fd	| 
isascii		| ft_putnbr_fd	| 
isprint		||  
toupper		| |
tolower		| | 

## Compilación

Para compilar la biblioteca, simplemente ejecuta el comando `make` en la raíz del proyecto. Esto generará el archivo `libft.a`, que puedes vincular con tus programas.

