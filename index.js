if(process.platform === "win32")
  process.env['LUA_CPATH'] = __dirname + "\\build\\Release\\clibs\\?.dll";

var nodelua = null;

nodelua = require(__dirname + "/build/Release/nodelua");

module.exports = nodelua;
