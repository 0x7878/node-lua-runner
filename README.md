## Node-lua-runner

This is a fork from [medaeus245/node-lua](https://github.com/medaeus245/node-lua) which won't get any updates anymore and was just outdated.
Credits goes to him for the original work.

This Package allows you to use LUA inside Node.js.
See [`examples`](#examples).

I refactored the code so that it will compile with newer Node.JS versions.
I tested it with Windows 10 and Node.JS 18+. 
Other Operating Systems or Combinations are not tested yet.

## Installation

`npm install node-lua-runner`

## 1.1.0	2023-04-21

- Added LuaFileSystem for Windows (x64) compiled against luajit. See Examples for usage.

## About


Using Lua5.1 C interface: https://www.lua.org/manual/5.1/manual.html with luajit compiler

**Based on:**
 - nodelua ( https://github.com/brettlangdon/NodeLua )
 - node-luajit ( https://github.com/whtiehack/node-luajit )
 - LuaFileSystem ( https://github.com/lunarmodules/luafilesystem )

**Features:**
- Low-Level API
- For now Sync only


**Compilation:**
- On Windows and Mac : Luajit library already included in the package
- On Linux: Compilation with following parameters:
  - Include directory: (find /usr/include /usr/local/include $NODELUA_INCLUDE -name lua.h | sed s/lua.h//)
  - Library directory: "/usr/local/lib"
  - Library: "/usr/local/lib/libluajit-5.1.so"

NOTE (Linux only): Don't forget to set your LD_LIBRARY_PATH to /usr/local/lib so that node-lua can find luajit.

## Examples

- [Simple](https://github.com/0x7878/node-lua-runner/blob/master/examples/simple/index.js)
- [Using lua require function](https://github.com/0x7878/node-lua-runner/blob/master/examples/lua_require/index.js)
- [using lua file system](https://github.com/0x7878/node-lua-runner/tree/master/examples/lua_lfs)

## API


```javascript

const nodelua = require('node-lua-runner');

var lua = new nodelua.LuaState();


/**
 * [Add a path to the lua package.path variable. Set a root path for lua require (see example)]
 * @param  {String} path
 */
lua.AddPackagePath(__dirname);


/**
 * [Loads and runs the given file]
 * @type {String} file
 * @throws {Exception}
 */
lua.DoFile(__dirname + "/test.lua");


/**
 * [Loads and runs the given string]
 * @type {String} str
 * @throws {Exception}
 */
lua.DoString("print('Hello world!')");


/**
 * [Sets the function f as the new value of global name]
 * @param  {String} name [name of the global in lua]
 * @param  {Function} f [function to set]
 */
lua.RegisterFunction('add', function() {
	var a = lua.ToValue(1);
	var b = lua.ToValue(2);
	lua.Pop(2);
	lua.Push(a + b);
	return 1;
});


/**
 * [Pops a value from the stack and sets it as the new value of global name]
 * @type {String} name
 */
lua.SetGlobal("myVar");


/**
 * [Pushes onto the stack the value of the global name]
 * @type {String} name
 */
lua.GetGlobal('myVar');


/**
 * [Does the equivalent to t[k] = v, where t is the value at the given valid index and v is the value at the top of the stack. This function pops the value from the stack.]
 * @type {Number} index
 * @type {String} key
 */
lua.SetField(index, "t");


/**
 * [Pushes onto the stack the value t[key], where t is the value at the given valid index.]
 * @type {Number} index
 * @type {String} key
 */
lua.GetField(index, "t");


/**
 * [Get value at the given acceptable index]
 * @type {Number} index
 * @return value
 */
var value = lua.ToValue(-1);


/**
 * [Calls a function. Gets the function and arguments from the stack. Pushes the results onto the stack. See https://www.lua.org/manual/5.1/manual.html#pdf-pcall for more information]
 * @type {Number} args
 * @type {Number} results
 * @throws {Exception}
 */
lua.Call(args, results);


/**
 * [Yields a coroutine.]
 * @type {Number} args
 */
lua.Yield(args);


/**
 * [Starts and resumes a coroutine in a given thread.]
 * @type {Number} args
 */
lua.Resume(args);


/**
 * [Pushes a value n onto the stack]
 * @type n
 */
lua.Push(5);


/**
 * [Pops n elements from the stack. Default value is 1]
 * @type {Number} n
 */
lua.Pop();
lua.Pop(n);


/**
 * [Returns the index of the top element in the stack. Because indices start at 1, this result is equal to the number of elements in the stack (and so 0 means an empty stack)]
 * @return {Number}
 */
var size = lua.GetTop();


/**
 * [Accepts any acceptable index, or 0, and sets the stack top to this index. If the new top is larger than the old one, then the new elements are filled with nil. If index is 0, then all stack elements are removed]
 * @type {Number} index
 */
lua.SetTop(index);


/**
 * [Moves the top element into the given position (and pops it), without shifting any element (therefore replacing the value at the given position)]
 * @type {Number} index
 */
lua.Replace(index);


```
