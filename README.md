# vexTurtlePlanner
A planner to make a vex robot draw a shape on the field (like the turtle graphics in the LOGO programming language)

# Uses
You can use:
- ** getTextPathPoints.exe ** to get a text path using the windows api. Then use ** (index.html)[https://wawesomenogui.github.io/vexTurtlePlanner/] ** to visualize and resize the points.
- You can also program a turtle routine in LOGO and use ** LOGOtoC.exe ** to translate the LOGO commands to C. Run LOGOtoC.exe like: `echo $myLOGOCode.lgo | LOGOtoC.exe` in a terminal. Alternitively echo short scripts directly e.g. `echo fd 10 rt 20 bk 40 | LOGOtoC.exe`.
