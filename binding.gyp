{
  "targets": [
    {
      "target_name": "NodeIbapiAddon",
      "sources": [ "NodeIbapiAddon.cpp"
                  ,"NodeIbapi.cpp"
                  ,"IbPosixClient.cpp"
                  ,"import/EPosixClientSocket.cpp"
                  ,"import/EClientSocketBase.cpp" ],
      "cflags":  ['-O2'],
      "cflags_cc": ['-O2'],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          },
        }],
        ['OS=="win"', {
          'libraries': ['-llibjson.lib']
        }],
        ['OS!="win"', {
          'link_settings': {
            'libraries': ['libjson.a',],
            'library_dirs': ['../import/libjson',],
          },
        }],
      ]
    }
  ]
}
