const eLogLv = {
    LOG_LV_INFO  : [0, "INFO",  "white"],
    LOG_LV_ALERT : [1, "ALERT", "yellow"],
    LOG_LV_PROG  : [2, "PROG",  "orange"],
    LOG_LV_FATAL : [3, "FATAL", "red"],
    LOG_LV_DEBUG : [4, "DEBUG", "lightblue"],
    LOG_LV_ERROR : [5, "ERROR", "red"]
}

class Logger {
    static log(lv, msg) {
        Logger.#INSTANCE.logImpl(lv, msg);
    }

    static fmtLog(lv, fmt, ...args) {
        Logger.#INSTANCE.fmtLogImpl(lv, fmt, ...args);
    }

    static clear() {
        Logger.#INSTANCE.clearImpl();
    }

    logImpl(lv, msg) {
        const div = document.createElement('div');
        div.className = 'div-log';

        const now = new Date().toTimeString().split(' ')[0];
        div.textContent = `${now} [${lv[1]}] ${msg}`;
        div.style.color = lv[2];

        Logger.#DIV_CONSOLE.appendChild(div);
        Logger.#DIV_CONSOLE.scrollTop = Logger.#DIV_CONSOLE.scrollHeight;
    }

    fmtLogImpl(lv, fmt, ...args) {
        try {
            if (!fmt) {
                this.logImpl(lv, "Error: Missing format string");
                return;
            }

            let formattedMsg = fmt;
            let argIndex = 0;

            formattedMsg = formattedMsg.replace(/\{\}/g, () => {
                if (argIndex < args.length) {
                    const arg = args[argIndex++];
                    // Handle different types of arguments safely
                    if (arg === null || arg === undefined) {
                        return 'null';
                    } else if (typeof arg === 'object') {
                        try {
                            return JSON.stringify(arg);
                        } catch (e) {
                            return '[Object]';
                        }
                    } else {
                        return String(arg);
                    }
                }

                return '[missing]';
            });

            this.logImpl(lv, formattedMsg);
        } catch (error) {
            this.logImpl(lv, `Error formatting message: ${fmt}`);
        }
    }

    clearImpl() {
        while (Logger.#DIV_CONSOLE.firstChild) {
            Logger.#DIV_CONSOLE.removeChild(Logger.#DIV_CONSOLE.firstChild);
        }
    }

    constructor() {
        this.logImpl(eLogLv.LOG_LV_INFO, 'Logger initialized');
    }

    static #DIV_CONSOLE;
    static #INSTANCE;

    static {
        Logger.#DIV_CONSOLE = document.getElementById('div-console');
        Logger.#INSTANCE = new Logger();
    }
}

/* CPP BIND FUNCTIONS */

function _log(lv, msg, ...args) {
    const k = Object.keys(eLogLv);
    let fmt = Format.get(msg);
    console.log("_log called with:", { lv, msg, args });

    if (fmt === null) {
        Logger.log(eLogLv.LOG_LV_ERROR, `Fmt not found: ${msg}`)
        fmt = msg;
    }

    if (args && args.length > 0) {
        Logger.fmtLog(eLogLv[k[lv]], fmt, ...args);
    } else {
        Logger.log(eLogLv[k[lv]], fmt);
    }
}

function _clearLog() {
    Logger.clear();
}