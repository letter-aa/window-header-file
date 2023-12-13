*create windows easily! no need to make your own windows function with the oh so tedious "WinMain", just call newWindow and put in the arguments (in order):

**the window name** - anything you want it to be

**the window icon** - anything that starts with ICON_

**the size of the window** - put in {x,y} for this one! (x being the width, and y being the height)

**the position of the window** - put in {x,y} for this one too! if you want, you can use "defaultPos" for the x, and/or the y to use the default position!

here's an example:

```
newWindow("I'm a window!", ICON_DEFAULT, { 500,500 }, { defaultPos, defaultPos });
```


*just dont forget to include the header file
