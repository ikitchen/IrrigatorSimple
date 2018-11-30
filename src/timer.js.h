#ifndef TIMER_JS_H
#define TIMER_JS_H
//DO NOT MODIFY THIS FILE. It is generated automatically
#define TIMER_JS "var end = Date.now() + _e;\nsetInterval(function() {\n    var elapsed = end - Date.now();\n    if (elapsed <= 0) {\n        window.location.reload();\n    } else {\n        document.getElementById('elapsed').innerText = (elapsed / 1000) | 0;\n    }\n}, 1000);\n"
#endif
