import json

Import("env")

with open('src/timer.js', 'r') as ifile:
    source = ifile.read()
    stringified = json.dumps(source)
    with open('src/timer.js.h', 'w') as ofile:
        ofile.write('#ifndef TIMER_JS_H\n')
        ofile.write('#define TIMER_JS_H\n')
        ofile.write('//DO NOT MODIFY THIS FILE. It is generated automatically\n')
        ofile.write('#define TIMER_JS F(' + stringified + ')\n')
        ofile.write('#endif\n')
print "Created src/timer.js.h"