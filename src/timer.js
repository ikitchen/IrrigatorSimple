var end = Date.now() + _e;
setInterval(function() {
    var elapsed = end - Date.now();
    if (elapsed <= 0) {
        window.location.reload();
    } else {
        document.getElementById('elapsed').innerText = (elapsed / 1000) | 0;
    }
}, 1000);
