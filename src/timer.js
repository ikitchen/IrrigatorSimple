(function(document, now, second) {
    var end = now() + _e;
    function loop() {
        var elapsed = end - now();
        if (elapsed <= 0) {
            document.location.reload();
        } else {
            document.getElementById('elapsed').innerText =
                (elapsed / second) | 0;
        }
    }
    setInterval(loop, second);
    loop();
})(document, Date.now, 1000);
