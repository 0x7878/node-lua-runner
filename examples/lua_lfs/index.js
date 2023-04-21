const nodelua = require('../../index');

var lua = new nodelua.LuaState();


lua.DoFile(__dirname + "/file.lua");
