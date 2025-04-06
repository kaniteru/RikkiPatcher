const eLogLv = {
    LOG_LV_INFO  : [0, "INFO",     "white"],
    LOG_LV_ALERT : [1, "ALERT",    "yellow"],
    LOG_LV_PROG  : [2, "PROGRESS", "orange"],
    LOG_LV_FATAL : [3, "FATAL",    "red"],
    LOG_LV_DEBUG : [4, "DEBUG",    "lightblue"]
}

class Logger {
    log(lv, msg) {
        const div = document.createElement('div');
        div.className = 'div-log';

        const now = new Date().toTimeString().split(' ')[0];
        div.textContent = `${now} [${lv[1]}] ${msg}`;
        div.style.color = lv[2];

        Logger.#DIV_CONSOLE.appendChild(div);
        Logger.#DIV_CONSOLE.scrollTop = Logger.#DIV_CONSOLE.scrollHeight;
    }

    test() {
        for (const k in eLogLv) {
            this.log(eLogLv[k], 'Test log');
        }
    }

    clear() {
        while (Logger.#DIV_CONSOLE.firstChild) {
            Logger.#DIV_CONSOLE.removeChild(Logger.#DIV_CONSOLE.firstChild);
        }
    }

    constructor() {
        this.log(eLogLv.LOG_LV_INFO, 'Logger initialized');
    }

    static #DIV_CONSOLE = document.getElementById('div-console');
    static INSTANCE = new Logger();
}

/* CPP BIND FUNCTIONS */

function _log(lv, msg) {
    const k = Object.keys(eLogLv);
    Logger.INSTANCE.log(eLogLv[k[lv]], msg);
}

function _clearLog() {
    Logger.INSTANCE.clear();
}