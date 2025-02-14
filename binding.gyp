{
  "targets": [
    {
      "target_name": "nodelua",
      "variables": {
        "lua_include": "",
        "lib_dirs": ""
      },
      "conditions": [
        [
          "OS=='win'",
          {
          "variables": { 
            "module_root_dir": "<!(cd)"
            },
            "include_dirs": [
              "./win64luajit"
            ],
            "library_dirs": [
              "./win64luajit"
            ],
            "libraries": [
              "lua51.lib"
            ],
            "copies":[
            { 
              'destination': './build/Release',
              'files':[
                '<(module_root_dir)/win64luajit/lua51.dll',
              ]},
              {
              'destination': './build/Release/clibs',
              'files':[
                '<(module_root_dir)/win64luajit/lfs.dll',
              ]
            }
            ]
          }
        ],
        [
          'OS=="mac"',
          {
            "include_dirs": [
              "./maclualib/include"
            ],
            "libraries": [
              "../maclualib/lib/liblua.a"
            ],
            "actions": [],
            "cflags": [
              "-std=c++11",
              "-stdlib=libc++"
            ],
            "xcode_settings": {
              "CLANG_CXX_LANGUAGE_STANDARD": "c++0x",
              "CLANG_CXX_LIBRARY": "libc++"
            }
          }
        ],
        [
          'OS=="linux"',
          {
            "include_dirs": [
               "<!(find /usr/include /usr/local/include $NODELUA_INCLUDE -name lua.h -print -quit | sed s/lua.h//)"
            ],
            "library_dirs": [
              "/usr/local/lib"
            ],
            "libraries": [
              "/usr/local/lib/libluajit-5.1.so"
            ],
            "actions": []
          }
        ]
      ],
      "sources": [
        "src/utils.cc",
        "src/luastate.cc",
		"src/nodelua.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
