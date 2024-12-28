const RIKKI_PATCHER_VER = 241228;

function onLoad() {
    Logger.INSTANCE.log(eLogLv.LOG_LV_INFO, `Rikki Patcher Version: ${RIKKI_PATCHER_VER}`);
    const inWv = typeof window.INIT_PATCHER === "function";

    if (inWv) {
        Control.INSTANCE.move(eCtrlLv.CTRL_LV_PROGRESS);
        window.INIT_PATCHER();
    } else {
        Logger.INSTANCE.log(eLogLv.LOG_LV_DEBUG, 'Rikki Patcher running in web');
        Control.INSTANCE.move(eCtrlLv.CTRL_LV_PATCH);
    }
}

document.getElementById('h4-kani').addEventListener('click', ev => {
    window.OPEN_GITHUB();
});

function _initSuccess() {

}

function _initGmdir(fd) {
    if (fd === '') {
        Control.INSTANCE.move(eCtrlLv.CTRL_LV_GMDIR);
    } else {
        //Logger.INSTANCE.log(eLogLv.LOG_LV_INFO, `Game directory set: ${fd}`);
        Control.INSTANCE.move(eCtrlLv.CTRL_LV_OPTIONS);
    }
}
