# ia2_test

This is a simple command line tool on windows which grabs the IAccessible interface under the mouse or from a given point, attempts to convert it to an IAccessible2 interface and recursively goes down the object hierarchy calling a representative sample of IA2 methods. I found it quite helpful when debugging crashes when using screen readers.

## Building

Just invoke **make**, depends on **i686-w64-mingw32-g++**

## Usage

If you don't already have a screen reader installed, you'll need to register the IAccessible2Proxy.dll library [available here](https://wiki.linuxfoundation.org/accessibility/iaccessible2/comproxydll)

After invoking ia2_test.exe from the command line you'll be presented with a simple command prompt accepting the following commands:

**mouse** - grabs the IAccessible object from the window underneath the mouse cursor

**quit** - quits ia2_test.exe

**x, y** - grabs the IAccessible object from the window underneath the given point

